/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeSquareAudioProcessorEditor::LeSquareAudioProcessorEditor (LeSquareAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsrComponent (audioProcessor.apvts), gainComponent(audioProcessor.apvts), oscComponent(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 400);
    addAndMakeVisible(oscComponent);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(gainComponent);
    
    
}

LeSquareAudioProcessorEditor::~LeSquareAudioProcessorEditor()
{
}

//==============================================================================
void LeSquareAudioProcessorEditor::paint (juce::Graphics& g)
{
    //Tout en gris
    g.fillAll(juce::Colour::fromRGB(186, 189, 194));
}

void LeSquareAudioProcessorEditor::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto oneSixthWidth = bounds.getWidth()/6;
    
    
    oscComponent.setBounds(0, 0, oneSixthWidth, getHeight());
    adsrComponent.setBounds(oscComponent.getRight(), 0, oneSixthWidth * 4, getHeight());
    gainComponent.setBounds(adsrComponent.getRight(), 0, oneSixthWidth, getHeight());
    
}
