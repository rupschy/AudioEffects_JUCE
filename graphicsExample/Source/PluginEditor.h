/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LargeKnob.h"
#include "SmallKnob.h"

//==============================================================================
/**
*/
class GraphicsExampleAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                             public juce::Slider::Listener
{
public:
    GraphicsExampleAudioProcessorEditor (GraphicsExampleAudioProcessor&);
    ~GraphicsExampleAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged();
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GraphicsExampleAudioProcessor& audioProcessor;

    ImageComponent bgImage;
    
    Slider knob1;
    Slider knob2;
    

    // Classes for "Look and Feel"
    LargeKnob largeKnob;
    SmallKnob smallKnob;
    // Look and feel version is updated so this is a previous version
    LookAndFeel_V3 lookAndFeel3;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicsExampleAudioProcessorEditor)
};
