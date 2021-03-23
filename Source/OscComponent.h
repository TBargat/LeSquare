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
    
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> octaveAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
