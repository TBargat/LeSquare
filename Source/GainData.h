/*
  ==============================================================================

    GainData.h
    Created: 20 Mar 2021 8:23:20pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/*
 This class will help us to handle all the 'maths' behind our synth general Gain, it inherits from juce::dsp::Gain class to take the most of Juce library
 */
class GainData : public juce::dsp::Gain<float>
{
public :
    
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setGain(const float gain);

    private :
};

