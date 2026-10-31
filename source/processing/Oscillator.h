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
    void setFunctionType(const OscillatorFunctionType& functionType);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void renderNextBlock(juce::dsp::ProcessContextReplacing<float>& context);

private:

};


