//
//  main.c
//  perceptronMultiCoucheTestWeights
//
//  Created by hatim tachi on 27/02/2018.
//  Copyright © 2018 hatim tachi. All rights reserved.
//

#include <stdio.h>
#include "NeuronStructure.h"
#include "readFile.h"
#include "NeuronConfiguration.h"
#define FILENAME_CONFIGURATION "Configuration.txt"
#define FILENAME_TEST "Test.txt"
#define FILENAME_WEIGHTS "Weights.txt"

int main(void) {
 
    /***************************************** Parametre ***************************************************************/

    int numberOfInputNeurons            = 0;
    int numberOfHiddenAndOutputNeurons  = 0;
    int lengthOfOutput                  = 0;
    int lengthDataTest                  = getLengthFile(FILENAME_TEST);
    Data *inputDataTest                 = malloc(lengthDataTest * sizeof(Data));
    Data *outputDataTest                = malloc(lengthDataTest * sizeof(Data));

    int vectornumberOfNeuronsPerLayer[getWidthFile(FILENAME_CONFIGURATION) - 1];

    getConfigurationFile(FILENAME_CONFIGURATION, &numberOfInputNeurons, &numberOfHiddenAndOutputNeurons, &lengthOfOutput,vectornumberOfNeuronsPerLayer);
    getDataFromFile(FILENAME_TEST, inputDataTest, outputDataTest, numberOfInputNeurons,lengthOfOutput);
    
    
    layer layerOfNeuronNetwork;
    inputNeuron *inputNeuronNetwork = calloc(numberOfInputNeurons, sizeof(inputNeuron));
    layerOfNeuronNetwork.layer      = calloc(numberOfHiddenAndOutputNeurons, sizeof(hiddenAndOutputNeuron*));
    
    if (layerOfNeuronNetwork.layer != NULL) {
        
        for (int i = 0; i < numberOfHiddenAndOutputNeurons; i++) {
            
            layerOfNeuronNetwork.layer[i] = calloc(vectornumberOfNeuronsPerLayer[i], sizeof(hiddenAndOutputNeuron));
            
        }
    }
    
    /***************************************** Configuration du reseau ***************************************************/
    
    configurationLayers(numberOfHiddenAndOutputNeurons, numberOfInputNeurons, vectornumberOfNeuronsPerLayer, &layerOfNeuronNetwork);
    networkInitialization(FILENAME_WEIGHTS, numberOfInputNeurons, numberOfHiddenAndOutputNeurons, lengthOfOutput, vectornumberOfNeuronsPerLayer, &layerOfNeuronNetwork);
    
    /******************************************** Test *************************************************************/
    
    double vectorExpected[lengthDataTest];
    
    for (int i = 0; i < lengthDataTest; i++) {
        vectorExpected[i] = outputDataTest[i].vector[0];
    }    

    testTraining(lengthDataTest, numberOfHiddenAndOutputNeurons, numberOfInputNeurons, vectornumberOfNeuronsPerLayer, inputNeuronNetwork, inputDataTest, &layerOfNeuronNetwork,vectorExpected);
    

    free(inputDataTest);
    free(outputDataTest);
    free(inputNeuronNetwork);
    
    return 0;
}



