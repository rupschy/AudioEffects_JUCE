/*
  ==============================================================================

    Distortion.h
    Created: 4 Feb 2021 2:28:39pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
// match name of new CPP/H files to class name
class Distortion {
    
public:
    float processSample(float x);
    
    void setDrive(float newDrive);
    
    void setFs(float Fs);

    
private:
    float drive = 1.f;
    
    float smoothDrive = 1.f;
    
    float Fs = 48000.f;
    float smoothTime = 0.01f;
    float alpha = exp(-log(9)/(Fs*smoothTime));
    // drive can't be changed unless the function is used
//    I/e plugin processor doesnt know what drive is as its in private
};

