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
