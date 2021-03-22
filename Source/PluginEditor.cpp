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
    setSize (1200, 400);
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
    //Tout en noir pour le moment
    g.fillAll(juce::Colours::black);
}

void LeSquareAudioProcessorEditor::resized()
{
    oscComponent.setBounds(0, 0, 200, getHeight());
    adsrComponent.setBounds(oscComponent.getRight(), 0, 800, getHeight());
    gainComponent.setBounds(adsrComponent.getRight(), 0, 200, getHeight());
    
}
