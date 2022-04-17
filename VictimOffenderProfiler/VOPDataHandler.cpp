//
//  VOPDataHandler.cpp
//  VictimOffenderProfiler
//
//  Created by Paul Bauer on 4/9/22.
//

#include "VOPDataHandler.hpp"
#include "csv.hpp"


void VOPDataHandler::LoadRawData(){
    
    //Get Offenses and create incident list
    LoadOffenseData(10000);
    std::cout << "loaded offense data\n";
    
    //Get victim data
    LoadVictimData();
    std::cout << "loaded victim data\n";
    
    //Get relationship data
    LoadVictimOffenderRealtionshipData();
    
    //Get bias motivation data
    LoadBiasData();
    
    int skip = 0;
    for(auto& incident: incidents){
        if(skip % int(incidents.size() * 0.05) == 0){
            incident->ListContents();
        }
    }
    
}

void VOPDataHandler::LoadOffenseData(int limit){
    
    int count = 0;
    
    //Get document
    csv::CSVReader reader(dataInPath + "NIBRS_VICTIM_OFFENSE.csv");
    
    //Get rows of data
    for (auto& row: reader) {
        
        //Create incident object for this offense
        Incident* newIncident = new Incident();
        newIncident->offenseID = row["OFFENSE_ID"].get<int>();
        newIncident->victimID = row["VICTIM_ID"].get<int>();
        
        //Add to incidents
        incidents.push_back(newIncident);
        
        count++;
        if(count > limit){
            break;
        }
        
    }
}

void VOPDataHandler::LoadVictimData(){
    
    //Make copy of incidents array and pop off incidents that have already been matched or setup method to skip indeces. Stop when all have been matched
    
    //Get document
    csv::CSVReader victimOffense(dataInPath + "NIBRS_OFFENSE.csv");
    
    int offenseIDsAdded = 0;
    
    //Get rows of data
    for (auto& row: victimOffense) {
        
        //Locate incident for this offense
        for (auto& incident: incidents){
            if(row["OFFENSE_ID"].get<int>() == incident->offenseID){
                
                //add the victim id to the incident
                incident->offenseType = row["OFFENSE_TYPE_ID"].get<int>();
                
                offenseIDsAdded++;
                //std::cout << "Added an offenseID" << offenseIDsAdded << "\n";
                break;
                
            }
        }
        if(offenseIDsAdded > incidents.size()){
            break;
        }
    }
    
    std::cout << "Got victim id's\n";
    //Get document
    csv::CSVReader victim(dataInPath + "NIBRS_VICTIM.csv");
    
    int victimsAdded = 0;
    
    //Get rows of data
    for (auto& row: victim) {
        
        //Locate incident for this offense
        for (auto& incident: incidents){
            if(row["VICTIM_ID"].get<int>() == incident->victimID){
                //std::cout << "Found data for a victim\n";
                
                //add the victim type, age, and sex to the incident
                try{
                    incident->victimType = row["VICTIM_TYPE_ID"].get<int>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get vitim type\n";
                    incident->victimType = -1;
                }
                
                try{
                    incident->victimAge = row["AGE_NUM"].get<int>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get victim age\n";
                    incident->victimAge = -1;
                }
                
                try{
                    incident->victimSex = row["SEX_CODE"].get<std::string>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get victim sex\n";
                    incident->victimSex = "unknown";
                }
                
                //Count victim that have been loaded
                victimsAdded++;
                break;
                
            }
        }
        
        if(victimsAdded > incidents.size()){
            break;
        }
    }
}

void VOPDataHandler::LoadVictimOffenderRealtionshipData(){
    
    //Get relationship types
    csv::CSVReader relationshipTypes(dataInPath + "NIBRS_RELATIONSHIP.csv");
    
    //Get rows of data
    for (auto& row: relationshipTypes) {
        
        //Add to map
        relationshipTypeStrings[row["RELATIONSHIP_ID"].get<int>()] = row["RELATIONSHIP_NAME"].get<std::string>();
        
        relationshipTypeNums[row["RELATIONSHIP_ID"].get<int>()] = row["RELATIONSHIP_TYPE_ID"].get<int>();
        
        //std::cout << relationshipTypeStrings[row["RELATIONSHIP_ID"].get<int>()] << "\n";
    }
    
    
    //Get relationship types
    csv::CSVReader relationships(dataInPath + "NIBRS_VICTIM_OFFENDER_REL.csv");
    
    int relationshipsAdded = 0;
    
    //Get rows of data
    for (auto& row: relationships) {
        
        //Locate incident for this relationship
        for (auto& incident: incidents){
            
            if(row["VICTIM_ID"].get<int>() == incident->victimID){
                //std::cout << "found: " << row["VICTIM_ID"].get<int>() << ", " << incident->victimID << "\n";
                //Get relationship id
                int relationshipId = row["RELATIONSHIP_ID"].get<int>();
                
                //std::cout << "RelationshipID" << relationshipTypeStrings[relationshipId] << "\n";
                
                //add the victim id to the incident
                incident->relationshipNum = relationshipTypeNums[relationshipId];
                incident->relationshipString = relationshipTypeStrings[relationshipId];
                relationshipsAdded++;
                break;
                
            }
        }
        if(relationshipsAdded > incidents.size()){
            break;
        }
    }
    
}

void VOPDataHandler::LoadBiasData(){
    //Get relationship types
    csv::CSVReader biasTypes(dataInPath + "NIBRS_BIAS_LIST.csv");
    
    //Get rows of data
    for (auto& row: biasTypes) {
        
        //Add to map
        biasTypeStrings[row["BIAS_ID"].get<int>()] = row["BIAS_DESC"].get<std::string>();
        
        relationshipTypeNums[row["BIAS_ID"].get<int>()] = row["BIAS_CODE"].get<int>();
        
        //std::cout << biasTypeStrings[row["BIAS_ID"].get<int>()] << "\n";
    }
    
    //Get relationship types
    csv::CSVReader bias(dataInPath + "NIBRS_BIAS_MOTIVATION.csv");
    
    int biasAdded = 0;
    
    //Get rows of data
    for (auto& row: bias) {
        
        //Locate incident for this relationship
        for (auto& incident: incidents){
            if(row["OFFENSE_ID"].get<int>() == incident->offenseID){
                
                //Get bias id
                int biasId = row["BIAS_ID"].get<int>();
                
                //add the victim id to the incident
                incident->biasNum = biasTypeNums[biasId];
                incident->biasString = biasTypeStrings[biasId];
                biasAdded++;
                break;
                
            }
        }
        if(biasAdded > incidents.size()){
            break;
        }
    }
    
}

void VOPDataHandler::CleanData(){
    
    //Remove duplicates
    RemovedDuplicates();
    
    //Remove records that are missing features
    RemoveIncompleteRecords();
    
    //Convert features to float values and store them in vectors
    GenerateIncidentVectors();
    
}

void VOPDataHandler::RemovedDuplicates(){
    
    //Remove duplicates
    std::vector<Incident*>::iterator uniqueIt = std::unique(incidents.begin(), incidents.end());
    uniqueIt = incidents.erase(uniqueIt, incidents.end());
    std::cout << "remaining incident data: " << incidents.size() << "\n";
    
}

void VOPDataHandler::RemoveIncompleteRecords(){
    
    //Remove incompletes
    auto incident = incidents.begin();
    while(incident != incidents.end()){
        //std::cout << "checking if this incident is missing data\n";
        
        //Check for missing features
        if(!(**incident > 5)){
            //std::cout << "this incident is missing data\n";
            incident = incidents.erase(incident);
        }else{
            ++incident;
        }
    }
    std::cout << "remaining incident data post cleaning: " << incidents.size() << "\n";
    
}

void VOPDataHandler::GenerateIncidentVectors(){
    
    //Convert features to float values
    for(auto& incident: incidents){
        
        //Create a vector with the 6 features
        incidentVectors.push_back(incident->GetIncidentVector());
    }
    
}

void VOPDataHandler::OutputIncidentVectors(){
    
    //open a file stream
    std::ofstream file;
    file.open("/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/CleanInput/CleanOutput.csv");
    
    //Create csv writer
    auto writer = csv::make_csv_writer(file);

    //Ouput all incident vectors to csv
    for(auto& incidentVector: incidentVectors){

        //Add row to the csv
        writer << incidentVector;

    }
    
    //Close file
    file.close();
}

void VOPDataHandler::LoadIncidentVectors(std::string inputPath) { 
    //Get document
    csv::CSVReader reader(dataInPath + "NIBRS_VICTIM_OFFENSE.csv");

    //Get rows of data
    for (auto& row: reader) {

        //Create vector for row
        std::vector<float> rowVec;

        //load vecors from csv
        for(auto& col: row){

            //Create vector
            rowVec.push_back(col.get<float>());

        }

        //Add to incidents
        incidentVectors.push_back(rowVec);

    }
    
    std::cout << "Loaded " << incidentVectors.size() << " Incident vectors\n";
}


