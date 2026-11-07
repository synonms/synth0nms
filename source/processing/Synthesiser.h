#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "../StateParameters.h"

class Synthesiser : public juce::Synthesiser
{
public:
    Synthesiser(StateParameters& stateParameters);

    void initialise (double sampleRate, int samplesPerBlock, int numOutputChannels);
    void processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer);

    float getRmsValue(const int channel) const
    {
        return channel < 0 || channel > 1
            ? -60.f
            : m_rmsLevelsInDecibels[channel].getCurrentValue();
    }

private:
    StateParameters& m_stateParameters;
    juce::LinearSmoothedValue<float> m_rmsLevelsInDecibels[2] { -60.f, -60.f };
};

