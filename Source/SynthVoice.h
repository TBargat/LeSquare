/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Mar 2021 12:07:36pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> //Necessary to access Juce methods
#include "SynthSound.h" //Necessary to access the parameters and methods of SynthSound

/*
 This class inherits from SynthesiserVoice from Juce, we do this to be able to tweak our SynthSound objects.
 */
class SynthVoice : public juce::SynthesiserVoice
{
    
    public :
    // There are some pure virtual methods to implement here
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailoff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    
    private :
    
    
};
