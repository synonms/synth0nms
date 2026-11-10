#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "../StateParameters.h"
#include "CircularBuffer.h"
#include "modules/MasterModule.h"

class Synthesiser : public juce::Synthesiser
{
public:
    Synthesiser(StateParameters& stateParameters);

    void initialise (double sampleRate, int samplesPerBlock, int numOutputChannels);
    void processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer);

    MasterModule& getMasterModule()
    {
        return m_masterModule;
    }

private:
    StateParameters& m_stateParameters;
    CircularBuffer m_circularBuffer;
    MasterModule m_masterModule;
};

