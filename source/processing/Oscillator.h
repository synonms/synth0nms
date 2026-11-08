#pragma once

#include <juce_dsp/juce_dsp.h>

#include "OscillatorFunctionType.h"
#include "ISoundModule.h"

class Oscillator : public juce::dsp::Oscillator<float>, public ISoundModule
{
public:
    Oscillator();

    // ISoundModule
    void apply(juce::AudioBuffer<float>& audioBuffer, int startSample, int numSamples) override;
    void initialise(const juce::dsp::ProcessSpec& processSpec) override;

    void setBlendFunctionType(const OscillatorFunctionType& functionType);
    void setBlendRatio(float blendRatio);
    void setFunctionType(const OscillatorFunctionType& functionType);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);

private:
    float m_blendRatio {0.0f}; // [0.0..1.0] Where 0.0 = 100% OSC -> 0.5 = 50%/50% -> 1.0 = 100% Blend OSC
    std::function<float(float)> m_function;
    std::function<float(float)> m_blendFunction;

    void updateFunction();
};


