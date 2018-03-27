//
//  NeuronConfiguration.c
//  perceptronMultiCoucheTestWeights
//
//  Created by hatim tachi on 28/02/2018.
//  Copyright © 2018 hatim tachi. All rights reserved.
//

#include "NeuronConfiguration.h"


void configurationLayers(int numberOfHiddenAndOutputNeurons,int numberOfInputNeurons,int *vectornumberOfNeuronsPerLayer,layer *layerOfNeuronNetwork){
    
    for (int i = 0; i < numberOfHiddenAndOutputNeurons; i++) {
        for (int j = 0; j < vectornumberOfNeuronsPerLayer[i]; j++) {
            
            layerOfNeuronNetwork->layer[i][j].number = vectornumberOfNeuronsPerLayer[i];
            
            if (i == 0) {
                
                layerOfNeuronNetwork->layer[i][j].weights           = calloc(numberOfInputNeurons, sizeof(double));
                layerOfNeuronNetwork->layer[i][j].oldWeights        = calloc(numberOfInputNeurons, sizeof(double));
                layerOfNeuronNetwork->layer[i][j].lenghtOfWeights   = numberOfInputNeurons;
                
            }else{
                
                layerOfNeuronNetwork->layer[i][j].weights           = calloc(vectornumberOfNeuronsPerLayer[i - 1], sizeof(double));
                layerOfNeuronNetwork->layer[i][j].oldWeights        = calloc(vectornumberOfNeuronsPerLayer[i - 1], sizeof(double));
                layerOfNeuronNetwork->layer[i][j].lenghtOfWeights   = vectornumberOfNeuronsPerLayer[i - 1];
            }
            
        }
    }
}

/*********************************************************************************************/

void networkInitialization(char* fileName,int numberOfInputNeurons,int numberOfHiddenAndOutputNeurons,int lengthOfOutput,int *vectornumberOfNeuronsPerLayer,layer *layerOfNeuronNetwork){
    
    FILE* file = fopen(fileName, "r");
    char line[getBuffer(fileName)];
    char *token;
    const char specialC[2]  = ",";
    
    
    for (int i = 0; i < numberOfHiddenAndOutputNeurons; i++) {
        
        fgets(line ,getBuffer(fileName) * sizeof(char) ,file);
        token = strtok(line,specialC);
        
        while (token != NULL) {
            
            for (int j = 0; j < vectornumberOfNeuronsPerLayer[i]; j++) {
                for (int w = 0; w < layerOfNeuronNetwork->layer[i][j].lenghtOfWeights; w++) {

                    double x = strtod(token, NULL);

                    layerOfNeuronNetwork->layer[i][j].weights[w] = x;
                    layerOfNeuronNetwork->layer[i][j].oldWeights[w] = layerOfNeuronNetwork->layer[i][j].weights[w];

                    token = strtok(NULL, specialC);

                }
            }
        }
    }
}

/*********************************************************************************************/

bool propagationInNetwork(int numberOfHiddenAndOutputNeurons,int *vectornumberOfNeuronsPerLayer,inputNeuron *inputNeuronNetwork, layer *layerOfNeuronNetwork,double valueExpected,double *outputValue){
    //double errorV = 0.15;
    FILE *fileOutError = fopen("./errors.txt","a");        
    
    for (int i = 0; i < numberOfHiddenAndOutputNeurons; i++) {
        for (int j = 0; j < vectornumberOfNeuronsPerLayer[i]; j++) {
            
            layerOfNeuronNetwork->layer[i][j].value = 0;
            if (i == 0) {
                for (int k = 0; k < layerOfNeuronNetwork->layer[i][j].lenghtOfWeights; k++) {
                    layerOfNeuronNetwork->layer[i][j].value +=
                    layerOfNeuronNetwork->layer[i][j].weights[k] * inputNeuronNetwork[k].value;
                    
                }
            }else{
                
                for (int k = 0; k < layerOfNeuronNetwork->layer[i][j].lenghtOfWeights; k++) {
                    
                    layerOfNeuronNetwork->layer[i][j].value +=
                    layerOfNeuronNetwork->layer[i][j].weights[k] * layerOfNeuronNetwork->layer[i - 1][k].value;
                }
            }
            
            layerOfNeuronNetwork->layer[i][j].value = tangenteHyperbolique(layerOfNeuronNetwork->layer[i][j].value);
            *outputValue = layerOfNeuronNetwork->layer[i][j].value;

           /***  Test Error ***/
            if(i == numberOfHiddenAndOutputNeurons - 1){    
                if(layerOfNeuronNetwork->layer[i][j].value > 0.9){
                    if(valueExpected != 1){

                        for (int k = 0; k < layerOfNeuronNetwork->layer[0][j].lenghtOfWeights; k++) {
                            
                            fprintf(fileOutError,"%d,",(int)(inputNeuronNetwork[k].value));
                            printf(" %lf ",inputNeuronNetwork[k].value);
                            
                        }                    
                        fprintf(fileOutError,"%d,%lf\n",(int)(valueExpected),layerOfNeuronNetwork->layer[i][j].value);                                                
                        printf("\n --> %lf | %lf\n\n ; ",layerOfNeuronNetwork->layer[i][j].value,valueExpected);
                        fclose(fileOutError);                        
                        return true;   
                    }
                }else{
                    if(valueExpected == 1){
                        for (int k = 0; k < layerOfNeuronNetwork->layer[0][j].lenghtOfWeights; k++) {
                            
                            fprintf(fileOutError,"%d,",(int)(inputNeuronNetwork[k].value));                            
                            printf(" %lf ",inputNeuronNetwork[k].value);

                        }            

                        fprintf(fileOutError,"%d,%lf\n",(int)(valueExpected),layerOfNeuronNetwork->layer[i][j].value);                                                
                        printf("\n --> %lf | %lf\n\n ; ",layerOfNeuronNetwork->layer[i][j].value,valueExpected);
                        fclose(fileOutError);
                        return true;   
                    }
                }
            }
        }
    }
    fclose(fileOutError);
    return false;
}

/*********************************************************************************************/

void testTraining(int lengthDataTest,int numberOfHiddenAndOutputNeurons,int numberOfInputNeurons,int *vectornumberOfNeuronsPerLayer,inputNeuron *inputNeuronNetwork,Data *inputDataTest,layer *layerOfNeuronNetwork,double *vectorExpected){
    
    int count = 0;
    bool countBool = false;
    double errorQuadratique = .0;
    double outputValue = .0;
    for (int i = 0; i < lengthDataTest; i++) {
        
        for (int j = 0; j < numberOfInputNeurons; j++) {
            
            inputNeuronNetwork[j].value = inputDataTest[i].vector[j];
        
        }
        
        countBool =  propagationInNetwork(numberOfHiddenAndOutputNeurons, vectornumberOfNeuronsPerLayer, inputNeuronNetwork,
                             layerOfNeuronNetwork,vectorExpected[i],&outputValue);
        if(countBool){
            count++;
            countBool = false;
        }        
        errorQuadratique += pow(vectorExpected[i] - outputValue ,2);
        outputValue = 0;        
    }
    errorQuadratique = sqrt(errorQuadratique); 
    errorQuadratique = (double) (errorQuadratique/ lengthDataTest);
    printf("\nnb error ->  %d \n",count);        
    printf("error quadratique : %lf \n",errorQuadratique);
}

/*********************************************************************************************/

double tangenteHyperbolique(double value){
    return tanh(value);
}

/*********************************************************************************************/

void displaysTheNeuralNetworkTest(int *vectorOfNumberOfNeuronsPerLayer,int numberOfInputNeurons ,int numberOfHiddenAndOutputNeurons ,inputNeuron *inputNeuronNetwork ,layer *layerOfNeuronNetwork){
    printf("input values :\n\n");
    for (int i = 0; i < numberOfInputNeurons; i++) {
        printf("\t %lf ",inputNeuronNetwork[i].value);
    }
    
    for (int i = 0; i < numberOfHiddenAndOutputNeurons; i++) {
        if (i == numberOfHiddenAndOutputNeurons - 1) {
            printf("output ::\n\n");
            for (int j = 0; j < vectorOfNumberOfNeuronsPerLayer[i]; j++) {
                
                printf("neuron value is : %lf \n",layerOfNeuronNetwork->layer[i][j].value);
                
            }
        }
        printf("\n******************\n");
    }
}



/*********************************************************************************************/

void displaysTheNeuralNetwork(int *vectorOfNumberOfNeuronsPerLayer,int numberOfInputNeurons ,int numberOfHiddenAndOutputNeurons ,inputNeuron *inputNeuronNetwork ,layer *layerOfNeuronNetwork){
    printf("input values :\n\n");
    for (int i = 0; i < numberOfInputNeurons; i++) {
        printf("\t %lf ",inputNeuronNetwork[i].value);
    }
    printf("\n*****************\n");
    
    for (int i = 0; i < numberOfHiddenAndOutputNeurons; i++) {
        if (i == numberOfHiddenAndOutputNeurons - 1) {
            printf("output ::\n\n");
        }else{
            printf("layer :: %d ::\n\n",i);
        }
        for (int j = 0; j < vectorOfNumberOfNeuronsPerLayer[i]; j++) {
            
            printf("number of neuron in this layer : %d && size of weights is %d && value is : %lf \n\n",layerOfNeuronNetwork->layer[i][j].number,layerOfNeuronNetwork->layer[i][j].lenghtOfWeights,layerOfNeuronNetwork->layer[i][j].value);
            printf("weights values is :\n");
            for (int k = 0; k < layerOfNeuronNetwork->layer[i][j].lenghtOfWeights; k++) {
                printf("\t %lf ",layerOfNeuronNetwork->layer[i][j].weights[k]);
            }
            printf("\nold weights values is :\n");
            for (int k = 0; k < layerOfNeuronNetwork->layer[i][j].lenghtOfWeights; k++) {
                printf("\t %lf ",layerOfNeuronNetwork->layer[i][j].oldWeights[k]);
            }
            printf("\n\n");
        }
        printf("\n******************\n");
    }
}








