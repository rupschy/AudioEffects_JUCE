/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SimpleMeter.h"

//==============================================================================
/**
*/
class GranularSynthesis2AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                public juce::ComboBox::Listener,
                                                public Timer
{
public:
    GranularSynthesis2AudioProcessorEditor (GranularSynthesis2AudioProcessor&);
    ~GranularSynthesis2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void comboBoxChanged(juce::ComboBox * comboBox) override;

    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GranularSynthesis2AudioProcessor& audioProcessor;
    
    void timerCallback() override;
    
    ComboBox grainSizeSelector;
    
    SimpleMeter inputMeter;
    SimpleMeter outputMeter;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GranularSynthesis2AudioProcessorEditor)
};
