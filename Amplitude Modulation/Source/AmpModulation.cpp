/*
  ==============================================================================

    AmpModulation.cpp
    Created: 9 Feb 2021 2:50:52pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "AmpModulation.h"

AmpModulation::AmpModulation(){
    
    // Initializing effect to these values
    rate = 2.f;
    depth = 50.f;
    
    setRate(rate);
    setDepth(depth);
}

AmpModulation::AmpModulation(float newRate, float newDepth){
    rate = newRate;
    depth = newDepth;
    setRate(rate);
    setDepth(depth);
    
}




float AmpModulation::processSample(float x, int c){
    float lfo = amp * sin(currentAngle[c]) + dc;
    
    float y = x * lfo;
    
    currentAngle[c] += angleChange;
    if ( currentAngle[c] > pi2){
        currentAngle[c] -= pi2;
    }
    
    return y;
}

void AmpModulation::prepare(float newFs){
    Fs = newFs;
}

void AmpModulation::setRate(float newRate){
    rate = newRate; //Hz
    
    // Determine angle change
    angleChange = rate * pi2 / Fs;
}

void AmpModulation::setDepth(float newDepth){
    depth = newDepth; // [0-100%]
    
    //Determine amp + dc offset of sine wave
    amp = depth / 200.f;
    dc = 1.f - amp;
}
