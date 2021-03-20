/*
  ==============================================================================

    OscData.h
    Created: 20 Mar 2021 12:32:57pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> //Necessary to access Juce methods


/*
 This class will help us to handle all the 'maths' behind our synth Oscillator, it inherits from juce::dsp::Oscillator class to take the most of Juce library
 */
class OscData : public juce::dsp::Oscillator<float>
{
public :
    //on prend tout ce qui est relatif à l'OSCILLATEUR dans le SynthVoice, et on le rappatrie ici pour le gérer de façon plus éloignée
    void prepareToPlay (juce::dsp::ProcessSpec& spec); // quand on regarde dans le Synthvoic on voit que ça nécessite un ProcessSpec, juste une référence encore une fois
    
    //on va créer une méthode de sélection d'oscillateur
    void setOscWaveType ();
    
    //on récupère la méthode setFrequency aussi (qui est dans le startNote de synthVoice)
    void setWaveFrequency (const int midiNoteNumber);
    
    
    
    //on ajoute la méthode ici également :
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& audioBlock);
    
private :
    
};
