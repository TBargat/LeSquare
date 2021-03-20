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
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels); // to use our prepare to play
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateAllDataParameters(const float attack, const float decay, const float sustain, const float release); 
    
    OscData& getOscillator () {return oscData;}; //method to let our processor access directly to the oscillator
    GainData& getGain () {return gainData;};
    
    private :
   
    AdsrData adsrData; // To handle our adsr logic part
    OscData oscData; // To handle our OSC logic part

    juce::dsp::Gain<float> gain; // Gain, will need to be refactored probably
    
    GainData gainData; // to handle our Gain
    
    juce::AudioBuffer<float> synthBuffer; // creation of the buffer

    bool isPrepared { false }; // boolean used to validated the good processing of the prepare block
    
};
