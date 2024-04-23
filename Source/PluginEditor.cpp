/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SPATControlAudioProcessorEditor::SPATControlAudioProcessorEditor (SPATControlAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    
    juce::LookAndFeel::setDefaultLookAndFeel(&myLNF);


    setSize (460, 330);
    setWantsKeyboardFocus(true);
    
    typeBox.addItem("mono", 1);
    typeBox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::lightgrey);
    typeBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::black);
    typeBox.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    typeBox.addItem("stereo", 2);
    typeBox.setSelectedId(1);
    
    presLabel.setText("Source Presence", juce::dontSendNotification);
    presLabel.attachToComponent(&presSlider, false);

    warmthLabel.setText("Source Warmth", juce::dontSendNotification);
    warmthLabel.attachToComponent(&warmthSlider, false);
    

    brillianceLabel.setText("Source Brilliance", juce::dontSendNotification);
    brillianceLabel.attachToComponent(&brillianceSlider, false);

    roomPresLabel.setText("Room Presence", juce::dontSendNotification);
    roomPresLabel.attachToComponent(&roomPresSlider, false);

    runRevLabel.setText("Running Reverb", juce::dontSendNotification);
    runRevLabel.attachToComponent(&runRevSlider, false);

    envLabel.setText("Envelopment", juce::dontSendNotification);
    envLabel.attachToComponent(&envSlider, false);

    azimSlider.setRotaryParameters(0, juce::MathConstants<float>::twoPi, 0);
    azimSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    azimSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    azimSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    distSlider.setTextValueSuffix(" m");
    distSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    distSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    elevSlider.setRotaryParameters(juce::MathConstants<float>::pi, 0, 1);
    elevSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    elevSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    elevSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    yawSlider.setRotaryParameters(0, juce::MathConstants<float>::twoPi, 0);
    yawSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    yawSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    yawSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    apertureSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    apertureSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    apertureSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    earlywidthSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    earlywidthSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    earlywidthSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    earlyshapeSlider.setTextValueSuffix(" %");
    earlyshapeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    earlyshapeSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::deepskyblue);

    azimLabel.setText("Azimuth", juce::dontSendNotification);
    azimLabel.attachToComponent(&azimSlider, false);

    distLabel.setText("Distance", juce::dontSendNotification);
    distLabel.attachToComponent(&distSlider, false);

    elevLabel.setText("Elevation", juce::dontSendNotification);
    elevLabel.attachToComponent(&elevSlider, false);

    yawLabel.setText("Yaw", juce::dontSendNotification);
    yawLabel.attachToComponent(&yawSlider, false);

    apertureLabel.setText("Aperture", juce::dontSendNotification);
    apertureLabel.attachToComponent(&apertureSlider, false);

    earlywidthLabel.setText("Early Width", juce::dontSendNotification);
    earlywidthLabel.attachToComponent(&earlywidthSlider, false);

    earlyshapeLabel.setText("Early Shape", juce::dontSendNotification);
    earlyshapeLabel.attachToComponent(&earlyshapeSlider, false);

    juce::Font myfont;
    myfont.setBold(true);
    myfont.setHeight(11.0f);

    for (int i = 1; i < 65; i++)
    {
        indexBox.addItem(juce::String(i), i);
    }
    indexBox.setSelectedId(1);
    indexBox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::lightgrey);
    indexBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::black);
    indexBox.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    indexBox.setJustificationType(juce::Justification::centred);
    
    spatPortText.setJustification(juce::Justification::centred);
    spatPortText.setFont(myfont);
    spatPortText.setIndents(spatPortText.getLeftIndent(), 0);
    spatPortText.setInputRestrictions(5, "0123456789");
    spatPortText.setColour(juce::TextEditor::backgroundColourId, juce::Colours::lightgrey);
    spatPortText.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    spatPortText.setText(juce::String(audioProcessor.spatPort));

    spatPortLabel.setFont(myfont);
    spatPortLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    spatPortLabel.setText("Spat Port:", juce::dontSendNotification);
    spatPortLabel.setJustificationType(juce::Justification::right);

    panoramixPortText.setJustification(juce::Justification::centred);
    panoramixPortText.setFont(myfont);
    panoramixPortText.setIndents(spatPortText.getLeftIndent(), 0);
    panoramixPortText.setInputRestrictions(5, "0123456789");
    panoramixPortText.setColour(juce::TextEditor::backgroundColourId, juce::Colours::lightgrey);
    panoramixPortText.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    panoramixPortText.setText(juce::String(audioProcessor.panoramixPort));

    panoramixPortLabel.setFont(myfont);
    panoramixPortLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    panoramixPortLabel.setText("Panoramix Port:", juce::dontSendNotification);
    panoramixPortLabel.setJustificationType(juce::Justification::right);
    
    sourceLabel.setFont(myfont);
    sourceLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    sourceLabel.setText("Source", juce::dontSendNotification);
    sourceLabel.setJustificationType(juce::Justification::right);

    // add UI elements to the editor
    addAndMakeVisible(&presSlider);
    addAndMakeVisible(&warmthSlider);
    addAndMakeVisible(&brillianceSlider);
    addAndMakeVisible(&roomPresSlider);
    addAndMakeVisible(&runRevSlider);
    addAndMakeVisible(&envSlider);

    addAndMakeVisible(&azimSlider);
    addAndMakeVisible(&distSlider);
    addAndMakeVisible(&elevSlider);
    addAndMakeVisible(&yawSlider);
    addAndMakeVisible(&apertureSlider);
    addAndMakeVisible(&earlywidthSlider);
    addAndMakeVisible(&earlyshapeSlider);

    addAndMakeVisible(&indexBox);
    addAndMakeVisible(&sourceLabel);
    addAndMakeVisible(&spatPortText);
    addAndMakeVisible(&spatPortLabel);
    addAndMakeVisible(&panoramixPortText);
    addAndMakeVisible(&panoramixPortLabel);
    addAndMakeVisible(&typeBox);
    

    // create attachments
    presSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SOURCEPRES", presSlider);
    warmthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SOURCEWARMTH", warmthSlider);
    brillianceSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SOURCEBRILLIANCE", brillianceSlider);
    roomPresSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ROOMPRES", roomPresSlider);
    runRevSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "RUNNINGREV", runRevSlider);
    envSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ENVELOP", envSlider);

    azimSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "AZIM", azimSlider);
    elevSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ELEV", elevSlider);
    distSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DIST", distSlider);
    yawSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "YAW", yawSlider);
    apertureSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "APERTURE", apertureSlider);
    earlywidthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "EARLYWIDTH", earlywidthSlider);
    earlyshapeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "EARLYSHAPE", earlyshapeSlider);

    indexBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "INDEX", indexBox);
    typeBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "TYPE", typeBox);
    

    spatPortText.addListener(this);
    panoramixPortText.addListener(this);
    

}

SPATControlAudioProcessorEditor::~SPATControlAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void SPATControlAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey);
    g.setColour(juce::Colours::darkgrey);

    g.drawRoundedRectangle(10, 45, 270, 180, 4, 2);
    g.drawRoundedRectangle(10, 235, 440, 90, 4, 2);

    g.setFont(10.0f);    
}

void SPATControlAudioProcessorEditor::resized()
{
    
    sourceLabel.setBounds(10, 15, 40, 22);
    indexBox.setBounds(50, 15, 50, 22);

    typeBox.setBounds(110, 15, 90, 22);

   
    spatPortLabel.setBounds(210, 15, 65, 20);
    spatPortText.setBounds(275, 15, 40, 20);

    panoramixPortLabel.setBounds(315, 15, 95, 20);
    panoramixPortText.setBounds(410, 15, 40, 20);

    presSlider.setBounds(10, 70, 80, 80);
    warmthSlider.setBounds(100, 70, 80, 80);
    brillianceSlider.setBounds(190, 70, 80, 80);
    roomPresSlider.setBounds(10, 155, 80, 80);
    runRevSlider.setBounds(100, 155, 80, 80);
    envSlider.setBounds(190, 155, 80, 80);

    azimSlider.setBounds(10, 255, 75, 75);
    elevSlider.setBounds(70, 255, 75, 75);
    distSlider.setBounds(130, 255, 75, 75);
    yawSlider.setBounds(190, 255, 75, 75);
    apertureSlider.setBounds(250, 255, 75, 75);
    earlywidthSlider.setBounds(310, 255, 75, 75);
    earlyshapeSlider.setBounds(370, 255, 75, 75);
}

void SPATControlAudioProcessorEditor::textEditorTextChanged(juce::TextEditor& textEditor)
{
    spatPortText.onReturnKey = [this]
        {
            audioProcessor.spatPort = spatPortText.getText().getIntValue();
            audioProcessor.spatMessageSender.connect("127.0.0.1", audioProcessor.spatPort);
            spatPortText.unfocusAllComponents();
        };

    spatPortText.onFocusLost = [this]
        {
            audioProcessor.spatPort = spatPortText.getText().getIntValue();
            audioProcessor.spatMessageSender.connect("127.0.0.1", audioProcessor.spatPort);
            spatPortText.unfocusAllComponents();
        };

    panoramixPortText.onReturnKey = [this]
        {
            audioProcessor.panoramixPort = panoramixPortText.getText().getIntValue();
            audioProcessor.panoramixMessageSender.connect("127.0.0.1", audioProcessor.panoramixPort);
            panoramixPortText.unfocusAllComponents();
        };

    panoramixPortText.onFocusLost = [this]
        {
            audioProcessor.panoramixPort = panoramixPortText.getText().getIntValue();
            audioProcessor.panoramixMessageSender.connect("127.0.0.1", audioProcessor.panoramixPort);
            panoramixPortText.unfocusAllComponents();
        };

}

