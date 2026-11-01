#pragma once

#include <juce_dsp/juce_dsp.h>

class Filter
{
public:
    void prepareToPlay (const juce::dsp::ProcessSpec& processSpec);
    void renderNextBlock(juce::dsp::ProcessContextReplacing<float>& context);
    void updateParameters(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance, float modulator = 1.0f);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> m_filter;
};
