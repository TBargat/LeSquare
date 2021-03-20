/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h" //Necessary to access AdsrComponent
#include "OscComponent.h" //Necessary to access OscComponent

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
    // On instancie un AdsrComponent pour avoir accès à nos sliders
    AdsrComponent adsrComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeSquareAudioProcessorEditor)
};
