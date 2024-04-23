/*
  ==============================================================================

    customStyle.h
    Created: 19 Apr 2024 4:00:59pm
    Author:  regnier

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace juce
{

    class CustomLNF : public juce::LookAndFeel_V4
    {
    public:
        void drawRotarySlider(Graphics&, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider&);
        
        Label* createSliderTextBox(Slider& Slider) override;
        
                
        Font getComboBoxFont(ComboBox& /*box*/) override
        {
            return getCommonFont();
        }

        Font getPopupMenuFont() override
        {
            return getCommonFont();
        }

        Font getLabelFont(Label& /*box*/) override
        {
            return getCommonFont();
        }


    private:
        Font getCommonFont()
        {
            return Font("Sans Serif", "Bold", 10.f);
        }

    };


    class CustomDial : public Slider
    {
    public:
        CustomDial()
        {
            setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            //setColour(Slider::ColourIds::rotarySliderFillColourId, Colours::orange);
            //setColour(Slider::ColourIds::thumbColourId, Colours::orange);
            // setSize(80, 80);
            setTextBoxStyle(Slider::TextBoxBelow, false, 80, 24);
            //setColour(Slider::ColourIds::textBoxOutlineColourId, Colours::transparentWhite);
            //setColour(Slider::ColourIds::textBoxTextColourId, Colours::black);
            
            
        }

    private:

    };

    class CustomLabel : public Label
    {
    public:
        

        CustomLabel()
        {
            setColour(Label::textColourId, juce::Colours::black);
            setJustificationType(Justification::centredBottom);
            Font myFont;
            myFont.setBold(true);
            setFont(myFont.withHeight(10.0f));   
        }

    private:
        bool leftOfOwnerComp = false;
        Value textValue;

    };


}