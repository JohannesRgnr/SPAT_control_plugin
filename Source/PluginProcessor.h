/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class SPATControlAudioProcessor  : public juce::AudioProcessor,
    private juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    SPATControlAudioProcessor();
    ~SPATControlAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;

    juce::String ipAddress = "127.0.0.1";
    int spatPort = 9001;
    int panoramixPort = 4002;
    int type = 0;

    /* instantiate OSC message senders */
    juce::OSCSender spatMessageSender;
    juce::OSCSender panoramixMessageSender;

private:



    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    void oscConnect();
    void sendAEDtoSpat();
    void sendAEDtoPanoramix();

    void parameterChanged(const juce::String& parameterID, float newValue);
  
    int idx = 1;
    int sourceType = 0;
    int mode = 0;
    float radius = 0.0f;
    float volFactor = 1.0f;
    float azimuth = 0.0f;
    float elevation = 0.0f;
    float dist = 1.0f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SPATControlAudioProcessor)
};
