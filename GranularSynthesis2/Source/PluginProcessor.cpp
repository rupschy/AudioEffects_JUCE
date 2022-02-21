/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Granulate.h"
#include <JuceHeader.h>

//==============================================================================
GranularSynthesis2AudioProcessor::GranularSynthesis2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

GranularSynthesis2AudioProcessor::~GranularSynthesis2AudioProcessor()
{
}

//==============================================================================
const juce::String GranularSynthesis2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GranularSynthesis2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthesis2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GranularSynthesis2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GranularSynthesis2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GranularSynthesis2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GranularSynthesis2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GranularSynthesis2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String GranularSynthesis2AudioProcessor::getProgramName (int index)
{
    return {};
}

void GranularSynthesis2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void GranularSynthesis2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    granulate.prepare(sampleRate);
    vuAnalysisInput.setSampleRate(sampleRate);
    vuAnalysisOutput.setSampleRate(sampleRate);

}

void GranularSynthesis2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GranularSynthesis2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void GranularSynthesis2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    playHead = this->getPlayHead();


    granulate.setGrainSize(grainSize);
    granulate.setPermParameters(grainSize);
    granulate.setPermutationSet(grainSize);
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        for (int n = 0; n < buffer.getNumSamples(); ++n){
            float x = buffer.getReadPointer(channel)[n];
            meterValueInput = vuAnalysisInput.processSample(x,channel);
            
//            1. Bring sample-by-sample to matrix
            x = granulate.setInputMatrix(x,channel);
            x = granulate.outputArray(channel);
            
            
            meterValueOutput = vuAnalysisOutput.processSample(x,channel);
            buffer.getWritePointer(channel)[n] = x;
        }
//        auto* channelData = buffer.getWritePointer (channel);
    }
}

//==============================================================================
bool GranularSynthesis2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* GranularSynthesis2AudioProcessor::createEditor()
{
    return new GranularSynthesis2AudioProcessorEditor (*this);
}

//==============================================================================
void GranularSynthesis2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void GranularSynthesis2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GranularSynthesis2AudioProcessor();
}
