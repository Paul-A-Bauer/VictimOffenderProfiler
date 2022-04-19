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
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <math.h>
#include <limits>

#include "Incident.hpp"


class VOPDataHandler {
    
    //incident objects
    std::vector<Incident*> incidents;
    
    //Set path for data folder
    std::string dataInPath = "/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/RawSource/";
    
    std::string dataOutPath = "/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/Output/";
    
    std::string dataCleanedPath = "/Users/paulbauer/Documents/Classes/Spring 2022/ML/TermProject/ProjectSource/VictimOffenderProfiler/VictimOffenderProfiler/Data/CleanInput/";
    
    //Store lists of relationship type strings and numeric id's
    std::map<int, std::string> relationshipTypeStrings;
    std::map<int, int> relationshipTypeNums;
    
    //Store lists of bias type strings and numeric id's
    std::map<int, std::string> biasTypeStrings;
    std::map<int, int> biasTypeNums;
    
    //Incident vectors X
    std::vector<std::vector<float>> incidentVectors;
    
    //Weights W
    std::vector<float> w = {0.2, 0.2, 0.2, 0.2, 0.2};
    
    //Learning rate
    float lr = 0.01;
    
    //Eulers number
    float e = 2.71828;
    
public:
    
    //Load data from files
    void LoadRawData();
    
    //Load data from offense files
    void LoadOffenseData(int limit = 10000);
    
    //Load data from victim files
    void LoadVictimData();
    
    //Load victim/offender relationship data
    void LoadVictimOffenderRealtionshipData();
    
    //Load bias data
    void LoadBiasData();
    
    //-----------------------Cleaning functions----------------------------------
    
    //Clean data
    void CleanData();
    
    //Remove duplicate entries
    void RemovedDuplicates();
    
    //Remove entries with missing features
    void RemoveIncompleteRecords();
    
    //Convert input features to float values and generate incident vectors
    void GenerateIncidentVectors();
    
    //Output data as csv
    void OutputIncidentVectors();
    
    //Load precleaned incident data from .csv
    void LoadIncidentVectors(std::string inputPath);
    
    //---------------------Learning functions-------------------------
    
    //Sigmoid logistic function
    float Sigmoid(float s);
    
    //Hyperbolic tangent (alternative)
    float Tanh(float s);
    
    //Ein
    float GetEin();
    
    //Eout
    float GetEout();
    
    //Predict
    float PredictProbabilityS(std::vector<float> dataPoint);
    
    //Predict with alernative activation
    float PredictProbabilityTH(std::vector<float> dataPoint);
    
    //Update weights
    void UpdateWeights(float predicted, float recorded, std::vector<float> inputs);
    
    //Train the weights on a specified number of rows using the sigmoid activation
    void TrainModelS(int trainingSet, int epoch);
    
    //Train the weights on a specified number of rows using the Tanh activation
    void TrainModelTH(int trainingSet, int epoch);
};

#endif /* VOPDataHandler_hpp */
