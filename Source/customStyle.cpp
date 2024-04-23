/*
  ==============================================================================

    customStyle.cpp
    Created: 19 Apr 2024 4:00:59pm
    Author:  regnier

  ==============================================================================
*/

#include "customStyle.h"


namespace juce
{
    void CustomLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
    {
        auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
        auto fill = slider.findColour(Slider::rotarySliderFillColourId);
        auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

        auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin(8.0f, radius * 0.2f);
        auto arcRadius = radius - lineW * 0.5f;

        Path backgroundArc;
        backgroundArc.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(outline);
        g.strokePath(backgroundArc, PathStrokeType(lineW-1, PathStrokeType::curved, PathStrokeType::rounded));

        if (slider.isEnabled())
        {
            Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);
            g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
        }

       
        Point<float> thumbPoint(bounds.getCentreX() + (arcRadius + lineW * 0.5) * std::cos(toAngle - MathConstants<float>::halfPi),
            bounds.getCentreY() + (arcRadius + lineW * 0.5) * std::sin(toAngle - MathConstants<float>::halfPi));

        g.setColour(slider.findColour(Slider::thumbColourId));
        g.drawLine(bounds.getCentreX(), bounds.getCentreY(), thumbPoint.getX(), thumbPoint.getY(), lineW);

    }

    Label* CustomLNF::createSliderTextBox(Slider& Slider) 
    {
        Label* CustomLNFLabelptr = LookAndFeel_V4::createSliderTextBox(Slider);
        CustomLNFLabelptr->setColour(Label::textColourId, juce::Colours::black);
        // CustomLNFLabelptr->setColour(Label::backgroundColourId, juce::Colours::black);
        CustomLNFLabelptr->setColour(Label::outlineColourId, juce::Colours::transparentWhite);
        CustomLNFLabelptr->setJustificationType(Justification::centredTop);
        return CustomLNFLabelptr;
    }






}