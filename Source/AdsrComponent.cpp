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
// On ajoute également le paramètre de l'étape 64 ici et on peut donc changer le premier paramètre de nos attachments : de à audioProcessor.apvts à simplement apvts, et on appellera en fait audioProcessor.apvts dans notre Editor via cette méthode :)
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment; // pour refacto clean
    
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider); // on doit faire référence au Audioprocessor Value Tree State
    //NB: c'est là qu'on aloue de la mémoire pour l'attachnment
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    // on peut donc de façon plus élégante dessiner nos sliders :
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
    // on doit ensuite aller dans le resized pour le mettre à l'écran

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    // on fout tout en noir et supprime tout pour le moment
    g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
    // On fait apparaitre nos sliders avec des règles entre eux
    //NB : il existe plusieurs méthodes (ici on est en static, on aurait pu utiliser flexbox également par exemple)
    const auto bounds = getLocalBounds().reduced(10); // valeur random
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() /4 - padding; // chiffres basés sur l'expériences
    const auto sliderHeight= bounds.getHeight();
    const auto sliderStartX =0; // en haut à gauche, le début de l'UI
    const auto sliderStartY = 0;
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight); // on le place par rapport au premier
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}
// On rajoute ça en changeant la classe parente >> on remplace TapSynthAudioProcessorEditor par AdsrComponent
void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
