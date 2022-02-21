/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GraphicsExampleAudioProcessorEditor::GraphicsExampleAudioProcessorEditor (GraphicsExampleAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
//    bgImage = ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    setSize(420,420);
    
    knob1.addListener(this);
    knob1.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    knob1.setBounds(50,50,200,200);
    knob1.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    knob1.setLookAndFeel(&largeKnob);
    addAndMakeVisible(knob1);
    

    knob2.addListener(this);
    knob2.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    knob2.setBounds(50,50,100,100);
    knob2.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
//    knob2.setLookAndFeel(&smallKnob);
    knob2.setLookAndFeel(&lookAndFeel3);
    addAndMakeVisible(knob2);
    
}

GraphicsExampleAudioProcessorEditor::~GraphicsExampleAudioProcessorEditor()
{
}

//==============================================================================
void GraphicsExampleAudioProcessorEditor::paint (juce::Graphics& g)
{
//    g.drawImage(bgImage,0,0);
}

void GraphicsExampleAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void GraphicsExampleAudioProcessorEditor::sliderValueChanged(){
    if (Slider == knob1){
        sliderValueChanged = knob1.getValue;
    }
}
