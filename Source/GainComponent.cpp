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

}

GainComponent::~GainComponent()
{
}

void GainComponent::paint (juce::Graphics& g)
{
    // on fout tout en noir et supprime tout pour le moment
    g.fillAll(juce::Colours::black);
}

void GainComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10); // valeur random
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() /4 - padding; // chiffres basés sur l'expériences
    const auto sliderHeight= bounds.getHeight();
    const auto sliderStartX =0; // en haut à gauche, le début de l'UI
    const auto sliderStartY = 0;
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    
    gainSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);

}

void GainComponent::setGainSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
