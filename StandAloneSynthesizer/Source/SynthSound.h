/*
  ==============================================================================

    SynthSound.h
    Created: 11 Mar 2021 5:46:36pm
    Author:  John Rupsch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel (int midiChannel) override { return true; }
};
