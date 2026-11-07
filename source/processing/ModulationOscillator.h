#pragma once

#include <juce_dsp/juce_dsp.h>

#include "OscillatorFunctionType.h"

class ModulationOscillator : public juce::dsp::Oscillator<float>
{
public:
    ModulationOscillator();

    void prepareToPlay (const juce::dsp::ProcessSpec& processSpec);
    void setFunctionType(const OscillatorFunctionType& functionType);
    void setIsEnabled(bool isEnabled) { m_isEnabled = isEnabled; }
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);

private:
    bool m_isEnabled {false};
};

