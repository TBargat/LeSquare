/*
  ==============================================================================

    SynthSound.h
    Created: 20 Mar 2021 12:07:53pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> //Necessary to access Juce methods

/*
    This class inherits from SynthesiserSound from Juce, we do this to be able to tweak our SynthSound objects.
 */
class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override {return true;} // pure virtual methods that we need to implement
    bool appliesToChannel (int midiChannel) override {return true;}
};
