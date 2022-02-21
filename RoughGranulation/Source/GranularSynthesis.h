/*
  ==============================================================================

    GranularSynthesis.h
    Created: 24 Feb 2021 4:44:45pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class Granulate{
    
public:
    
    // Constructor
    Granulate();
    
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    void setDelayMS(float newDelayMS);
    
    void generateMatrix();
    // creates matrix of grains dependent on output length and grain length requested
    // also windows each grain
    // uses window functions, loops, round
    // Output is: matrix(grainSize,lenIn/grainSize) and numframes
    
    void permutationOrder();
    // creates new order of grains
    // also finds amt of overlapped grains to output the needed output length
    // uses abs, randperm, loops, bool
    // Output is: permutation(randperm(framesOut))' and framesOut integer
    
    void movingAverageFilter();
    // generates a matrix for each envelope created by movingAverage function
    // Uses conjugate, sqrt, elementwise mult, indexing, loop, sum
    // Output is: matrix(same size as grainMatrix)
    
    void permMatrices();
    // generates 3-dimensional matrices for frequency based processing
    // also generates time-based 2-dimensional matrices
    // uses loops, index, elementwise mult, real, istft
    // Output is: 3D matrix(nfft,mfft,numframes) and 2D matrix(same size as grainMatrix
    
    void outputMatrix();
    // generates matrix of values for initializing output
    // makes real-time possible as stored values are here for all needed time/grains
    // uses loops, indexing, elementwise mult
    // Output is: 2D matrix(size of grainMatrix)
    
    void outputArray();
    // creates final output with normalization from outputMatrix
    // uses indexing, loops, initialization, max, abs
    // Output is: array
    
                  
private:
                  
    float Fs = 48000.f;
    
    int outLengthTime = 10; // in seconds
    
    float delayMS = 24000.f;
    
    float outLengthSamples = round(Fs*outLengthTime);
    
    
    // float w[2][192000] = {0.f}; //needs braces for array based initialization
    float w[2][192000] = {0.f}; //needs braces for array based initialization
    // read/write pointer for array w
    int index[2] = {0};
    int writeIndex[2] = {47999}; //start at the end area
    int delayIndex[2] = {47999 - delaySamples}; // dependent on delaySample
    
};

