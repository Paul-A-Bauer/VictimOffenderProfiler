//
//  main.cpp
//  VictimOffenderProfiler
//
//  Created by Paul Bauer on 4/9/22.
//

#include <iostream>
#include <vector>
#include "Incident.hpp"
#include "VOPDataHandler.hpp"

int main(int argc, const char * argv[]) {
    
    // Create data handler
    VOPDataHandler dh = VOPDataHandler();
    dh.LoadRawData();
    
    return 0;
}
