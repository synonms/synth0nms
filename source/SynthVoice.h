#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

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

private:
    juce::dsp::Oscillator<float> m_oscillator {[] (float x) { return std::sin (x); }};
    juce::dsp::Gain<float> m_gain;
    juce::ADSR m_adsr;
    juce::ADSR::Parameters m_adsrParameters;
};
