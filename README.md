# LeSquare

## Description of the project

LeSquare is a basic AU-plugin synthesizer made in C++ with the Juce framework.
It is an exercice to apply the different notions I learned about Juce and audio programming over the 2 past weeks.

## LeSquare's feature

LeSquare is a monophonic synthesizer with one square wave oscillator.

The user can change the following parameters through the UI :

- The Octave (choice between : -1, 0 and +1)
- The Amp ADSR enveloppe (with 4 sliders to control Attack, Decay, Sustain and Release)
- The general gain of the output (our VCA here)

NB : it accepts midi input, so any midi keyboard can control the picth of our synthesizer's voice

## LeSquare's architecture

I tried to take the most of Juce library and of OOP concepts to make the code more readable and ready for further implementations if needed.

While I tried to keep the "maths" in the AudioProcessor and the graphic part in our Editor, I created several levels of abstractions as followed :

- For the "maths" and process :
    AudioProcessor >> (SynthVoice and SynthSound)
    Synthvoice >> (AdsrData and OscData and GainData)

- For the interface and UI :
    Editor >> (AdsrComponent and OscComponent and GainComponent)
    
    
The interaction of the UI and the DATA occurs thanks to the use of attachnements and a value tree.

## LeSquare's Design

I wanted to keep the interface very minimalist and pure, my instpiration for the colours and palettes was the OP-Z.

## How to use LeSquare

NB : it's an AU plugin, meaning it only works on Mac OS.

Dowload the zip of this repo.
Open Projucer on your computer (you can dowload it here : https://juce.com/discover/projucer).
Open the LeSquare.jucer file.
Export it on Xcode.
Build the project.

You can now open the plugin in any audio program that can host AU plugins.