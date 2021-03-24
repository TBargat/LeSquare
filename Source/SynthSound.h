/*
  ==============================================================================

    SynthSound.h
    Created: 20 Mar 2021 12:07:53pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> 


class SynthSound : public juce::SynthesiserSound
{
public:
    // Pure virtual methods that we need to implement
    bool appliesToNote (int midiNoteNumber) override {return true;}
    bool appliesToChannel (int midiChannel) override {return true;}
};
