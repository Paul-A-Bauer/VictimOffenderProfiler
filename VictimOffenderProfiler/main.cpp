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
    std::string menuString = "\n\n\n\nSelect action\n 1. Load Raw Data\n 2. Clean Data and generate vectors\n 3. Output vectors\n 4. Load pre cleaned vectors\n 5. Train using sigmoid\n Enter -1 to Quit\n";
    
    //menu loop
    while(input > -1) {
        //print menu options
        std::cout << menuString;
        
        //Get input
        if(!(std::cin >> input)){
            std::cin.clear ();
            std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
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
                    std::cout << "Enter the file name with full path and extension\n";
                    std::cin >> path;
                    
                    //Clear the cin buffer
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    //Load pre cleaned data from a csv file
                    dh.LoadIncidentVectors(path);
                    
                    
                    break;
                }
                case 5:{
                    //Get desired training set size
                    std::cout << "How many data points would you like to use for training?\n";
                    
                    int trainSet;
                    std::cin >> trainSet;
                    
                    //Get desired training epochs
                    std::cout << "How many training epochs would you like to complete?\n";
                    
                    int trainingEpochs;
                    std::cin >> trainingEpochs;
                    
                    //Execute training
                    dh.TrainModelS(trainSet, trainingEpochs);
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
