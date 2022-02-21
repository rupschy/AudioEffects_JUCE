/*
  ==============================================================================
    Echo.cpp
    Created: 16 Feb 2021 1:43:15pm
    Author:  Eric Tarr
  ==============================================================================
*/

#include "EchoEffect.h"


// Constructor
Echo::Echo(){}

void Echo::processSignal(float *signal, const int numSamples, const int c){
//    for (int n = 0; n < numSamples; n++){
//        // get value and de-reference from memory location
//        float x = *signal;
//        x = processSample(x,c);
//        *signal = x;
//        signal++; // take this memory location and move to the next
    // ALTERNATIVE WAY
    for (int n = 0; n < numSamples; n++){
        // get value and de-reference from memory location
        float x = *signal;
        x = processSample(x,c);
        signal[n] = x;
    }
}

float Echo::processSample(float x, int c){
    
    int delayIndex = writeIndex[c] - delaySamples;
    
    if (delayIndex < 0){
        delayIndex += BUFFERSIZE;
    }
//
    float d = filter.processSample(w[c][delayIndex],c);
//
    float y = x + 0.7f * d;
    
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
    filter.setFs(Fs);

}

void Echo::setBPM(float newBPM){
    bpm = newBPM;
}

void Echo::setNoteDuration(NoteSelection newNoteSelection){
    // noteDuration = newNoteDuration;
    noteSelect = newNoteSelection;
    
    
    switch (noteSelect) {
        case WHOLE:
            noteDuration = 4.f; //this is the only place we will need to put in numbers b/c of enum
            break;
        case HALF:
            noteDuration = 2.f;
            break;
        case QUARTER:
            noteDuration = 1.f;
        case EIGHTH:
            noteDuration = 0.5f;
            break;
        case SIXTEENTH:
            noteDuration = 0.25f;
            break;
            
        default:
            noteDuration = 1.f;
    }
    // Convert to delaySamples
//    float beatSec = bpm * (1.f/60.f);
//    float secBeat = 1.f/beatSec;
//    float secNote = noteDuration * secBeat;
//    float msNote = secNote * 1000.f;
//    setDelayMS(msNote);
    
}

void Echo::setDelayMS(float newDelayMS){
    if (newDelayMS <= 1000.f){
        delayMS = newDelayMS;
        delaySamples = round(Fs*delayMS/1000.f);
    }
}


void Echo::setFilterCutoff(float freq){
    filter.setFreq(freq);
}
