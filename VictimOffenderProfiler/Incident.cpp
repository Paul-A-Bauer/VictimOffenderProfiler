//
//  Incident.cpp
//  VictimOffenderProfiler
//
//  Created by Paul Bauer on 4/9/22.
//

#include "Incident.hpp"

//Default constructor
Incident::Incident() {
    
}

void Incident::ListContents(){
    std::cout << "Incident\n\n";
    
    //Print victime data
    std::cout << "VictimID: " << victimID << "\n";
    std::cout << "VictimType: " << victimType << "\n";
    std::cout << "VictimAge: " << victimAge << "\n";
    std::cout << "VictimSex: " << victimSex << "\n\n";
    
    //Print offense data
    std::cout << "OffenseID: " << offenseID << "\n";
    std::cout << "OffenseType: " << offenseType << "\n\n";
    
    //Print bias data
    std::cout << "BiasNum: " << biasNum << "\n";
    std::cout << "BiasString: " << biasString << "\n\n";
    
    //Print relationship
    std::cout << "RelationshipNum: " << relationshipNum << "\n";
    std::cout << "RelationshipString: " << relationshipString << "\n\n";
    
}

bool Incident::operator==(const Incident& other) const {
    
    if(victimID == other.victimID && offenseID == other.offenseID){
        return true;
    }else{
        return false;
    }
    
}

bool Incident::operator>(const int compare) const {
    
    //Count features with valid values
    int featureCount = 0;
    if(offenseID > 0){
        featureCount++;
    }
    
    if(offenseType > 0){
        featureCount++;
    }
    
    //Victim
    if(victimID > 0){
        featureCount++;
    }
    
    if(victimType > 0){
        featureCount++;
    }
    
    if(victimAge > 0){
        featureCount++;
    }
    if(victimSex != ""){
        featureCount++;
    }
    
    //Relationship
    if(relationshipNum > 0.0f){
        featureCount++;
    }
    if(relationshipString != ""){
        featureCount++;
    }
    
    //Bias
    if(biasNum > 0){
        featureCount++;
    }
    if(biasString != ""){
        featureCount++;
    }
    
    //Compare valid features to int
    if(featureCount > compare){
    
        return true;
    }else{
        return false;
    }
    
}
