/*
  ==============================================================================

    GainData.h
    Created: 20 Mar 2021 8:23:20pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainData : public juce::dsp::Gain<float>
{
public :
    
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setGain(float gain);

    private :
};

