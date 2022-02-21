/*
  ==============================================================================

    Panner.h
    Created: 8 Mar 2021 4:26:55pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

#include <cmath>

class Panner
{
public:
    
    //void prepare(float Fs, int samplesPerPBlock) override;
    //void
    
    
};

class DelayLine {
public:
    void bufferSetup (const int maxDelayTimeSamples)
    {
        delayBufferSamples = maxDelayTimeSamples + 2;
        if (delayBufferSamples < 1)
            delayBufferSamples = 1;
        
        delayWritePosition = 0;
};
    
    void writeSample(const float sampleToWrite)
    {
        delayBuffer.setSample(0, delayWritePosition, sampleToWrite);
        
        if(++delayWritePosition >= delayBufferSamples)
            delayWritePosition -= delayBufferSamples;
    }
    
    float readSample (const float delayTime){
        float readPosition = fmodf((float)(delayWritePosition - 1) - delayTime + (float)delayBufferSamples);
        int localReadPosition = floorf(readPosition);
        
        float fraction = readPosition - (float)localReadPosition;
        float delayed1 = delayBuffer.getSample(0, (localReadPosition + 0));
        float delayed2 = delayBuffer.getSample(0, (localReadPosition + 1) % delayBufferSamples);
        
        return delayed1 + fraction * (delayed2-delayed1);
    }
    
private:
    AudioSampleBuffer delayBuffer;
    int delayBufferSamples;
    int delayWriteSamples;
};

DelayLine delayLineL;
DelayLine delayLineR;
int maxDelaySamples;
