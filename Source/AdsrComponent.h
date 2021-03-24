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
    // We use our constructor to get the apvts >> it is just a reference
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
    
    // NB : we put them last here cause the objects are destructed bottom up when we close the app, it avoids it to crash
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    //NB : unique_ptr allows us to improve memory management >> when we close the app, it frees up memory
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
