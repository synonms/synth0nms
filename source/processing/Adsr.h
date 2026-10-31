#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

class Adsr : public juce::ADSR
{
public:
    void prepareToPlay (const juce::dsp::ProcessSpec& processSpec);
    void update(float attack, float decay, float sustain, float release);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples);

private:
    juce::ADSR::Parameters m_adsrParameters;

};

