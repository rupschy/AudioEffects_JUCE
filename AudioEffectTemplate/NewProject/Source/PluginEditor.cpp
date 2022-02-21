/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    auto backgroundImage = ImageCache::getFromMemory(BinaryData::bg_jpg, BinaryData::bg_jpgSize);
    
    if(! backgroundImage.isNull()){
        backgroundImageComponent.setImage(backgroundImage,RectanglePlacement::stretchToFit);
    }
    else {
        jassert(!backgroundImage.isNull());
    }
    
    addAndMakeVisible(backgroundImageComponent);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (700, 350);
    
    


}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (juce::Colours::darkgrey);
//    g.setColour(juce::Colours::orange);
    
    
    //1 basics
//    g.fillRect ( 10, 10, 40 , 40);
    //         (x, y, width, height);
    
    //2 Using rectangle and Point classes
    juce::Rectangle<int> areaHeader(1,1,700,100);
    g.setColour(juce::Colours::darkgrey);
    g.fillRect(areaHeader);
    
    juce::Rectangle<int> areaRight(350,125,350,250);
    g.setColour(juce::Colours::cornflowerblue);
    g.fillRect(areaRight);
    
    juce::Rectangle<int> areaLeft(1,125,350,250);
    g.setColour(juce::Colours::darkorchid);
    g.fillRect(areaLeft);
    
    // 3 Using Point and Path classes
//    juce::Path path;
//    path.startNewSubPath(juce::Point<float> (10,10));
//    path.lineTo(juce::Point<float> (50,10));
//    path.lineTo(juce::Point<float> (50,50));
//    path.lineTo(juce::Point<float> (10,50));
//    g.fillPath(path);
    
    
    
//    g.setColour(juce::Colours::cornflowerblue);
//    g.setFont (18.0f);
//    g.drawFittedText ("| Granular |", getLocalBounds(), juce::Justification::centredLeft, 1);
//
//    g.setColour(juce::Colours::darkorchid);
//    g.drawFittedText ("| Texturize |", getLocalBounds(), juce::Justification::centredRight, 1);
//
//
//    g.setColour(juce::Colours::black);
//    g.setFont(64.f);
//    g.drawFittedText("Texture Synthesizer", getLocalBounds(), juce::Justification::centredTop, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    

}
