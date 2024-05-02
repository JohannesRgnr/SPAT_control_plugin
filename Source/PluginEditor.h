/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "customStyle.h"

//==============================================================================
/**
*/
class SPATControlAudioProcessorEditor  : public juce::AudioProcessorEditor
    ,
    //private juce::Slider::Listener,
    private juce::ComboBox::Listener,
    private juce::TextEditor::Listener
    // private juce::Button::Listener
{
public:
    SPATControlAudioProcessorEditor (SPATControlAudioProcessor&);
    ~SPATControlAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void spatModeUI();
    void panoramixModeUI();

private:
    
    void showConnectionErrorMessage(const juce::String& messageText)
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Connection error",
            messageText,
            "OK");
    }

    void textEditorTextChanged(juce::TextEditor& textEditor) override;
    void comboBoxChanged(juce::ComboBox* ComboBox) override;
    // void buttonClicked(juce::Button* button) override;

    // void sourceTypeBtnClicked();

    juce::CustomLNF myLNF;

    

    juce::CustomDial azimSlider, distSlider, elevSlider, yawSlider, apertureSlider, widthSlider, earlywidthSlider, earlyshapeSlider;
    juce::CustomLabel azimLabel, distLabel, elevLabel, yawLabel, apertureLabel, widthLabel, earlywidthLabel, earlyshapeLabel;

    juce::CustomDial presSlider, warmthSlider, brillianceSlider, roomPresSlider, runRevSlider, envSlider;
    juce::CustomLabel presLabel, warmthLabel, brillianceLabel, roomPresLabel, runRevLabel, envLabel;
    
    juce::ComboBox indexBox, typeBox, modeBox;
    juce::CustomLabel sourceLabel, typeLabel, modeLabel;

    juce::TextEditor spatPortText;
    juce::Label spatPortLabel;
    juce::TextEditor panoramixPortText;
    juce::Label panoramixPortLabel;

  
    

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> presSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> warmthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> brillianceSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomPresSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> runRevSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> envSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> azimSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> elevSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> distSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> yawSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> apertureSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> earlywidthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> earlyshapeSliderAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> indexBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeBoxAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> modeBoxAttachment;
    
    int sourceIndex = 1;
    // float sourceVolume = 0.0f;
    float azimuth = 0.0f;
    float elevation = 0.0f;


    SPATControlAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SPATControlAudioProcessorEditor)
};
