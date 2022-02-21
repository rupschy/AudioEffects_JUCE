/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyTestPluginAudioProcessorEditor::MyTestPluginAudioProcessorEditor (MyTestPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300); // Constructor
    
    gainSlider.addListener(this); // Listen to user interaction with this GUI window
    gainSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag); // Circular knob
    gainSlider.setBounds(40,80,120,120); // Position on GUI
    // gainSlider.setBounds(<#int x#>, <#int y#>, <#int width#>, <#int height#>)
    gainSlider.setRange(0.f,10.f,.01f); // Set range and interval for slider max and min
    gainSlider.setSkewFactorFromMidPoint(2.f); // Setting mid-point of pan-pot
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 30);
    
    // Changed to pointer
    gainSlider.setValue(*audioProcessor.gain); // Sets value as init
    addAndMakeVisible(gainSlider);
    
    muteButton.addListener(this);
    muteButton.setBounds(120,90,20,20);
    muteButton.setButtonText("Mute");
    muteButton.setToggleState(audioProcessor.muteOn, dontSendNotification);
    addAndMakeVisible(muteButton);
    
    startTimerHz(30);
}

MyTestPluginAudioProcessorEditor::~MyTestPluginAudioProcessorEditor()
{
}

//==============================================================================
void MyTestPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::orangered);
    g.setFont (15.0f);
    //g.drawFittedText ("My Distortion Plug-in", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("My Distortion Plug-in" ,10,30, 100, 100,juce::Justification::centred,1);
}

void MyTestPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}




void MyTestPluginAudioProcessorEditor::sliderValueChanged(Slider * slider){
    if (slider == &gainSlider){
        *audioProcessor.gain = gainSlider.getValue();
        // Did the slider move? if so, assign this new value to the gain variable
    }
    
    
}


void MyTestPluginAudioProcessorEditor::buttonClicked(Button * button){


    if (button == &muteButton){
        audioProcessor.muteOn = !audioProcessor.muteOn;
    }
}


void MyTestPluginAudioProcessorEditor::timerCallback(){
    gainSlider.setValue(*audioProcessor.gain);
}
