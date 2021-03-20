/*
  ==============================================================================

    AdsrData.h
    Created: 20 Mar 2021 12:32:46pm
    Author:  Thibault Bargat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h> //Necessary to access Juce methods

/*
 This class will help us to handle all the 'maths' behind our voice amp enveloppe (ADSR), it inherits from juce::ADSR class 
 */

class AdsrData : public juce::ADSR
{
public:
    //on prototype notre méthode ici :
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
    
private:
    
    juce::ADSR::Parameters adsrParams;
};
