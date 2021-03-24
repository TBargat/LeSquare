/*
  ==============================================================================

    AdsrData.cpp
    Created: 20 Mar 2021 12:32:46pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#include "AdsrData.h"


void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
// We use const cause we just need to read the data, no need to define it
{
    adsrParameters.attack = attack; 
    adsrParameters.decay = decay;
    adsrParameters.sustain = sustain;
    adsrParameters.release = release;
    // We can now set the parameters with this ADSR class' method
    setParameters(adsrParameters);
};
