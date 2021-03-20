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
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr ; // we check if the SynthesiserSound is well casted >> expecting true
};
void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    oscData.setWaveFrequency(midiNoteNumber); // we choose the pitch of the note base on the midi key triggered
    adsrData.noteOn(); // we use this method from ADSR to start the enveloppe
    
};
void SynthVoice::stopNote (float velocity, bool allowTailoff)
{
  
    adsrData.noteOff(); // we turn off the enveloppe
    if (! allowTailoff || ! adsrData.isActive())
    {
        clearCurrentNote(); // to clear the sound once the key is not hold anymore >> NECESSARY?
    };
};
void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
};
void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
};
// METHODE PREPARE TO PLAY
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    //on peut utiliser le sample rate depuis l'ADSR (voir la doc)
    adsrData.setSampleRate(sampleRate);
    //
    juce::dsp::ProcessSpec spec ;
    spec.maximumBlockSize = samplesPerBlock ;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels ; // NB getTotalNumOutputChannels() n'existe pas ici, donc on créé un paramètre de plus dans la méthode 'outputChannels' (le troisième)
    
    // on peut finalement préparer notre instance de l'oscillateur grâce au ProcessSpec
    oscData.prepareToPlay(spec);
    // On prépare le gain également
//    gain.prepare(spec);
//    gain.setGainLinear(0.3f);
    gainData.prepareToPlay(spec);
//    gainData.setGain(0.3f);
//
    
    isPrepared = true;
};

void SynthVoice::updateAllDataParameters(const float attack, const float decay, const float sustain, const float release) // pour encapsuler tous les paramètres qui peuvent changer
{
    adsrData.updateADSR(attack, decay, sustain, release);
};

// METHOD RENDERNEXTBLOCK that we will call in the processor
void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    // jassert pour en fait déclarer 'if isPrepared has NOT been called, STOP project execution' >> traduction : tu n'as pas appelé prepareToPlay
    jassert (isPrepared); // NB jassert (isPrepared = true); = jassert (isPrepared);
    //si l'audio est vide on doit retourner un truc vide https://docs.juce.com/master/classSynthesiserVoice.html#a72ab7856c1e7651b1ce955388645a0a1
    if (!isVoiceActive())
        return; // cela veut dire que si la condition est vérifiée, la méthode renderNextBlock s'arrête ici
    
    
    // on récupère le buffer créé dans le header et on définit sa taille via : https://docs.juce.com/master/classAudioBuffer.html#a4434de94aa03d7db6d7ef06977ddf0ac qui gère bien la mémoire, on veut pas une nouvelle allocation (d'où les trois booléens)
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    // on nettoie ça pour l'appelle du renderNextBlock >> pour éviter le clicking
    synthBuffer.clear();
    
    // On crée un "alias" pour passer un AudioBlock avec le constructeur via AudioBuffer, aucune data n'est créée, c'est un alias pointant vers l'AudioBuffer
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    
    
    
    
    
    // On peut alors processer l'oscillateur NB : l'action de replace (vi le Process Context de la méthode process) va remplacer ce qui était dans l'audioBuffer avant le traitement
    oscData.getNextAudioBlock(audioBlock);
    
    // On process également le gain
//    gain.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    // CHANGEMENT PAR GAINDATA
    gainData.process(juce::dsp::ProcessContextReplacing<float> (audioBlock));
    
    // on applique l'ADSR à notre gain et osc
    adsrData.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples()); // rappelle, l'audioBlock est un alias de l'outputBuffer donc on traite bien ce qu'on a fait au dessus. Ce qu'on met dans l'audioBlock va dans l'audioBuffer
    
    
 
    // pour éviter le pb de clicking, on va créer un autre audiobuffer qui aura en mémoire ce qui est en cours
    //on ajoute notre synthBuffer à l'outputBuffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        // on utilise la méthode 'addFrom', on ajouter des samples d'un buffer à l'autre
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        // https://docs.juce.com/master/classSynthesiserVoice.html#a72ab7856c1e7651b1ce955388645a0a1 : if the sound that the voice is playing finishes during the course of this rendered block, it must call clearCurrentNote(), to tell the synthesiser that it has finished.
        if (!adsrData.isActive())
        {
            clearCurrentNote();
        };
    }
};


