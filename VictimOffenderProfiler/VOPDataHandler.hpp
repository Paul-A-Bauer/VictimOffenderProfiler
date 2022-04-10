//
//  VOPDataHandler.hpp
//  VictimOffenderProfiler
//
//  Created by Paul Bauer on 4/9/22.
//

#ifndef VOPDataHandler_hpp
#define VOPDataHandler_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

#include "Incident.hpp"


class VOPDataHandler {
    
    //incident objects
    std::vector<Incident*> incidents;
    
    //Set path for data folder
    std::string dataInPath = "/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/RawSource/";
    
    std::string dataOutPath = "/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/Output/";
    
    std::string dataCleanedPath = "/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/CleanInput/";
    
public:
    //Load data from files
    void LoadRawData();
    
    //Load data from offense files
    void LoadOffenseData(int limit = 10000);
    
    //Load data from victim files
    void LoadVictimData();
    
    //Load victim/offender relationship data
    void LoadVictimOffenderRealtionshipData();
    
};

#endif /* VOPDataHandler_hpp */
