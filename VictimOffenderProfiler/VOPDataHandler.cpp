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
                    incident->victimRace = row["RACE_ID"].get<int>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get vitim race\n";
                    incident->victimRace = -1;
                }
                
                try{
                    incident->victimEthnicity = row["ETHNICITY_ID"].get<int>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get vitim ethnicity\n";
                    incident->victimEthnicity = -1;
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
                incident->relationshipNum = relationshipId;
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
        
        biasTypeNums[row["BIAS_ID"].get<int>()] = row["BIAS_CODE"].get<int>();
        
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
    
    //Sort outputs into categories
    SortRelationships();
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
        if(!(**incident > 6)){
            //std::cout << "this incident is missing data\n";
            incident = incidents.erase(incident);
        }else{
            ++incident;
        }
    }
    std::cout << "remaining incident data post cleaning: " << incidents.size() << "\n";
    
}

void VOPDataHandler::SortRelationships(){
    
    for(auto& incident: incidentVectors){
        
        int last = static_cast<int>(incident.size()-1);
        
        //check what relationship is
        if(incident[last] == 18 || incident[last] == 1 || incident[last] == 7 || incident[last] == 8 || incident[last] == 24){
            incident[last] = 0;
        }else{
            incident[last] = 1;
        }
    }
}

void VOPDataHandler::GenerateIncidentVectors(){
    
    //Convert features to float values
    for(auto& incident: incidents){
        
        //Create a vector with the 6 features
        incidentVectors.push_back(incident->GetIncidentVector());
    }
    
}

void VOPDataHandler::OutputIncidentVectors(){
    
    
    SortRelationships();
    
    
    //open a file stream
    std::ofstream file;
    file.open("/Users/paulbauer/Documents/Classes/Spring_2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/CleanInput/CleanOutput.csv");
    
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

void VOPDataHandler::OutputResultsVectors(){
    
    //open a file stream
    std::ofstream file;
    file.open("/Users/paulbauer/Documents/Classes/Spring_2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/Output/Predictions.csv");
    
    //Create csv writer
    auto writer = csv::make_csv_writer(file);

    //Ouput all incident vectors to csv
    for(auto& incidentVector: outputVectors){

        //Add row to the csv
        writer << incidentVector;

    }
    
    //Close file
    file.close();
}

void VOPDataHandler::LoadIncidentVectors(std::string inputPath) { 
    //Get document
    csv::CSVReader reader(inputPath);

    //Get rows of data
    for (csv::CSVRow& row: reader) {

        //Create vector for row
        std::vector<float> rowVec;

        //load vecors from csv
        for(csv::CSVField& col: row){

            //Create vector
            rowVec.push_back(col.get<float>());

        }

        //Add to incidents
        incidentVectors.push_back(rowVec);

    }
    
    std::cout << "Loaded " << incidentVectors.size() << " Incident vectors\n";
}

float VOPDataHandler::Sigmoid(float s) {
    float top = 1;//(pow(e, s));
    float bottom = (1 + pow(e, (-1 * s)));
    float S = (top/bottom);
    return S;
}

float VOPDataHandler::Tanh(float s) { 
    return (pow(e, s) - pow(e, (-s)))/(pow(e, s) + pow(e, (-s)));
}

void VOPDataHandler::UpdateWeights(float predicted, float recorded, std::vector<float> inputs) { 
    
    //Update weights for all features
    for(int i = 0; i < w.size(); i++){
        
        //Get gradient
        float g = (predicted - recorded) * inputs[i];
        
        //update weight for this feature
        w[i] = w[i] - (lr * g);
    }
}

float VOPDataHandler::PredictProbabilityS(std::vector<float> dataPoint) { 
    
    float weightedSum = 0;
    
    //calculate prediction using current weights
    for(int i = 0; i < w.size(); i++){
        weightedSum += w[i] * dataPoint[i];
    }
    
    //Activate using sigmoid and return
    return Sigmoid(weightedSum);
}

void VOPDataHandler::TrainModelS(int trainingSet, int epoch) { 
    
    //Seed weights
    for(auto& weight: w){
        weight = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
    
    float error = 1.0;
    //Train for requested number of epoch
    for(int i = 0; i < epoch; i++){
        
        //Save current weights
        std::vector<float> wBackup = w;
        
        //predict and update weights for each data point in the test set
        for(int j = 0; j < trainingSet; j++){
            
            //Get a predicted value
            float predictedOutput = PredictProbabilityS(incidentVectors[j]);
            
            UpdateWeights(predictedOutput, incidentVectors[j][(w.size())], incidentVectors[j]);
        }
        
        //Get insample error for this epoch
        float errorNow = GetError(trainingSet, 0, false);
        
        //Revert weights if error not lowered
        if(errorNow > error){
            w = wBackup;
        }else{
            error = errorNow;
        }
        
        
        std::cout << "Ein for epoch " << i << " : " << error << "\n";
    }
    
    //Get Eout
    float Eout = GetError(int(incidentVectors.size()), trainingSet, true);
    
    std::cout << "Final Eout: " << Eout << "\n";
}

float VOPDataHandler::GetError(int testEnd, int testStart, bool saveResults) {
    
    //Hold value for error
    float error = 0.0;
    
    //Get predictions for in sample and check errors
    for(int i = testStart; i < testEnd; i++){
        
        //Get prediction
        float prediction = PredictProbabilityS(incidentVectors[i]);
        
        //std::cout << "predicted: " << prediction << " " << round(prediction) << " actual: " << incidentVectors[i][5] << "\n";
        
        //Add incident record and prediction to outputVectors
        if(saveResults){
            
            //Add incident vector to results
            outputVectors.push_back(incidentVectors[i]);
            
            //Add prediction to result record
            outputVectors.back().push_back(prediction);
            
            //Print every 100th example to console
            if(i % 100 == 0){
                std::cout << "Actual: " << incidentVectors[i].back() << "Predicted: " << prediction << "/n";
            }
            
        }
        
        //round prediction
        if(prediction > 0.5){
            prediction = 1;
        }else{
            prediction = 0;
        }
        
        //Add to error
        if(prediction != incidentVectors[i][(w.size())]){
            error += 1.0;
        }
    }
    
    if(saveResults){
        
        //Save results to csv file
        OutputResultsVectors();
        
    }
    
    return error/testEnd;
}

float VOPDataHandler::GetDotProduct(float y , std::vector<float> x) {
    float sum = 0;
    
    //calculate prediction using current weights
    for(int i = 0; i < x.size()-1; i++){
        sum += x[i] * y;
    }
    
    //Activate using sigmoid and return
    return sum;
}

float VOPDataHandler::GetDotProduct(std::vector<float> y , std::vector<float> x) {
    float sum = 0;
    
    //calculate prediction using current weights
    for(int i = 0; i < y.size(); i++){
        sum += x[i] * y[i];
    }
    
    //Activate using sigmoid and return
    return sum;
}












