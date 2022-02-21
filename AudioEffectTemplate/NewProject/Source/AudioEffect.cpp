/*
  ==============================================================================

    AudioEffect.cpp
    Created: 25 Feb 2021 2:46:01pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "AudioEffect.h"


float AudioEffect::processSample(float x){
    return x;
}


void AudioEffect::prepare(float newFs){
    Fs = newFs;
}
