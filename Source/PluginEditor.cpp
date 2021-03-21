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
    setSize (400, 300);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(gainComponent);
    addAndMakeVisible(oscComponent);
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
    adsrComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
    gainComponent.setBounds(0, 0, getWidth() / 2, getHeight());
    oscComponent.setBounds(getWidth() / 4, 0, getWidth() / 2, getHeight());
}
