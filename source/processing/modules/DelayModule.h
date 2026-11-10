#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

#include "ISoundModule.h"
#include "../CircularBuffer.h"

class DelayModule : public ISoundModule
{
public:
    DelayModule(CircularBuffer& circularBuffer);
    virtual ~DelayModule() = default;

    // ISoundModule
    void apply(juce::AudioBuffer<float>& audioBuffer, int startSample, int numSamples) override;
    void initialise(const juce::dsp::ProcessSpec& processSpec) override;

    void update(const float delayInSeconds, const float intensity)
    {
        m_delayInSeconds = delayInSeconds;
        m_intensity = intensity;
    }

private:
    CircularBuffer& m_circularBuffer;
    float m_sampleRate {44100};
    float m_delayInSeconds { 0.5f };
    float m_intensity {0.5f};
};

