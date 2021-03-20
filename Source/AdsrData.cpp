/*
  ==============================================================================

    AdsrData.cpp
    Created: 20 Mar 2021 12:32:46pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include "AdsrData.h"
//ce n'est pas un SynthVoice du coup
void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release) //const car on lit la donnée, on n'a pas besoin de la définir, revoir les noms pour éviter la confusion peut-être
{
    adsrParams.attack = attack; // rappel : c'est un objet de type ADSR, il a donc les attributs attack, decay etc...
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    // On ajoute ensuite c'est params à notre ADSR comme suit :
    setParameters(adsrParams);
};
