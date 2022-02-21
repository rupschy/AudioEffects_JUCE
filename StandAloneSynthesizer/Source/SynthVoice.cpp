/*
  ==============================================================================

    SynthVoice.cpp
    Created: 11 Mar 2021 5:46:11pm
    Author:  John Rupsch

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound (juce::SynthesiserSound * sound){
    return dynamic_cast<juce::SynthesiserSound*>(sound);
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound * sound, int currentPitchWheelPosition){
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}


void SynthVoice::stopNote (float velocity, bool allowTailOff){
    adsr.noteOff();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){
    
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels  = outputChannels;
    
    osc.prepare (spec);
    gain.prepare(spec);
    
    osc.setFrequency(440.f);
    gain.setGainLinear(0.01f); //between 0 and 1
    
    isPrepared = true;
}

void SynthVoice::renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    jassert (isPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock { outputBuffer };
    osc.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    adsr.applyEnvelopeToBuffer (outputBuffer, startSample, numSamples);
}
