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
    
    juce::Slider octaveSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> octaveAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
