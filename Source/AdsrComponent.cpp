/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 20 Mar 2021 12:33:16pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
    
    setAttackLookAndFeel();
    setDecayLookAndFeel();
    setSustainLookAndFeel();
    setReleaseLookAndFeel();
    
    setSliderLabelParams(attackLabel, "A");
    setSliderLabelParams(decayLabel, "D");
    setSliderLabelParams(sustainLabel, "S");
    setSliderLabelParams(releaseLabel, "R");
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(186, 189, 194));
}

void AdsrComponent::resized()
{
    // We create const to easily handle our position rules
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding; // We divide by 4 cause we have 4 sliders in our component
    const auto sliderHeight= bounds.getHeight() - padding;
    const auto sliderStartX = padding;
    const auto sliderStartY = padding;
    
    
    attackLabel.setBounds(sliderStartX, sliderStartY, sliderWidth, padding * 2);
    attackSlider.setBounds(sliderStartX, attackLabel.getBottom() + padding, sliderWidth, sliderHeight - attackLabel.getBottom());
    
    decayLabel.setBounds(attackSlider.getRight() + padding, attackLabel.getY(), sliderWidth, padding * 2);
    decaySlider.setBounds(attackSlider.getRight() + padding, attackSlider.getY(), sliderWidth, sliderHeight - attackLabel.getBottom());
    
    sustainLabel.setBounds(decaySlider.getRight() + padding, attackLabel.getY(), sliderWidth, padding * 2);
    sustainSlider.setBounds(decaySlider.getRight() + padding, attackSlider.getY(), sliderWidth, sliderHeight - attackLabel.getBottom());
    
    releaseLabel.setBounds(sustainSlider.getRight() + padding, attackLabel.getY(), sliderWidth, padding * 2);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, attackSlider.getY(), sliderWidth, sliderHeight - attackLabel.getBottom());
    
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
    addAndMakeVisible(slider);
}

void AdsrComponent::setSliderLabelParams(juce::Label& label, juce::String labelText)
{
    label.setText(labelText, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void AdsrComponent::setAttackLookAndFeel()
{
    attackLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(255, 172, 64));
    attackLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(255, 227, 191));
    attackLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(252, 193, 116));
    attackSlider.setLookAndFeel(&attackLookAndFeel);
}

void AdsrComponent::setDecayLookAndFeel()
{
    decayLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(247, 230, 77));
    decayLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(255, 248, 181));
    decayLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(255, 242, 125));
    decaySlider.setLookAndFeel(&decayLookAndFeel);
}

void AdsrComponent::setSustainLookAndFeel()
{
    sustainLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(144, 237, 97));
    sustainLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(206, 240, 189));
    sustainLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(170, 232, 139));
    sustainSlider.setLookAndFeel(&sustainLookAndFeel);
    
}

void AdsrComponent::setReleaseLookAndFeel()
{
    releaseLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(102, 200, 242));
    releaseLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(218, 234, 242));
    releaseLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(180, 220, 237));
    releaseSlider.setLookAndFeel(&releaseLookAndFeel);
}
