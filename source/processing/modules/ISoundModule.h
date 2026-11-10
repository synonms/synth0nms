#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

class ISoundModule
{
protected:
    ~ISoundModule() = default;
    bool isEnabled {true};

public:
    virtual void initialise(const juce::dsp::ProcessSpec& processSpec) = 0;
    virtual void apply(juce::AudioBuffer<float>& audioBuffer, int startSample, int numSamples) = 0;

    void setIsEnabled(const bool value) { isEnabled = value; }
};
