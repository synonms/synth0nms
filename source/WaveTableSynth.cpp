#include "WaveTableSynth.h"

void WaveTableSynth::prepareToPlay(juce::dsp::ProcessSpec processSpec)
{
    m_sampleRate = processSpec.sampleRate;

    // Approach 1
//    initialiseOscillators();

    // Approach 2
    m_sineWaveOscillator.prepare(processSpec);
    m_sawWaveOscillator.prepare(processSpec);
    m_squareWaveOscillator.prepare(processSpec);
    m_gain.prepare(processSpec);

    m_sineWaveOscillator.setFrequency(220.f);
    m_sawWaveOscillator.setFrequency(440.f);
    m_squareWaveOscillator.setFrequency(880.f);
    m_gain.setGainLinear(0.01f);
}

void WaveTableSynth::processBlock(juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer)
{
    // Approach 1
    // int currentSample = 0;
    //
    // for (const auto midiMessage : midiBuffer) {
    //     const juce::MidiMessage midiEvent = midiMessage.getMessage();
    //     const int midiEventSample = static_cast<int>(midiEvent.getTimeStamp());
    //
    //     render(audioBuffer, currentSample, midiEventSample);
    //     handleMidiEvent(midiEvent);
    //
    //     currentSample = midiEventSample;
    // }
    //
    // render(audioBuffer, currentSample, audioBuffer.getNumSamples());

    // Approach 2
    juce::dsp::AudioBlock<float> audioBlock(audioBuffer);
    // Write oscillator waves to audio buffer
    m_sineWaveOscillator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    m_sawWaveOscillator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    m_squareWaveOscillator.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    // Bring down gain to avoid blowing ear drums
    m_gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void WaveTableSynth::initialiseOscillators()
{
    constexpr int OSCILLATOR_COUNT = 128;

    const auto waveTable = generateSineWaveTable();

    m_oscillators.clear();

    for (int i = 0; i < OSCILLATOR_COUNT; ++i) {
        m_oscillators.emplace_back(waveTable, m_sampleRate);
    }
}

std::vector<float> WaveTableSynth::generateSineWaveTable()
{
    constexpr int WAVETABLE_LENGTH = 64;
    const float PI = std::atanf(1.f) * 4;

    std::vector<float> sineWaveTable(WAVETABLE_LENGTH);

    for (int i = 0; i < WAVETABLE_LENGTH; ++i) {
        sineWaveTable[i] = std::sinf(2 * PI * static_cast<float>(i) / static_cast<float>(WAVETABLE_LENGTH));
    }

    return sineWaveTable;
}

void WaveTableSynth::handleMidiEvent(const juce::MidiMessage& midiMessage)
{
    if (midiMessage.isNoteOn()) {
        const int midiNoteNumber = midiMessage.getNoteNumber();
        const auto frequency = midiNoteNumberToFrequency(midiNoteNumber);
        m_oscillators[midiNoteNumber].setFrequency(frequency);
    }
    else if (midiMessage.isNoteOff()) {
        const int oscillatorNumber = midiMessage.getNoteNumber();
        m_oscillators[oscillatorNumber].stop();
    }
    else if (midiMessage.isAllNotesOff()) {
        for (WaveTableOscillator& oscillator : m_oscillators) {
            oscillator.stop();
        }
    }
}

void WaveTableSynth::render(juce::AudioBuffer<float>& audioBuffer, int startSample, int endSample)
{
    float* firstChannel = audioBuffer.getWritePointer(0);

    for (WaveTableOscillator& oscillator : m_oscillators) {
        if (oscillator.isPlaying()) {
            for (int sample = startSample; sample < endSample; ++sample) {
                firstChannel[sample] += oscillator.getSample();
            }
        }
    }

    for (auto channel = 1; channel < audioBuffer.getNumChannels(); ++channel) {
        std::copy(firstChannel + startSample, firstChannel + endSample, audioBuffer.getWritePointer(channel) + startSample);
    }
}

float WaveTableSynth::midiNoteNumberToFrequency(const int midiNoteNumber)
{
    constexpr float A4_FREQUENCY = 440.f;
    constexpr float A4_NOTE_NUMBER = 69.f;
    constexpr float SEMITONES_IN_AN_OCTAVE = 12.f;

    return A4_FREQUENCY * std::powf(2.f, (static_cast<float>(midiNoteNumber) - A4_NOTE_NUMBER) / SEMITONES_IN_AN_OCTAVE);
}
