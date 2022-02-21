/*
  ==============================================================================

    EarlyReflections.h
    Created: 31 Mar 2021 11:19:49pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class EarlyReflections {
    
public:
    EarlyReflections();
    
    void setSampleRate(float newFs);
    
    void setDelayTimeSamples();
    void setGain();
    
    void createIndex();
    
    float processSample(float x, int chan);
    
private:
    float Fs = 48000.f;
    
    float buf[48000][2] = {0.f};
    float bufferLength = 48000.f;
    
    int wIndex[2] = {48000};
    int rIndex[19][2] = {(int)48000.f};
    
    float delayTimeSamples[19];
    float gain[19];
    
};
