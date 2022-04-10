//
//  VOPDataHandler.cpp
//  VictimOffenderProfiler
//
//  Created by Paul Bauer on 4/9/22.
//

#include "VOPDataHandler.hpp"
#include "csv.hpp"

#include <algorithm>

void VOPDataHandler::LoadRawData(){
    
    //Get Offenses and create incident list
    LoadOffenseData(10);
    std::cout << "loaded offense data\n";
    
    //Get victim data
    LoadVictimData();
    std::cout << "loaded victim data\n";
    
}

void VOPDataHandler::LoadOffenseData(int limit){
    
    int count = 0;
    
    //Get document
    csv::CSVReader reader(dataInPath + "NIBRS_OFFENSE.csv");
    
    //Get rows of data
    for (auto& row: reader) {
        
        //Create incident object for this offense
        Incident* newIncident = new Incident();
        newIncident->offenseID = row["OFFENSE_ID"].get<int>();
        newIncident->offenseType = row["OFFENSE_TYPE_ID"].get<int>();
        
        //Add to incidents
        incidents.push_back(newIncident);
        
        count++;
        if(count > limit){
            break;
        }
        
    }
}

void VOPDataHandler::LoadVictimData(){
    
    //Get document
    csv::CSVReader victimOffense(dataInPath + "NIBRS_VICTIM_OFFENSE.csv");
    
    //Get rows of data
    for (auto& row: victimOffense) {
        
        //Locate incident for this offense
        for (auto& incident: incidents){
            if(row["OFFENSE_ID"].get<int>() == incident->offenseID){
                
                //add the victim id to the incident
                incident->victimID = row["VICTIM_ID"].get<int>();
                break;
                
            }
        }
    }
    
    std::cout << "Got victim id's\n";
    //Get document
    csv::CSVReader victim(dataInPath + "NIBRS_VICTIM.csv");
    
    //Get rows of data
    for (auto& row: victim) {
        
        //Locate incident for this offense
        for (auto& incident: incidents){
            if(row["VICTIM_ID"].get<int>() == incident->victimID){
                std::cout << "Found data for a victim\n";
                
                //add the victim type, age, and sex to the incident
                try{
                    incident->victimType = row["VICTIM_TYPE_ID"].get<int>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get vitim type\n";
                }
                
                try{
                    incident->victimAge = row["AGE_NUM"].get<int>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get victim age\n";
                }
                
                try{
                    incident->victimSex = row["SEX_CODE"].get<std::string>();
                    //std::cout << "got data\n";
                }
                catch(...){
                    std::cout << "could not get victim sex\n";
                }
                
                break;
                
            }
        }
    }
}

void VOPDataHandler::LoadVictimOffenderRealtionshipData(){
    
    //Get relationship data
    
}
