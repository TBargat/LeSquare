/*
  ==============================================================================

    OscData.h
    Created: 20 Mar 2021 12:32:57pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> 


/*
 This class will help us to handle all the 'maths' behind our synth Oscillator, it inherits from juce::dsp::Oscillator class to take the most of Juce library
 */
class OscData : public juce::dsp::Oscillator<float>
{
public :

    // This is the lowest level of prepareToPlay management here
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    
    void setOscWaveType ();
    
    void setWaveFrequency (const int midiNoteNumber);

    void setOctave (const int octave);
   
    
    
    // This is the lowest level of audioBlock management here
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& audioBlock);
    
private :
    
    int currentOctave { 0 };
    int currentMideNoteFrequency { 0 };
    
};
