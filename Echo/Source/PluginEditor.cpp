/*
  ==============================================================================
    This file contains the basic framework code for a JUCE plugin editor.
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EchoEffectAudioProcessorEditor::EchoEffectAudioProcessorEditor (EchoEffectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    delayKnob.addListener(this);
    delayKnob.setBounds(100, 50, 125, 125);
    delayKnob.setValue(audioProcessor.delayMS);
    delayKnob.setRange(10.f, 1000.f,1.f);
    delayKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 75, 25);
    delayKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(delayKnob);
    
    noteSelector.addListener(this);
    noteSelector.addItem("Whole",1)
    noteSelector.addItem("Half",2);
    noteSelector.addItem("Quarter",3);
    noteSelector.addItem("Eighth",4);
    noteSelector.addItem("Sixteenth",5);
    noteSelector.setSelectedId(2);
    noteSelector.setBounds(275,100,120,40);
    addAndMakeVisible(noteSelector);
    
    tempoSyncButton.addListener(this);
    tempoSyncButton.setBounds(275, 175, 100, 40);
    tempoSyncButton.setButtonText("Sync'd");
    tempoSyncButton.setToggleState(audioProcessor.tempoSyncd, dontSendNotification);
    tempoSyncButton.setRadioGroupId(1); // links with notTempoSyncd
    addAndMakeVisible(tempoSyncButton);
    
        
    notTempoSyncButton.addListener(this);
    notTempoSyncButton.setBounds(275, 175, 100, 40);
    notTempoSyncButton.setButtonText("Sync off");
    notTempoSyncButton.setToggleState(audioProcessor.tempoSyncd, dontSendNotification);
    notTempoSyncButton.setRadioGroupId(1);
    addAndMakeVisible(notTempoSyncButton);
    
    delayKnob.setEnabled(!audioProcessor.tempoSyncd);
    noteSelector.setEnabled(audioProcessor.tempoSyncd);
    
    
    
    meter.setBounds(25,25,10,100);
    meter.configuration = SimpleMeter::VERTICAL;
    addAndMakeVisible(meter);
    
    startTimerHz(30);
    
}

EchoEffectAudioProcessorEditor::~EchoEffectAudioProcessorEditor()
{
}

//==============================================================================
void EchoEffectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void EchoEffectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void EchoEffectAudioProcessorEditor::sliderValueChanged(Slider * slider){
    
    if (slider == &delayKnob){
        audioProcessor.delayMS = delayKnob.getValue();
    }
    
}

void EchoEffectAudioProcessor::comboBoxChanged(ComboBox * comboBox){
    
    if(comboBox == &noteSelector){
        if(noteSelector.getSelectedId() == 1){
            // half note
            audioProcessor.noteSelect = Echo::NoteSelection::WHOLE;
        }
        if(noteSelector.getSelectedId() == 2){
            // quarter note
            audioProcessor.noteDuration = Echo::NoteSection::HALF;
        }
        if(noteSelector.getSelectedId() == 3){
            // 8th note
            audioProcessor.noteDuration = Echo::NoteSection::QUARTER;
        }
        if(noteSelector.getSelectedId() == 4){
            // 16th note
            audioProcessor.noteDuration = Echo::NoteSection::EIGHTH;
        }
        if(noteSelector.getSelectedId() == 5){
            audioProcessor.noteDuration = Echo::NoteSection::SIXTEENTH;
        }
    }
}


void EchoEffectAudioProcessor::buttonClicked(Button * button){
    // Causes one when one is checked, the other will not
    if (button == &tempoSyncButton){
        audioProcessor.tempoSyncd = true;
        delayKnob.setEnabled(false);
        noteSelector.setEnabled(true);
    }
    if (button == &notTempoSyncButton){
        audioProcessor.tempoSyncd = false;
        delayKnob.setEnabled(true);
        noteSelector.setEnabled(false);
    }
}


// 30 times per second, it will call this fucntion and use it
void EchoEffectAudioProcessorEditor::timerCallback(){
    meter.update(audioProcessor.meterValue);
    // meterValue
}

