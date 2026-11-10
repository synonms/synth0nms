#pragma once

#include <juce_dsp/juce_dsp.h>

#include "ISoundModule.h"

class FilterModule : public ISoundModule
{
public:
    virtual ~FilterModule() = default;

    // ISoundModule
    void apply(juce::AudioBuffer<float>& audioBuffer, int startSample, int numSamples) override;
    void initialise(const juce::dsp::ProcessSpec& processSpec) override;

    void updateParameters(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance, float modulator = 1.0f);
    void reset();

private:
    juce::dsp::StateVariableTPTFilter<float> m_filter;
};
