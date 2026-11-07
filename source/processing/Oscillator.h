#pragma once

#include <juce_dsp/juce_dsp.h>

#include "OscillatorFunctionType.h"

class Oscillator : public juce::dsp::Oscillator<float>
{
public:
    Oscillator();

    void disable();
    void enable();
    void prepareToPlay (const juce::dsp::ProcessSpec& processSpec);
    void renderNextBlock(const juce::dsp::ProcessContextReplacing<float>& context);
    void setBlendFunctionType(const OscillatorFunctionType& functionType);
    void setBlendRatio(float blendRatio);
    void setFunctionType(const OscillatorFunctionType& functionType);
    void setIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);

private:
    bool m_isEnabled {false};
    float m_blendRatio {0.0f}; // [0.0..1.0] Where 0.0 = 100% OSC -> 0.5 = 50%/50% -> 1.0 = 100% Blend OSC
    std::function<float(float)> m_function;
    std::function<float(float)> m_blendFunction;

    void updateFunction();
};


