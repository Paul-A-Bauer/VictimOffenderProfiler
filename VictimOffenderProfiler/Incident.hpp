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
#include <algorithm>

class Incident {
    
public:
    //Offense
    int offenseID = -1;
    int offenseType = -1;
    
    //Victim
    int victimID = -1;
    int victimType = -1;
    int victimAge = -1;
    std::string victimSex;
    
    //Relationship
    float relationshipNum = -1.0f;
    std::string relationshipString;
    
    //Bias
    int biasNum = -1;
    std::string biasString;
    
    //Vector reprisentation of the incident to be used in training and prediction
    std::vector<float> GetIncidentVector();
    
    //Constructor
    Incident();
    
    //List contents of this incident
    void ListContents();
    
    //Compare incidents based on victim id
    bool operator==(const Incident& other) const;
    
    //Compare incident to int based on how many features have data
    bool operator>(const int compare) const;
};

#endif /* Incident_hpp */
