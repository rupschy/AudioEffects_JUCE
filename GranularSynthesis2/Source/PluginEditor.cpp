/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GranularSynthesis2AudioProcessorEditor::GranularSynthesis2AudioProcessorEditor (GranularSynthesis2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 350);
    
    
    
    inputMeter.setBounds(275,185,10,100);
    inputMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(inputMeter);
    
    outputMeter.setBounds(325,185,10,100);
    outputMeter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(outputMeter);
    
    grainSizeSelector.addListener(this);
    grainSizeSelector.addItem("64",1);
    grainSizeSelector.addItem("128",2);
    grainSizeSelector.addItem("256",3);
    grainSizeSelector.addItem("512",4);
    grainSizeSelector.addItem("1024",5);
    grainSizeSelector.addItem("2048",6);
    grainSizeSelector.addItem("4096",7);
    grainSizeSelector.addItem("8192",8);
    grainSizeSelector.setSelectedId(5);
    grainSizeSelector.setBounds(400,210,120,40);
    addAndMakeVisible(grainSizeSelector);

}

GranularSynthesis2AudioProcessorEditor::~GranularSynthesis2AudioProcessorEditor()
{
}

//==============================================================================
void GranularSynthesis2AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void GranularSynthesis2AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}




void GranularSynthesis2AudioProcessorEditor::comboBoxChanged(ComboBox * comboBox){
    if(comboBox == &grainSizeSelector){
        if(grainSizeSelector.getSelectedId() == 1){
            //64
            audioProcessor.grainSize = 64;
        }
        if(grainSizeSelector.getSelectedId() == 2){
            //64
            audioProcessor.grainSize = 128;
        }
        if(grainSizeSelector.getSelectedId() == 3){
            //64
            audioProcessor.grainSize = 256;
        }
        if(grainSizeSelector.getSelectedId() == 4){
            //64
            audioProcessor.grainSize = 512;
        }
        if(grainSizeSelector.getSelectedId() == 5){
            //64
            audioProcessor.grainSize = 1024;
        }
        if(grainSizeSelector.getSelectedId() == 6){
            //64
            audioProcessor.grainSize = 2048;
        }
        if(grainSizeSelector.getSelectedId() == 7){
            //64
            audioProcessor.grainSize = 4096;
        }
        if(grainSizeSelector.getSelectedId() == 8){
            //64
            audioProcessor.grainSize = 8192;
        }
    }
    
}


void GranularSynthesis2AudioProcessorEditor::timerCallback(){
    inputMeter.update(audioProcessor.meterValueInput);
    outputMeter.update(audioProcessor.meterValueOutput);
}
