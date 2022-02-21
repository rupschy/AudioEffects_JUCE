/*
  ==============================================================================

    Gain.h
    Created: 25 Feb 2021 2:46:07pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

#include "AudioEffect.h"





//Derived from AudioEffect

// When using inheritance like this, most times you'll use public
class Gain : public AudioEffect

// if changed to private, all derived variables are changed to being private from what they were in AudioEffect
{
public:
    
    // From AudioEffect we have:
    // processSample
    // prepare
    
    float processSample(float x) override;
    
    void setGainValue(float newGain);
    
private:
    float gain = 1.f;
    
    // from AudioEffect we have:
    // Fs
};
