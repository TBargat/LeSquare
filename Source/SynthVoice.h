/*
  ==============================================================================

    SynthVoice.h
    Created: 20 Mar 2021 12:07:36pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "AdsrData.h"
#include "OscData.h"
#include "GainData.h"


class SynthVoice : public juce::SynthesiserVoice
{
    
    public :
    // There are some pure virtual methods we need to implement here (followed by override cause they are inherited)
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailoff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateAllDataParameters(const float attack, const float decay, const float sustain, const float release, const float gain, const int octave); 
    
    OscData& getOscillator () {return oscData;}; // Method to let our processor access directly to the oscillator to set the wave form
    
    private :
   
    AdsrData adsrData;
    OscData oscData;
    GainData gainData;

    juce::AudioBuffer<float> synthBuffer;

    bool isPrepared { false }; // Boolean used to validate the good processing of the prepare block
    
};
