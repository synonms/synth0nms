#pragma once

#include <juce_dsp/juce_dsp.h>

enum OscillatorFunctionType
{
    SINE,
    SAW,
    SQUARE
};

class Oscillator : public juce::dsp::Oscillator<float>
{
public:
    Oscillator();
    void prepareToPlay (const juce::dsp::ProcessSpec& processSpec);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void renderNextBlock(juce::dsp::ProcessContextReplacing<float>& context);

    void setFunctionType(const OscillatorFunctionType& functionType);
    void setFrequencyModulation(float frequency, float depth);

private:
    juce::dsp::Oscillator<float> m_modulationOscillator {[] (const float x) { return std::sin (x); }};
    float m_frequencyModifier = 0.f;
    float m_fmDepth = 0.f;
    int m_lastMidiNoteNumber = 0;
};


