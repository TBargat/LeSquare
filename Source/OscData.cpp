/*
  ==============================================================================

    OscData.cpp
    Created: 20 Mar 2021 12:32:57pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include "OscData.h"

// on ajoute la méthode créée juste ici, on récupère oscData.prepare(spec); dans synthVoice
void OscData::prepareToPlay(juce::dsp::ProcessSpec &spec)
{
    prepare(spec); // on l'a renommé après le refactoring OscData, c'est toujours un Oscillator, donc les méthodes fonctionnent
    
};


void OscData::setOscWaveType()
{
  initialise ([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
};


void OscData::setWaveFrequency (const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)); // on l'a renommé après le refactoring OscData, c'est toujours un Oscillator, donc les méthodes fonctionnent); // on l'a renommé après le refactoring OscData, c'est toujours un Oscillator, donc les méthodes fonctionnent
};



// on va rappatrier  oscData.process(juce::dsp::ProcessContextReplacing<float> (audioBlock)); depuis le SynthVoice
// NB, il y aura besoin d'un argument de type juce::dsp::AudioBlock<float>

void OscData::getNextAudioBlock (juce::dsp::AudioBlock<float>& audioBlock)
{
    process(juce::dsp::ProcessContextReplacing<float> (audioBlock)); // on l'a renommé après le refactoring OscData, c'est toujours un Oscillator, donc les méthodes fonctionnent
};
