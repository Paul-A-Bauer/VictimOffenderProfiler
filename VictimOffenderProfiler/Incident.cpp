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
//    if(offenseID > 0){
//        featureCount++;
//    }else{
//        std::cout << "missing offenseID\n";
//    }
    
    if(offenseType > -1){
        featureCount++;
    }else{
        std::cout << "missing offenseType\n";
    }
    
    //Victim
//    if(victimID > 0){
//        featureCount++;
//    }else{
//        std::cout << "missing victimID\n";
//    }
    
    if(victimType > -1){
        featureCount++;
    }else{
        std::cout << "missing victimType\n";
    }
    
    if(victimAge > -1){
        featureCount++;
    }else{
        std::cout << "missing victimAge\n";
    }
    
    if(victimSex != ""){
        featureCount++;
    }else{
        std::cout << "missing victimSex\n";
    }
    
    //Relationship
    if(relationshipNum > -1.0f){
        featureCount++;
    }else{
        std::cout << "missing relationshipNum\n";
    }
    
//    if(relationshipString != ""){
//        featureCount++;
//    }else{
//        std::cout << "missing relationshipString\n";
//    }
    
    //Bias
    if(biasNum > -1){
        featureCount++;
    }else{
        std::cout << "missing biasNum\n";
    }
    
//    if(biasString != ""){
//        featureCount++;
//    }else{
//        std::cout << "missing biasString\n";
//    }
    
    //Compare valid features to int
    if(featureCount > compare){
    
        return true;
    }else{
        std::cout << "Only has " << featureCount << " features\n";
        return false;
    }
    
}

std::vector<float> Incident::GetIncidentVector(){
    
    //Convert all features to float values
    float offenseTypeF = static_cast<float>(offenseType);
    float victimTypeF = static_cast<float>(victimType);
    float victimAgeF = static_cast<float>(victimAge);
    float victimSexF = (victimSex != "F" ? 0.5f : 1.0f);
    float biasNumF = static_cast<float>(biasNum);
    
    //Return as a vector of floats
    return std::vector<float>({offenseTypeF, victimTypeF, victimAgeF, victimSexF, biasNumF, relationshipNum});
}
