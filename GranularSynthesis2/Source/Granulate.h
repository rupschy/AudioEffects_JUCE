/*
  ==============================================================================

    Granulate.h
    Created: 25 Feb 2021 2:18:21pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>



class Granulate{
public:

    //Constructor
    Granulate();
    
    
    void prepare(float newFs);
    
    void setGrainSize(int newGrainSize);

    float setInputMatrix(float x, int channel);
    
    void setPermParameters(int grainSize);
    
    void setPermutationSet(int grainSize);

//    void arrangeOutputGrains();

    float outputArray(int channel);
    
    
    

private:
    
    
    float Fs = 48000.f;
    
    static const int inputArrayLength = 262144;
    static const int outputArrayLength = 2*inputArrayLength;

    int grainSize = 1024; // choices: 64 128 256 512 1024 2048 4096 8192

    const static int matrixR = 256;
    int indexR = 0; // grain number
    const static int matrixC = 1024;
    int indexC = 0; // grain length
    
    int framesIn;
    int framesOut;
    
    float inputMatrix[matrixC][matrixR][2] = {0.f};
    int outputArrayIndex[512] = {0};
    

};
