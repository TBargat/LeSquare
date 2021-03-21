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

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    // on fout tout en noir et supprime tout pour le moment
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10); // valeur random
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() /4 - padding; // chiffres basés sur l'expériences
    const auto sliderHeight= bounds.getHeight();
    const auto sliderStartX =0; // en haut à gauche, le début de l'UI
    const auto sliderStartY = 0;
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    
    octaveSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);

}

void OscComponent::setOctaveSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}

