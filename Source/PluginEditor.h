/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"
#include "GainComponent.h"

//==============================================================================
/**
*/
class LeSquareAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LeSquareAudioProcessorEditor (LeSquareAudioProcessor&);
    ~LeSquareAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LeSquareAudioProcessor& audioProcessor;
    // We add our three component objects created in the UI
    AdsrComponent adsrComponent;
    GainComponent gainComponent;
    OscComponent oscComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeSquareAudioProcessorEditor)
};
