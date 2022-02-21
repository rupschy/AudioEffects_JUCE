#pragma once
#include "JuceHeader.h"
#include "PingPongDelayParameters.h"

class PingPongDelayProcessor    : public AudioProcessor
                                , public AudioProcessorValueTreeState::Listener
{
public:
    PingPongDelayProcessor();
    ~PingPongDelayProcessor();

    // How the plugin describes itself to the host
    const String getName() const override { return "PingPongDelay"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    //bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    bool hasEditor() const override { return true; }
    AudioProcessorEditor* createEditor() override;

    // Multiple simultaneously-loaded presets aka "programs" (not used)
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const String getProgramName(int) override { return {}; }
    void changeProgramName(int, const String&) override {}

    // Actual audio processing
    void prepareToPlay (double sampleRate, int maxSamplesPerBlock) override;
    void releaseResources() override;
    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    // Enabling the host to save and restore state
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

public:
    // Plugin's AudioProcessorValueTreeState
    AudioProcessorValueTreeState valueTreeState;

    // Application's view of the AudioProcessorValueTreeState, including working parameter values
    PingPongDelayParameters parameters;

    // Responding to parameter changes
    void parameterChanged(const String&, float) override;

private:
    // Circular buffer variables for implementing delay
    AudioSampleBuffer delayBuffer;
    int delayBufferLength;
    int delayReadPositionLeft, delayReadPositionRight;
    int delayWritePosition;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PingPongDelayProcessor)
};
