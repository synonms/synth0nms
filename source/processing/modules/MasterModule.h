#pragma once

#include <juce_dsp/juce_dsp.h>

#include "ISoundModule.h"

class MasterModule : public ISoundModule
{
public:
    virtual ~MasterModule() = default;

    // ISoundModule
    void apply(juce::AudioBuffer<float>& audioBuffer, int startSample, int numSamples) override;
    void initialise(const juce::dsp::ProcessSpec& processSpec) override;

    void setGain(const float gain)
    {
        m_gain.setGainLinear(std::clamp(gain, 0.0f, 1.0f));
    }

    float getRmsValue(const int channel) const
    {
        return channel < 0 || channel > 1
            ? -60.f
            : m_rmsLevelsInDecibels[channel].getCurrentValue();
    }

private:
    juce::dsp::Gain<float> m_gain;
    juce::LinearSmoothedValue<float> m_rmsLevelsInDecibels[2] { -60.f, -60.f };
};
