/*
  ==============================================================================

    AmpModulation.h
    Created: 9 Feb 2021 2:50:52pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AmpModulation{
public:
    
    AmpModulation(); // We make our own constructor
    AmpModulation(float newRate, float newDepth);
    
    float processSample(float x, int c);
    
    void prepare(float newFs);
    
    void setRate(float newRate);
    void setDepth(float newDepth);
    
    
    
    
private:
    float Fs = 48000.f;
    float Ts = 1.f/Fs;
    
    float rate = 1.f;
    float depth = 100.f;
    
    float angleChange = 0.f;
    float amp = 0.5f;
    float dc = 0.5f;
    
    float currentAngle[2] = {0.f};
    // initializing both channels to
    const float pi2 = 2.f * M_PI;
    
    
    
};
