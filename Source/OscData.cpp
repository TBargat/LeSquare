/*
  ==============================================================================

    OscData.cpp
    Created: 20 Mar 2021 12:32:57pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include "OscData.h"


void OscData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
    prepare(spec);    
};


// This is our SQUARE WAVEFORM HERE :)
void OscData::setOscWaveType()
{
  initialise ([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
};


void OscData::setWaveFrequency (const int midiNoteNumber)
{
    // We can manage the octave change like that
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((midiNoteNumber + currentOctave)));
    currentMideNoteFrequency = midiNoteNumber;
};

void OscData::setOctave (const int octave)
{
    // Our slider move from -1 to 1 with INT steps. That means we actually go from -1 semi-tone to +1 semi-tone.
    // Since we want to switch between +1 octave and -1 octave, we actually need to move of 12 semi-tones
    currentOctave = octave*12;
    setFrequency (juce::MidiMessage::getMidiNoteInHertz ((currentMideNoteFrequency + currentOctave)));
    
}

void OscData::getNextAudioBlock (juce::dsp::AudioBlock<float>& audioBlock)
{
    process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
};
