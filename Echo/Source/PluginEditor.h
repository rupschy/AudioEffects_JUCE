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
class EchoEffectAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener,
                                        public juce::ComboBox::Listener,
                                        public juce::Button::Listener,
                                        public Timer

{


public:
    EchoEffectAudioProcessorEditor (EchoEffectAudioProcessorEditor&);
    ~EchoEffectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider * slider) override;
    void comboBoxChanged(juce::ComboBox * comboBox) override;
    void buttonClicked(juce::Button * button) override;
    
    // need pure virtual function
    virtual void timerCallBack() = 0;
    
    Echo::NoteSelection noteSelect = Echo::NoteSelection::WHOLE;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    EchoEffectAudioProcessorEditor& audioProcessor;
    
    juce::Slider delayKnob;

    juce::ComboBox noteSelector;
    
    juce::ToggleButton tempoSyncButton;
    juce::ToggleButton notTempoSyncButton;
    
    SimpleMeter meter;
    // use timer to update meter drawing
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EchoEffectAudioProcessorEditor)
};
