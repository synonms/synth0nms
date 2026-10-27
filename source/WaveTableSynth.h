#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

#include "WaveTableOscillator.h"

class WaveTableSynth
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec processSpec);
    void processBlock(juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer);

private:
    void initialiseOscillators();
    void handleMidiEvent(const juce::MidiMessage& midiMessage);
    void render(juce::AudioBuffer<float>& audioBuffer, int startSample, int endSample);

    static std::vector<float> generateSineWaveTable();
    static float midiNoteNumberToFrequency(int midiNoteNumber);

    // Approach 1
    double m_sampleRate = 0;
    std::vector<WaveTableOscillator> m_oscillators;

    // Approach 2
    juce::dsp::Oscillator<float> m_sineWaveOscillator {[] (float x) { return std::sin (x); }};
    juce::dsp::Oscillator<float> m_sawWaveOscillator {[] (float x) { return x / juce::MathConstants<float>::pi; }};
    juce::dsp::Oscillator<float> m_squareWaveOscillator {[] (float x) { return x < 0.f ? -1.f : 1.f; }};
    juce::dsp::Gain<float> m_gain;
};
