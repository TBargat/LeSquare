/*
  ==============================================================================

    AdsrComponent.h
    Created: 20 Mar 2021 12:33:16pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    //On utilise notre constructeur pour récupérer notre ValueTree //NB, dans la structure précédente on avait simplement un référence à notre processor appeelée audioProcessor qui nous permettait de récupérer apvts comme ça : audioProcessor.apvts
    //NB : on créé une référence de apvts, on ne veut PAS le copier
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    
    
    
    void setSliderParams(juce::Slider& slider);
    void setSliderLabelParams(juce::Label& label, juce::String labelText);
    void setAttackLookAndFeel();
    void setDecayLookAndFeel();
    void setSustainLookAndFeel();
    void setReleaseLookAndFeel();
    
    
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    juce::LookAndFeel_V4 attackLookAndFeel;
    juce::LookAndFeel_V4 decayLookAndFeel;
    juce::LookAndFeel_V4 sustainLookAndFeel;
    juce::LookAndFeel_V4 releaseLookAndFeel;
    
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    
    //n ajoute les attachments de l'adsr
    //il faut connecter nos params du Value Tree du PluginProcessor avec nos objets créés ci-dessus >> on utilise des "attachments"
    // refactoring plus clean :
    //NB: on les place en dessous car ils doivent être détruits en premier à la fermeture de l'app
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    
    std::unique_ptr<SliderAttachment> attackAttachment; // un unique_pointr ici c'est parce qu'on controle un visual attachment, ça n'a pas besoin d'exister quand on ferme l'appli
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    //NB : les unique_ptr permettent de mieux gérer la mémoire >> lorsqu'on ferme l'appli ça libère directement l'espace dans la mémoire
    //On peut aussi les mettre sur nos sliders
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
