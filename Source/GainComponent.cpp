/*
  ==============================================================================

    GainComponent.cpp
    Created: 20 Mar 2021 8:22:59pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GainComponent.h"

//==============================================================================
GainComponent::GainComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; // pour refacto clean
    gainAttachment = std::make_unique<SliderAttachment>(apvts, "GAIN", gainSlider);
    setGainSliderParams(gainSlider);
    setGainLookAndFeel();
    setGainLabelParams(gainLabel, "VoL");
    
}

GainComponent::~GainComponent()
{
}

void GainComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(186, 189, 194));
}

void GainComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()  - padding;
    const auto sliderHeight= bounds.getHeight() - padding;
    const auto sliderStartX = 10;
    const auto sliderStartY = 10;
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    
    gainLabel.setBounds(sliderStartX, sliderStartY, sliderWidth, padding * 2);
    gainSlider.setBounds(sliderStartX, gainLabel.getBottom() + padding, sliderWidth, sliderHeight - gainLabel.getBottom());

}

void GainComponent::setGainSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
    addAndMakeVisible(slider);

    
    
}
void GainComponent::setGainLabelParams(juce::Label& label, juce::String labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void GainComponent::setGainLookAndFeel()
{
    gainLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(247, 117, 92)); //couleur fadder
    gainLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(252, 186, 169)); //couleur Background barre
    gainLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(255, 137, 107)); // couleur barre
    gainSlider.setLookAndFeel(&gainLookAndFeel);
}


