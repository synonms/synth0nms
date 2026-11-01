#pragma once

#include <juce_dsp/juce_dsp.h>

class Filter
{
public:
    void prepareToPlay (const juce::dsp::ProcessSpec& processSpec);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, const juce::MidiBuffer& midiBuffer, int startSample, int numSamples);
    void updateParameters(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> m_filter;
};
