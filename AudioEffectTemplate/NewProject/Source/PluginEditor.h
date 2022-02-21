/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    
    void resized() override;
    
    static const juce::Font& getAirstrikeFont()
        {
            static juce::Font Airstrike3D (Font (Typeface::createSystemTypefaceFor (BinaryData::airstrike3d_ttf,
                                                                        BinaryData::airstrike3d_ttfSize)));
            return Airstrike3D;
        }
    
    // void AttributedString::setFont(Range<int> range, const Font & Airstrike3D);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;

    ImageComponent backgroundImageComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
