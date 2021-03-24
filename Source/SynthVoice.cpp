/*
  ==============================================================================

    SynthVoice.cpp
    Created: 20 Mar 2021 12:07:36pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr ; // We check if the SynthesiserSound is well casted >> expecting true
};
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    oscData.setWaveFrequency(midiNoteNumber); // We choose the pitch of the note base on the midi key triggered
    adsrData.noteOn(); // We use this method from ADSR to start the enveloppe
};
void SynthVoice::stopNote (float velocity, bool allowTailoff)
{
  
    adsrData.noteOff(); // We turn off the enveloppe
    if (! allowTailoff || ! adsrData.isActive())
    {
        clearCurrentNote(); // To clear the sound once the key is not hold anymore
    };
};
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
};
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    // adsrData inherits from ADSR, and it allows us to set the sampleRate
    adsrData.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec ;
    spec.maximumBlockSize = samplesPerBlock ;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels ; // NB : getTotalNumOutputChannels() doesn't exist in the SynthVoice context (we are not in the AudioProcessor), that's why we add this third parameter to our method
    
    oscData.prepareToPlay(spec);
    gainData.prepareToPlay(spec);
    
    isPrepared = true; // Boolean we'll use in a jassert in renderNextBlock
};

void SynthVoice::updateAllDataParameters(const float attack, const float decay, const float sustain, const float release, const float gain, const int octave)
{
    adsrData.updateADSR(attack, decay, sustain, release);
    oscData.setOctave(octave);
    gainData.setGain(gain);
};

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    // jassert to do a quick check : 'if isPrepared has NOT been called, STOP project execution' i.e. prepareToPlay wasn't called correctly
    jassert (isPrepared);
    
    // If there is no audio, we need to end the renderNextBlock. The documentation states : "If the voice is currently silent, it should just return without doing anything."
    if (!isVoiceActive())
        return;
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    // We create an alias to pass an AudioBlock thanks to the AudioBuffer synthBuffer. No data is created, it's just an alias pointing to the AudioBuffer
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    oscData.getNextAudioBlock(audioBlock);
    gainData.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    adsrData.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    // To avoid clicking we create a new audioBuffer to store the current audio
    // And we add our synthBuffer to the outpubuffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        // NB : the documentation states that if the sound that the voice is playing finishes during the course of this rendered block, it must call clearCurrentNote(), to tell the synthesiser that it has finished.
        if (!adsrData.isActive())
        {
            clearCurrentNote();
        };
    }
};


