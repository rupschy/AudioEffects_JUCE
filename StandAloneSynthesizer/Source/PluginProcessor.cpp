/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StandAloneSynthesizerAudioProcessor::StandAloneSynthesizerAudioProcessor()
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
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

StandAloneSynthesizerAudioProcessor::~StandAloneSynthesizerAudioProcessor()
{
}

//==============================================================================
const juce::String StandAloneSynthesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StandAloneSynthesizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StandAloneSynthesizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StandAloneSynthesizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StandAloneSynthesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StandAloneSynthesizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StandAloneSynthesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StandAloneSynthesizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StandAloneSynthesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void StandAloneSynthesizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void StandAloneSynthesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++){
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
}

void StandAloneSynthesizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StandAloneSynthesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void StandAloneSynthesizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    


    for (int i = 0; i < synth.getNumVoices(); ++i){
        if ( auto voice = dynamic_cast<juce::SynthesiserVoice*>(synth.getVoice(i))){
            // Osc controls
            // ADSR
            // LFO
            
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool StandAloneSynthesizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StandAloneSynthesizerAudioProcessor::createEditor()
{
    return new StandAloneSynthesizerAudioProcessorEditor (*this);
}

//==============================================================================
void StandAloneSynthesizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StandAloneSynthesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StandAloneSynthesizerAudioProcessor();
}

// Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout StandAloneSynthesizerAudioProcessor::createParams(){
    
    // ComboBox to switch oscillators
    // A  D  S  R in floats
    
    std::vector<std::unique_ptr<juce::RangedAudioParameters>> params;
    
    params.push_back (std::make_unique<juce::AudioParameterChoice> (("OSC", "Oscilllator", juce::StringArray {"Sine", "Sawtooth", "Sqaure"}, 0));
        
    // A D S R
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> {0.1f, 1.0f, }, 1.f));
                      
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> {0.1f, 3.0f, }, 0.4f));
    
                      
                      
                      
    return { params.begin(), params.end() };
}
