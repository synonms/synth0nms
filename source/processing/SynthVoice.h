#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

#include "Adsr.h"
#include "Filter.h"
#include "Oscillator.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
//    bool isVoiceActive() const override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
//    void aftertouchChanged (int newAftertouchValue) override;
//    void channelPressureChanged (int newChannelPressureValue) override;
    void renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannelCount);

    // Oscillator controls
    void updateOscillator1FunctionType(const OscillatorFunctionType& functionType);
    void updateOscillator1FrequencyModulation(float frequency, float depth);
    void updateOscillator2FunctionType(const OscillatorFunctionType& functionType);
    void updateOscillator2FrequencyModulation(float frequency, float depth);
    void updateOscillator3FunctionType(const OscillatorFunctionType& functionType);
    void updateOscillator3FrequencyModulation(float frequency, float depth);

    // Amplitude ADSR controls
    void updateAmplitudeAdsr(float attack, float decay, float sustain, float release);

    // Filter controls
    void updateFilter1(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance);
    void updateFilter2(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance);

    // Modulation ADSR controls
    void updateModulationAdsr(float attack, float decay, float sustain, float release);

private:
    Oscillator m_oscillator1;
    Oscillator m_oscillator2;
    Oscillator m_oscillator3;
    Adsr m_amplitudeAdsr;
    Filter m_filter1;
    Filter m_filter2;
    Adsr m_modulationAdsr;

    juce::dsp::Gain<float> m_gain;
};
