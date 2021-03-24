/*
  ==============================================================================

    OscComponent.h
    Created: 20 Mar 2021 12:33:30pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    // We use our constructor to get the apvts >> it is just a reference
    OscComponent(juce::AudioProcessorValueTreeState& apvts);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void setOctaveSliderParams(juce::Slider& slider);
    void setOctaveLabelParams(juce::Label& label, juce::String labelText);
    void setOctaveLookAndFeel();
    
    juce::Slider octaveSlider;
    juce::LookAndFeel_V4 octaveLookAndFeel;
    juce::Label octaveLabel;
    
    // NB : we put it last here cause the objects are destructed bottom up when we close the app, it avoids it to crash
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> octaveAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
