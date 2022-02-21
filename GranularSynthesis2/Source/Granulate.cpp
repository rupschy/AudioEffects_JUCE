/*
  ==============================================================================

    Granulate.cpp
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/
#include "Granulate.h"
#include <iostream>

using namespace std;

// Constructor
Granulate::Granulate(){}


void Granulate::prepare(float newFs){
    Fs = newFs;
}

void Granulate::setGrainSize(int newGrainSize){
    grainSize = newGrainSize;
    
//    setPermParameters(grainSize);
}

void Granulate::setPermParameters(int grainSize){
    int simpleNumInputFrames = floor(inputArrayLength/grainSize);
    int simpleFramesOut = floor(outputArrayLength/grainSize);
    
    int outputArrayIndex[512] = {0};
    if (sizeof(outputArrayIndex) != simpleFramesOut){
        int g = simpleFramesOut;
        outputArrayIndex[g] = {0};
    }
    
    for (int n = 0; n < simpleFramesOut; n++){
        outputArrayIndex[n] = n;
    }
    
    if (simpleNumInputFrames != matrixR){
        simpleNumInputFrames = floor(inputArrayLength/grainSize);
    }
}


float Granulate::setInputMatrix(float x, int channel){

    inputMatrix[indexC][indexR][channel] = x;
    indexR++;
    if (indexR >= matrixR){
        // grain is finished, go to next one.
        indexR = 0;
        indexC++;
    }
    if (indexC >= matrixC){
        indexC = 0;
    }
    return inputMatrix[indexC][indexR][channel];
}




void Granulate::setPermutationSet(int grainSize){

    int simpleNumInputFrames = floor(inputArrayLength/grainSize);
    int simpleFramesOut = floor(outputArrayLength/grainSize);
    
    int outputArrayIndex[512] = {0};
    if (sizeof(outputArrayIndex) != simpleFramesOut){
        int g = simpleFramesOut;
        outputArrayIndex[g] = {0};
    }
    
    int frameDif = abs((int(simpleFramesOut)-(int)simpleNumInputFrames));
    for (int i = 0; i < simpleFramesOut; i++){
        outputArrayIndex[i] = i;
    }
//    Randomization of values within the scale from 0 -> outFrames
    int sizePerm = sizeof(outputArrayIndex)/sizeof(outputArrayIndex[0]);
    std::random_shuffle(outputArrayIndex,outputArrayIndex+sizePerm);
    
//    Change array from 0 -> outFrames to 0 -> numInputFrames
    for (int j = 0; j < simpleFramesOut; j++){
        if (outputArrayIndex[j] > simpleNumInputFrames - 1){
            outputArrayIndex[j] = abs(outputArrayIndex[j] - frameDif);
            if (outputArrayIndex[j] <= -1){
                outputArrayIndex[j] = 0;
            }
        if (outputArrayIndex[j] >= frameDif){
            outputArrayIndex[j] = frameDif - outputArrayIndex[j];
        }
        }
        else {
            outputArrayIndex[j] = outputArrayIndex[j];
        }
    }
    
}

float Granulate::outputArray(int channel){
   float x = inputMatrix[outputArrayIndex[indexC]][indexR][channel];
   indexR++;
//   outIndex++;
   if (indexR >=matrixR){
       indexR = 0;
       // switch to another grain and output those samples
       indexC++;
   }
   if (indexC >= matrixC){
       indexC = 0;
   }

   return x;


}
