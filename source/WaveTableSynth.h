#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

#include "WaveTableOscillator.h"

class WaveTableSynth
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock);
    void processBlock(juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer);

private:
    void initialiseOscillators();
    void handleMidiEvent(const juce::MidiMessage& midiMessage);
    void render(juce::AudioBuffer<float>& audioBuffer, int startSample, int endSample);

    static std::vector<float> generateSineWaveTable();
    static float midiNoteNumberToFrequency(int midiNoteNumber);

    double m_sampleRate = 0;
    std::vector<WaveTableOscillator> m_oscillators;
};
