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

    /** editor elements  **/
    setSize (460, 265);
    setWantsKeyboardFocus(true);
    
    typeBox.addItem("mono", 1);
    typeBox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::lightgrey);
    typeBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::black);
    typeBox.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    typeBox.addItem("stereo", 2);
    typeBox.setSelectedId(1);

    modeBox.addItem("spat", 1);
    modeBox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::lightgrey);
    modeBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::black);
    modeBox.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    modeBox.setJustificationType(juce::Justification::centred);
    modeBox.addItem("panoramix", 2);
    modeBox.setSelectedId(1);

        
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
    azimSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);
    

    distSlider.setTextValueSuffix(" m");
    distSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    distSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

    elevSlider.setRotaryParameters(juce::MathConstants<float>::pi, 0, 1);
    elevSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    elevSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    elevSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

    yawSlider.setRotaryParameters(0, juce::MathConstants<float>::twoPi, 0);
    yawSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    yawSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    yawSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

    apertureSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    apertureSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    apertureSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

    widthSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    widthSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    widthSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

    earlywidthSlider.setTextValueSuffix(juce::CharPointer_UTF8("\xc2\xb0"));
    earlywidthSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    earlywidthSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

    earlyshapeSlider.setTextValueSuffix(" %");
    earlyshapeSlider.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::deepskyblue);
    earlyshapeSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::grey);

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

    widthLabel.setText("Width", juce::dontSendNotification);
    widthLabel.attachToComponent(&widthSlider, false);

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
    spatPortLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
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
    panoramixPortLabel.setColour(juce::Label::textColourId, juce::Colours::lightgrey);
    panoramixPortLabel.setText("Panoramix Port:", juce::dontSendNotification);
    panoramixPortLabel.setJustificationType(juce::Justification::right);
    
    sourceLabel.setFont(myfont);
    sourceLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    sourceLabel.setText("Source", juce::dontSendNotification);
    sourceLabel.setJustificationType(juce::Justification::right);

    modeLabel.setFont(myfont);
    modeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    modeLabel.setText("Mode", juce::dontSendNotification);
    modeLabel.setJustificationType(juce::Justification::right);

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
    addAndMakeVisible(&widthSlider);
    addAndMakeVisible(&earlywidthSlider);
    addAndMakeVisible(&earlyshapeSlider);

    addAndMakeVisible(&indexBox);
    addAndMakeVisible(&sourceLabel);
    addAndMakeVisible(&modeBox);
    addAndMakeVisible(&modeLabel);
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
    widthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "WIDTH", widthSlider);
    earlywidthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "EARLYWIDTH", earlywidthSlider);
    earlyshapeSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "EARLYSHAPE", earlyshapeSlider);

    indexBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "INDEX", indexBox);
    typeBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "TYPE", typeBox);
    modeBoxAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "MODE", modeBox);

    spatPortText.addListener(this);
    panoramixPortText.addListener(this);
    modeBox.addListener(this);

    auto mode = audioProcessor.apvts.getRawParameterValue("MODE")->load();
    if (mode)
    {
        panoramixModeUI();
    }
    else
    {
        spatModeUI();
    }
    
}

SPATControlAudioProcessorEditor::~SPATControlAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void SPATControlAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    // g.setColour(juce::Colours::grey);

    //g.fillRoundedRectangle(10, 45, 270, 180, 4);
    
    //g.fillRoundedRectangle(10, 235, 440, 80, 4);

    juce::Path path1, path2, path3;
    path1.addRoundedRectangle(0, 0, 460, 30, 3);
    path2.addRoundedRectangle(0, 30, 250, 160, 3);
    path3.addRoundedRectangle(0, 190, 460, 75, 3);
    /*juce::DropShadow(juce::Colours::black, 10, { 2, 1 }).drawForPath(g, path1);
    juce::DropShadow(juce::Colours::black, 10, { 2, 1 }).drawForPath(g, path2);
    juce::DropShadow(juce::Colours::black, 10, { 2, 1 }).drawForPath(g, path3);*/

    g.setColour(juce::Colour::fromString("FFC4C4C4"));
    juce::ColourGradient cg = juce::ColourGradient::vertical(juce::Colour::fromString("FFC4C4C4"), 27, juce::Colours::darkgrey, 30);
    g.setGradientFill(cg);
    g.fillPath(path1);

    cg = juce::ColourGradient::vertical(juce::Colour::fromString("FFC4C4C4"), 187, juce::Colours::darkgrey, 190);
    g.setGradientFill(cg);
    g.fillPath(path2);

    cg = juce::ColourGradient::vertical(juce::Colour::fromString("FFC4C4C4"), 260, juce::Colours::darkgrey, 265);
    g.setGradientFill(cg);
    g.fillPath(path3);

    // g.setFont(10.0f);
    g.setFont(24.0f);
    g.drawFittedText("SPAT Control", 315, 30, 150, 50, juce::Justification::centred, 1);
    g.setFont(10.0f);
    g.drawFittedText("v.0.2_05/2024", 385, 60, 75, 20, juce::Justification::centred, 1);
}

void SPATControlAudioProcessorEditor::resized()
{
    int x_pos, y_pos1, y_pos2, x_space;

    /********* upper section ********/
    y_pos1 = 3;

    sourceLabel.setBounds(0, y_pos1, 40, 20);
    indexBox.setBounds(40, y_pos1, 50, 20);
    typeBox.setBounds(100, y_pos1, 65, 20);
      
    modeLabel.setBounds(330, y_pos1, 40, 20);
    modeBox.setBounds(370, y_pos1, 80, 20);

    /********* settings section ********/
    y_pos1 = 100;

    spatPortLabel.setBounds(340, y_pos1, 70, 20);
    spatPortText.setBounds(410, y_pos1, 40, 20);

    panoramixPortLabel.setBounds(280, y_pos1 + 30, 130, 20);
    panoramixPortText.setBounds(410, y_pos1 + 30, 40, 20);

    /********* source section ********/
    x_pos = 0;
    x_space = 80;
    y_pos1 = 47;
    y_pos2 = y_pos1 + 75;

    presSlider.setBounds(x_pos, y_pos1, 80, 80);
    warmthSlider.setBounds(x_pos + x_space, y_pos1, 80, 80);
    brillianceSlider.setBounds(x_pos + 2 * x_space, y_pos1, 80, 80);
    roomPresSlider.setBounds(x_pos, y_pos2, 80, 80);
    runRevSlider.setBounds(x_pos + x_space, y_pos2, 80, 80);
    envSlider.setBounds(x_pos + 2 * x_space, y_pos2, 80, 80);

    /********* position section ********/
    x_pos = 0;
    x_space = 55;
    y_pos1 = 205;
    
    azimSlider.setBounds(x_pos, y_pos1, 75, 75);
    elevSlider.setBounds(x_pos + x_space, y_pos1, 75, 75);
    distSlider.setBounds(x_pos + 2*x_space, y_pos1, 75, 75);
    yawSlider.setBounds(x_pos + 3*x_space, y_pos1, 75, 75);
    apertureSlider.setBounds(x_pos + 4*x_space, y_pos1, 75, 75);
    widthSlider.setBounds(x_pos + 5 * x_space, y_pos1, 75, 75);
    earlywidthSlider.setBounds(x_pos + 6*x_space, y_pos1, 75, 75);
    earlyshapeSlider.setBounds(x_pos + 7*x_space, y_pos1, 75, 75);
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


void SPATControlAudioProcessorEditor::comboBoxChanged(juce::ComboBox* ComboBox)
{
    modeBox.onChange = [this]
        {
            auto mode = audioProcessor.apvts.getRawParameterValue("MODE")->load();
            if (mode)
            {
                panoramixModeUI();
            }
            else 
            {
                spatModeUI();
            }
        };


}

void SPATControlAudioProcessorEditor::spatModeUI()
{
    presSlider.setEnabled(true);
    warmthSlider.setEnabled(true);
    brillianceSlider.setEnabled(true);
    roomPresSlider.setEnabled(true);
    runRevSlider.setEnabled(true);
    envSlider.setEnabled(true);
    yawSlider.setEnabled(true);
    apertureSlider.setEnabled(true);
    earlyshapeSlider.setEnabled(true);
    widthSlider.setEnabled(false);
    
}

void SPATControlAudioProcessorEditor::panoramixModeUI()
{
    presSlider.setEnabled(false);
    warmthSlider.setEnabled(false);
    brillianceSlider.setEnabled(false);
    roomPresSlider.setEnabled(false);
    runRevSlider.setEnabled(false);
    envSlider.setEnabled(false);
    yawSlider.setEnabled(false);
    apertureSlider.setEnabled(false);
    earlyshapeSlider.setEnabled(false);
    widthSlider.setEnabled(true);
    
}
