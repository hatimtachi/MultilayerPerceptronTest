//
//  NeuronConfiguration.h
//  perceptronMultiCoucheTestWeights
//
//  Created by hatim tachi on 28/02/2018.
//  Copyright © 2018 hatim tachi. All rights reserved.
//

#ifndef NeuronConfiguration_h
#define NeuronConfiguration_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "NeuronStructure.h"
#include "readFile.h"


void    configurationLayers             (int numberOfHiddenAndOutputNeurons,int numberOfInputNeurons,
                                        int *vectornumberOfNeuronsPerLayer,layer *layerOfNeuronNetwork);


void    networkInitialization           (char* fileName,int numberOfInputNeurons,int numberOfHiddenAndOutputNeurons,
                                         int lengthOfOutput,int *vectornumberOfNeuronsPerLayer,layer *layerOfNeuronNetwork);


void    displaysTheNeuralNetwork        (int *vectorOfNumberOfNeuronsPerLayer,int numberOfInputNeurons
                                         ,int numberOfHiddenAndOutputNeurons ,inputNeuron *inputNeuronNetwork
                                         ,layer *layerOfNeuronNetwork);


//void    testTraining                    (int lengthDataTest,int numberOfHiddenAndOutputNeurons,int numberOfInputNeurons,
  //                                       int *vectornumberOfNeuronsPerLayer,inputNeuron *inputNeuronNetwork,
    //                                     Data *inputDataTest,layer *layerOfNeuronNetwork);
void    testTraining                    (int lengthDataTest,int numberOfHiddenAndOutputNeurons,int numberOfInputNeurons,
                                        int *vectornumberOfNeuronsPerLayer,inputNeuron *inputNeuronNetwork,
                                        Data *inputDataTest,layer *layerOfNeuronNetwork,double *vectorExpected);

void    displaysTheNeuralNetworkTest    (int *vectorOfNumberOfNeuronsPerLayer,int numberOfInputNeurons ,
                                         int numberOfHiddenAndOutputNeurons ,inputNeuron *inputNeuronNetwork ,
                                         layer *layerOfNeuronNetwork);

bool    propagationInNetwork            (int numberOfHiddenAndOutputNeurons,int *vectornumberOfNeuronsPerLayer,inputNeuron *inputNeuronNetwork, 
                                        layer *layerOfNeuronNetwork,double valueExpected,double *outputValue);
                                          
//void    propagationInNetwork            (int numberOfHiddenAndOutputNeurons,int *vectornumberOfNeuronsPerLayer,
  //                                       inputNeuron *inputNeuronNetwork, layer *layerOfNeuronNetwork);

double tangenteHyperbolique             (double value);

#endif /* NeuronConfiguration_h */
