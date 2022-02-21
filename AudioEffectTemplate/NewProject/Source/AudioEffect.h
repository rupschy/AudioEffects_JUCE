/*
  ==============================================================================

    AudioEffect.h
    Created: 25 Feb 2021 2:46:01pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once


// Base class for general audio effect

class AudioEffect{
    
public:
    
    virtual float processSample(float x) = 0; // pure virtual- virtual without an implementation
    
    void prepare(float newFs);
    
protected:
    // Accessible in AudioEffect and derived classes
    // if needed in specialized audio effect, can be utilized as a protected variable
    float Fs;
    
private:
    // only accessible in AudioEffect
    
};
