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
    
    //Input
    int input = 0;
    
    //Menu string
    std::string menuString = "\n\n\n\nSelect action\n 1. Load Raw Data\n 2. Clean Data and generate vectors\n 3. Output vectors\n 4. Load pre cleaned vectors\n Enter -1 to Quit\n";
    
    //menu loop
    while(input > -1) {
        //print menu options
        std::cout << menuString;
        
        //Get input
        if(!(std::cin >> input)){
            std::cin.clear ();
            std::cin.ignore (256);
        }
        else{
            
            //Execute selected action
            switch (input) {
                case 1:{
                    //Load data from files
                    dh.LoadRawData();
                    break;
                }
                case 2:{
                    //Clean the data
                    dh.CleanData();
                    break;
                }
                case 3:{
                    //Output data to csv file
                    dh.OutputIncidentVectors();
                    break;
                }
                case 4:{
                    //Get file path for pre cleaned data
                    std::string path;
                    std::cin >> path;
                    //Load pre cleaned data from a csv file
                    dh.LoadIncidentVectors(path);
                    break;
                }
                default:{
                    break;
                }
            }
        }
        //Reset input
        //input = 0;
    }
    
    return 0;
}
