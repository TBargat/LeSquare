/*
  ==============================================================================

    OscComponent.cpp
    Created: 20 Mar 2021 12:33:30pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    octaveAttachment = std::make_unique<SliderAttachment>(apvts, "OCTAVE", octaveSlider);
    setOctaveSliderParams(octaveSlider);
    setOctaveLookAndFeel();
    setOctaveLabelParams(octaveLabel, "OcT");
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(186, 189, 194));
}

void OscComponent::resized()
{
    // We create const to easily handle our position rules
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()  - padding;
    const auto sliderHeight= bounds.getHeight() - padding;
    const auto sliderStartX = padding;
    const auto sliderStartY = padding;
    
    octaveLabel.setBounds(sliderStartX, sliderStartY, sliderWidth, padding * 2);
    octaveSlider.setBounds(sliderStartX, octaveLabel.getBottom() + padding, sliderWidth, sliderHeight - octaveLabel.getBottom());
}

void OscComponent::setOctaveSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
    addAndMakeVisible(slider);
}

void OscComponent::setOctaveLabelParams(juce::Label& label, juce::String labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void OscComponent::setOctaveLookAndFeel()
{
    octaveLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(77, 77, 77));
    octaveLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(255, 255, 255));
    octaveLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(125, 125, 125));
    octaveSlider.setLookAndFeel(&octaveLookAndFeel);
}
