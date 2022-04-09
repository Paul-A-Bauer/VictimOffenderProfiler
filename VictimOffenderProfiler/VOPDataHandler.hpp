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

#include "rapidcsv.h"
#include "Incident.hpp"


class VOPDataHandler {
    
    //incident objects
    std::vector<Incident*> incidents;
    
public:
    //Load data from files
    void LoadRawData();
    
    //Load data from offense files
    void LoadOffenseData();
    
};

#endif /* VOPDataHandler_hpp */
