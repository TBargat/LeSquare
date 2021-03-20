/*
  ==============================================================================

    GainComponent.h
    Created: 20 Mar 2021 8:22:59pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GainComponent  : public juce::Component
{
public:
    GainComponent(juce::AudioProcessorValueTreeState& apvts);
    ~GainComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void setGainSliderParams(juce::Slider& slider);
    
    juce::Slider gainSlider;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> gainAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};