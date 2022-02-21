/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
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

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //Initialize spec
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = 2;
    
    // Initializes everything needed for gain from DAW
    gain.prepare(spec);
    gain.reset();
    
    reverb.prepare(spec);
    reverb.reset();
    
    limiter.prepare(spec);
    limiter.reset();
    
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Need to convert AudioBuffer to AudioBlock for DSP Module
    dsp::AudioBlock<float> block (buffer);
    // Take in buffer and make into audioblock
    
    // Do DSP processing in here
    
    //block.multiplyBy(0.125f);
    
    // One time per block...
            //gain.setGainDecibels(-12.f);
    
    
    
    // instead of looping like:
    //    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    //    {
    //        for (int n = 0; n < block.getNumSamples(); ++channel){
    //            float x = block.getSample(channel,n);
    //            float y = gain.processSample(x);
    //            block.setSample(channel,n,y);
    //        }
    //    }

    //processSample vs process(which takes in a const ProcessContext & context
    
    // processSample()
    // SmapleType JUCE_VECTOR_CALLTYPE dsp::Gain<FloatType>::processSample(SampleType s);
    
    // process()
    // void dsp::Gain<FloatType>::process (const ProcessContext & context)
    
    // i/e processContext vs processContextNonReplacing) => has input and output to index
            //gain.process(dsp::ProcessContextReplacing<float> (block));
    
    // gain.process(dsp::ProcessContextNonReplacing<float> (block,outBlock));
    // Non Replacing is a great way to chain processes together:
    // gain->compression->distortion->reverb->Output
    
//    dsp::Reverb::Parameters params = reverb.getParameters();
//    params.roomSize = 0.95;
//    params.damping = 0.1;
//    params.width = 0.75;
//    reverb.setParameters(params);
//    
//    reverb.process(dsp::ProcessContextReplacing<float> (block));
    
    
    limiter.setThreshold(12.f);
    limiter.setRelease(100.f);
    
    reverb.process(dsp::ProcessContextReplacing<float> (block));
    
    // put in header
    struct MyParameters{
        float freq = 1000.f;
        float Q = 0.7071f;
        float amp = 6;
    };
    MyParameters myParams;
    
    myParams.freq = 2000.f;
    
    
    // At the end of processBlock, convert block back to buffer
    block.copyTo(buffer);
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
