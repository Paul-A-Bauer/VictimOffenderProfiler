//
//  Incident.hpp
//  VictimOffenderProfiler
//
//  Created by Paul Bauer on 4/9/22.
//

#ifndef Incident_hpp
#define Incident_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

class Incident {
    
public:
    //Offense
    int offenseID = 0;
    int offenseType = 0;
    
    //Victim
    int victimID = 0;
    int victimType = 0;
    int victimAge = 0;
    std::string victimSex;
    
    //Relationship
    float relationshipNum = 0.0f;
    std::string relationshipString;
    
    //Bias
    int biasNum = 0;
    std::string biasString;
    
    //Vector reprisentation of the incident to be used in training and prediction
    std::vector<float> incidentVector;
    
    //Constructor
    Incident();
    
    //List contents of this incident
    void ListContents();
};

#endif /* Incident_hpp */
