/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SPATControlAudioProcessor::SPATControlAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
    // establish OSC connection
    oscConnect();

    // add listeners
    apvts.addParameterListener("INDEX", this);
    apvts.addParameterListener("SOURCEPRES", this);
    apvts.addParameterListener("SOURCEWARMTH", this);
    apvts.addParameterListener("SOURCEBRILLIANCE", this);
    apvts.addParameterListener("ROOMPRES", this);
    apvts.addParameterListener("RUNNINGREV", this);
    apvts.addParameterListener("ENVELOP", this);

    apvts.addParameterListener("DIST", this);
    apvts.addParameterListener("AZIM", this);
    apvts.addParameterListener("ELEV", this);
    apvts.addParameterListener("YAW", this);
    apvts.addParameterListener("APERTURE", this);
    apvts.addParameterListener("EARLYWIDTH", this);
    apvts.addParameterListener("EARLYSHAPE", this);

    apvts.addParameterListener("TYPE", this);

}

SPATControlAudioProcessor::~SPATControlAudioProcessor()
{
}

//==============================================================================
const juce::String SPATControlAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SPATControlAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SPATControlAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SPATControlAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SPATControlAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SPATControlAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SPATControlAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SPATControlAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SPATControlAudioProcessor::getProgramName (int index)
{
    return {};
}

void SPATControlAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SPATControlAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SPATControlAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SPATControlAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else

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

void SPATControlAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool SPATControlAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SPATControlAudioProcessor::createEditor()
{
    return new SPATControlAudioProcessorEditor (*this);
}

//==============================================================================
void SPATControlAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SPATControlAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SPATControlAudioProcessor();
}


juce::AudioProcessorValueTreeState::ParameterLayout SPATControlAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SOURCEPRES", "sourcepres", 0.0f, 120.0f, 90.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SOURCEWARMTH", "sourcewarmth", 0.0f, 60.0f, 30.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SOURCEBRILLIANCE", "sourcebrilliance", 0.0f, 60.0f, 30.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ROOMPRES", "roompres", 0.0f, 120.0f, 48.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RUNNINGREV", "runningrev", 0.0f, 50.0f, 34.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ENVELOP", "envelop", 0.0f, 50.0f, 24.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("AZIM", "azim", 0.0f, 360.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ELEV", "elev", -90.0f, 90.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DIST", "dist", juce::NormalisableRange<float>(0.0f, 30.0f, 0.01f, 1.0f), 1.0f)); // NormalisableRange if skew factor needs to be specified
    params.push_back(std::make_unique<juce::AudioParameterFloat>("YAW", "yaw", 0.0f, 360.0f, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("APERTURE", "aperture", 10.0f, 180.0f, 80.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EARLYWIDTH", "earlywidth", 0.0f, 180.0f, 30.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("EARLYSHAPE", "earlyshape", 0.0f, 100.0f, 50.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterInt>("INDEX", "index", 1, 64, 1));
    params.push_back(std::make_unique<juce::AudioParameterInt>("TYPE", "type", 0, 1, 0));

    return { params.begin(), params.end() };

}


void SPATControlAudioProcessor::oscConnect()
{
    spatMessageSender.connect("127.0.0.1", spatPort);
    panoramixMessageSender.connect("127.0.0.1", panoramixPort);
}


void SPATControlAudioProcessor::sendAEDtoSpat()
{
    idx = apvts.getRawParameterValue("INDEX")->load();
    juce::String address = juce::String::formatted("/source/%d/aed", idx);

    juce::OSCMessage oscMessage(address);

    auto elev = apvts.getRawParameterValue("ELEV")->load();
    auto dist = apvts.getRawParameterValue("DIST")->load();
    auto azim = apvts.getRawParameterValue("AZIM")->load();

    oscMessage.addFloat32(azim);
    oscMessage.addFloat32(elev);
    oscMessage.addFloat32(dist);

    spatMessageSender.send(oscMessage);
}

void SPATControlAudioProcessor::sendAEDtoPanoramix()
{
    idx = apvts.getRawParameterValue("INDEX")->load();
    juce::String address;

    if (type)
    {
        address = juce::String::formatted("/stereo/%d/aed", idx);
    }
    else
    {
        address = juce::String::formatted("/track/%d/aed", idx);
    }
    
    juce::OSCMessage oscMessage(address);

    auto elev = apvts.getRawParameterValue("ELEV")->load();
    auto dist = apvts.getRawParameterValue("DIST")->load();
    auto azim = apvts.getRawParameterValue("AZIM")->load();

    oscMessage.addFloat32(azim);
    oscMessage.addFloat32(elev);
    oscMessage.addFloat32(dist);

    panoramixMessageSender.send(oscMessage);
}


void SPATControlAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    
    juce::String addressSpat;
    juce::String addressPanoramix;
    if (parameterID == "TYPE")
    {
        type = apvts.getRawParameterValue("TYPE")->load();
        
        
        DBG("type: " << type);
    }
   
    

    else if (parameterID == "INDEX")
    {
        idx = apvts.getRawParameterValue("INDEX")->load();
        // DBG("idx: " << idx);
    }

    else if (parameterID == "DIST"  || parameterID == "ELEV" || parameterID == "AZIM")
    {
        sendAEDtoSpat();
        sendAEDtoPanoramix();
    }
    else if (parameterID == "EARLYWIDTH")
    {
        addressSpat = juce::String::formatted("/source/%d/early/width", idx);
        addressPanoramix = juce::String::formatted("/track/%d/early/width", idx);

        juce::OSCMessage spatMessage(addressSpat);
        juce::OSCMessage panoramixMessage(addressPanoramix);

        spatMessage.addFloat32(newValue);
        panoramixMessage.addFloat32(newValue);

        spatMessageSender.send(spatMessage);
        panoramixMessageSender.send(panoramixMessage);
    }
    else    // SPAT parameters exclusively
    {
        if      (parameterID == "SOURCEPRES") { addressSpat = juce::String::formatted("/source/%d/pres", idx); }
        else if (parameterID == "SOURCEWARMTH") { addressSpat = juce::String::formatted("/source/%d/warm", idx); }
        else if (parameterID == "SOURCEBRILLIANCE") { addressSpat = juce::String::formatted("/source/%d/bril", idx); }
        else if (parameterID == "ROOMPRES") { addressSpat = juce::String::formatted("/source/%d/prer", idx); }
        else if (parameterID == "RUNNINGREV") { addressSpat = juce::String::formatted("/source/%d/revp", idx); }
        else if (parameterID == "ENVELOP") { addressSpat = juce::String::formatted("/source/%d/env", idx); }
        else if (parameterID == "YAW") { addressSpat = juce::String::formatted("/source/%d/yaw", idx); }
        else if (parameterID == "APERTURE") { addressSpat = juce::String::formatted("/source/%d/aperture", idx); }
        else if (parameterID == "EARLYSHAPE") { addressSpat = juce::String::formatted("/source/%d/early/shape", idx); }

        juce::OSCMessage oscMessage(addressSpat);
        oscMessage.addFloat32(newValue);
        spatMessageSender.send(oscMessage);
    }

    
}



