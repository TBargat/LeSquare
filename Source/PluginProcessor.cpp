/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeSquareAudioProcessor::LeSquareAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth.addSound(new SynthSound()); // Creation of the synthsound
    synth.addVoice(new SynthVoice()); // We create a monophonic synth here >> juste one voice is constructed
}

LeSquareAudioProcessor::~LeSquareAudioProcessor()
{
}

//==============================================================================
const juce::String LeSquareAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LeSquareAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LeSquareAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LeSquareAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LeSquareAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LeSquareAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LeSquareAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LeSquareAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LeSquareAudioProcessor::getProgramName (int index)
{
    return {};
}

void LeSquareAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LeSquareAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate); // we set de SampleRate to our synth based on the input
    //on utilise la méthode prepareToPlay de notre classe SynthVoice
    for (int i = 0; i < synth.getNumVoices(); i ++)
    {
        //synth.getVoice(i) // /!\ récupère chaque voix, getVoice retourn un SynthesiserVoice, pas un SynthVoice, on doit donc caster
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) // SynthVoice* = un pointer SynthVoice
        {
            voice -> prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels()); // sur la ligne du dessus cette méthode ne serait jamais apparue car on manipulait un SynthesiserVoice
            // rappel : getTotalNumOutputChannels() a été créé exprès aux étapes précédentes
        }
    }
}

void LeSquareAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LeSquareAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void LeSquareAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // loop created to modify our voices - the code is ready to handle polyphony
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            
            voice->updateAllDataParameters(0.1f, 1.0f, 1.0f, 1.0f);
            voice->getOscillator().setOscWaveType(); 
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples()); // we get the voices (just one with the monophonic synth) we played with a renderNextBlock
}

//==============================================================================
bool LeSquareAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LeSquareAudioProcessor::createEditor()
{
    return new LeSquareAudioProcessorEditor (*this);
}

//==============================================================================
void LeSquareAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LeSquareAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LeSquareAudioProcessor();
}


