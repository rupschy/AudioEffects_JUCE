/*
  ==============================================================================

    Gain.cpp
    Created: 25 Feb 2021 2:46:07pm
    Author:  John Rupsch

  ==============================================================================
*/
#pragma once

#include "Gain.h"
#include "AudioEffect.h"

// Derived class from AudioEffect

// syntax states Gain is a special version of AudioEffect
// declarations in AudioEffect available for Gain
// Add more specifics

float Gain::processSample(float x){
    return x * gain;
}
    
void Gain::setGainValue(float newGain){
    gain = newGain;
}
