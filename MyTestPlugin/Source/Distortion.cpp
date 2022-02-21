/*
  ==============================================================================

    Distortion.cpp
    Created: 4 Feb 2021 2:28:39pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "Distortion.h"
#include <JuceHeader.h>

float Distortion::processSample(float x){
    
    // A way to smooth parameters
    // if calculating filter coefficients, would not want to do this within every samp loop
    smoothDrive = alpha * smoothDrive + (1.f-alpha) * drive; // weights should add up to 1.0f
    
    
    float y = (2.f/M_PI) * atan(smoothDrive * x);
    
    return y;
    
}


void Distortion::setDrive(float newDrive){
    if (newDrive <= 10.f && newDrive >= 1.f){
        drive = newDrive;
    }
}


void Distortion::setFs(float newFs){
    Fs = newFs;
    alpha = exp(-log(9)/(Fs*smoothTime));
}
