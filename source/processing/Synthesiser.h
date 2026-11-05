#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "../StateParameters.h"

class Synthesiser : public juce::Synthesiser
{
public:
    Synthesiser(StateParameters& stateParameters);

    void initialise (double sampleRate, int samplesPerBlock, int numOutputChannels);
    void processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer);

private:
    StateParameters& m_stateParameters;
};

