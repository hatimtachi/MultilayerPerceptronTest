//
//  readFile.h
//  perceptronMultiCoucheTestWeights
//
//  Created by hatim tachi on 27/02/2018.
//  Copyright © 2018 hatim tachi. All rights reserved.
//

#ifndef readFile_h
#define readFile_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NeuronStructure.h"


int     getLengthFile       (char* fileName);

int     getBuffer           (char* fileName);

int     getWidthFile        (char *fileName);

void    getConfigurationFile(char *fileName, int *numberOfInputNeurons, int *numberOfHiddenAndOutputNeurons,
                          int *lengthOfOutput,int *vectornumberOfNeuronsPerLayer);

void    getDataFromFile     (char* fileName, Data *inputData, Data *outputData,
                             int numberOfInputNeurons, int lengthOfOutput);

#endif /* readFile_h */
