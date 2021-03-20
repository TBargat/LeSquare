/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h" //Necessary to access SynthSound
#include "SynthVoice.h" //Necessary to access SynthVoice

//==============================================================================
/**
*/
class LeSquareAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    LeSquareAudioProcessor();
    ~LeSquareAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // on met l'APVTS ici, mais c'est mieux de le mettre en privé en général >> il faut passer par une autre méthode pour l'appeler quand c'est privé ?
    juce::AudioProcessorValueTreeState apvts;
    
private:
    
    juce::Synthesiser synth; //Creation of our Synthesiser Object
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); // we create a value tree to communicate the parameters with our UI
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeSquareAudioProcessor)
};
