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
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; // pour refacto clean
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
    // on fout tout en noir et supprime tout pour le moment
    g.fillAll(juce::Colour::fromRGB(186, 189, 194));
}

void OscComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10); // valeur random
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth()  - padding; // chiffres basés sur l'expériences
    const auto sliderHeight= bounds.getHeight() - padding;
    const auto sliderStartX =10; // en haut à gauche, le début de l'UI
    const auto sliderStartY = 10;
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    
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
    octaveLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(77, 77, 77)); //couleur fadder
    octaveLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(255, 255, 255)); //couleur Background barre
    octaveLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(125, 125, 125)); // couleur barre
    octaveSlider.setLookAndFeel(&octaveLookAndFeel);
}
