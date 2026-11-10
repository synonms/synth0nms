#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

#include "ISoundModule.h"

class EnvelopeModule : public juce::ADSR, public ISoundModule
{
public:

    // ISoundModule
    void apply(juce::AudioBuffer<float>& audioBuffer, int startSample, int numSamples) override;
    void initialise(const juce::dsp::ProcessSpec& processSpec) override;

    void update(float attack, float decay, float sustain, float release);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);

private:
    juce::ADSR::Parameters m_adsrParameters;

};

