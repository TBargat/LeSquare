/*
  ==============================================================================

    GainData.cpp
    Created: 20 Mar 2021 8:23:20pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include "GainData.h"

void GainData::prepareToPlay (juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
};
void GainData::setGain(const float gain)
{
    setGainLinear(gain);
};

