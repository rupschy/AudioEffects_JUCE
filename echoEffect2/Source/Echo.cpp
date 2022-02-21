/*
  ==============================================================================

    Echo.cpp
    Created: 24 Feb 2021 3:48:31pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "Echo.h"


//Constructor
Echo::Echo(){}

void Echo::processSignal(float *signal, const int numSamples, const int c){
    // c - channel
//    for (int n = 0; n < numSamples; n++){
//        float x = *signal; // get value at memory location
//        x = processSample(x, c);
//        *signal = x;
//        signal++;
//    }
    
    // Alternative way
    for (int n = 0; n < numSamples; n++){
        float x = signal[n]; // get value at memory location
        x = processSample(x, c);
        signal[n] = x;
    }
}


float Echo::processSample(float x, int c){
    
    int delayIndex = writeIndex[c] - delaySamples;
    
    if (delayIndex < 0){
        delayIndex += BUFFERSIZE;
    }
    
    float y = x + 0.7f * w[c][delayIndex];
    
    // Feed-forward
    //w[c][index[c]] = x;
    
    // Feed-back
    w[c][writeIndex[c]] = y;
    
    writeIndex[c]++;
    if (writeIndex[c] >= BUFFERSIZE){
        writeIndex[c] = 0;
    }
    
    return y;
    
}

void Echo::prepare(float newFs){
    Fs = newFs;
    delaySamples = round(Fs*delayMS/1000.f);

}

void Echo::setBPM(float newBPM){
    
    bpm = newBPM;
    
}

void Echo::setNoteDuration(float newNoteDuration){
    noteDuration = newNoteDuration;
    
    // Convert to delaySamples;
    float beatSec = bpm * (1.f/60.f);
    float secBeat = 1.f/beatSec;
    float secNote = noteDuration * secBeat;
    float msNote = secNote * 1000.f;
    setDelayMS(msNote);
    
}

void Echo::setDelayMS(float newDelayMS){
    if (newDelayMS <= 1000.f){
        delayMS = newDelayMS;
        delaySamples = round(Fs*delayMS/1000.f);
    }
}
