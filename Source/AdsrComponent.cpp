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
    
    
    
    //on gère bloc par bloc le LookAndFeel
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
    // on fout tout en noir et supprime tout pour le moment
    g.fillAll(juce::Colour::fromRGB(186, 189, 194));
}

void AdsrComponent::resized()
{
    // On fait apparaitre nos sliders avec des règles entre eux
    //NB : il existe plusieurs méthodes (ici on est en static, on aurait pu utiliser flexbox également par exemple)
    const auto bounds = getLocalBounds().reduced(10); // valeur random
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding; // chiffres basés sur l'expériences
    const auto sliderHeight= bounds.getHeight() - padding;
    const auto sliderStartX = padding; // en haut à gauche, le début de l'UI
    const auto sliderStartY = padding;
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    
    attackLabel.setBounds(sliderStartX, sliderStartY, sliderWidth, padding * 2);
    attackSlider.setBounds(sliderStartX, attackLabel.getBottom() + padding, sliderWidth, sliderHeight - attackLabel.getBottom());
    decayLabel.setBounds(attackSlider.getRight() + padding, attackLabel.getY(), sliderWidth, padding * 2);
    decaySlider.setBounds(attackSlider.getRight() + padding, attackSlider.getY(), sliderWidth, sliderHeight - attackLabel.getBottom());
    sustainLabel.setBounds(decaySlider.getRight() + padding, attackLabel.getY(), sliderWidth, padding * 2);
    sustainSlider.setBounds(decaySlider.getRight() + padding, attackSlider.getY(), sliderWidth, sliderHeight - attackLabel.getBottom());
    releaseLabel.setBounds(sustainSlider.getRight() + padding, attackLabel.getY(), sliderWidth, padding * 2);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, attackSlider.getY(), sliderWidth, sliderHeight - attackLabel.getBottom());
    
    
    
    //on peut utiliser ces valeurs pour nos sliders maintenant
    // NB : les variables au dessus rende le code modifiable et extensible
    

}
// On rajoute ça en changeant la classe parente >> on remplace TapSynthAudioProcessorEditor par AdsrComponent
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
    attackLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(255, 172, 64)); //couleur fadder
    attackLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(255, 227, 191)); //couleur Background barre
    attackLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(252, 193, 116)); // couleur barre
    attackSlider.setLookAndFeel(&attackLookAndFeel);
}
void AdsrComponent::setDecayLookAndFeel()
{
    decayLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(247, 230, 77)); //couleur fadder
    decayLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(255, 248, 181)); //couleur Background barre
    decayLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(255, 242, 125)); // couleur barre
    decaySlider.setLookAndFeel(&decayLookAndFeel);
}
void AdsrComponent::setSustainLookAndFeel()
{
    sustainLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(144, 237, 97)); //couleur fadder
    sustainLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(206, 240, 189)); //couleur Background barre
    sustainLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(170, 232, 139)); // couleur barre
    sustainSlider.setLookAndFeel(&sustainLookAndFeel);
    
}
void AdsrComponent::setReleaseLookAndFeel()
{
    releaseLookAndFeel.setColour (juce::Slider::thumbColourId, juce::Colour::fromRGB(102, 200, 242)); //couleur fadder
    releaseLookAndFeel.setColour (juce::Slider::backgroundColourId , juce::Colour::fromRGB(218, 234, 242)); //couleur Background barre
    releaseLookAndFeel.setColour (juce::Slider::trackColourId, juce::Colour::fromRGB(180, 220, 237)); // couleur barre
    releaseSlider.setLookAndFeel(&releaseLookAndFeel);
}
