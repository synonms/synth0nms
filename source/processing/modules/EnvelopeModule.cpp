#include "EnvelopeModule.h"

void EnvelopeModule::apply(juce::AudioBuffer<float>& audioBuffer, const int startSample, const int numSamples)
{
    if (!isEnabled) return;

    applyEnvelopeToBuffer(audioBuffer, startSample, numSamples);
}

void EnvelopeModule::initialise(const juce::dsp::ProcessSpec& processSpec)
{
    setSampleRate(processSpec.sampleRate);
}

void EnvelopeModule::update(const float attack, const float decay, const float sustain, const float release)
{
    m_adsrParameters.attack = attack;
    m_adsrParameters.decay = decay;
    m_adsrParameters.sustain = sustain;
    m_adsrParameters.release = release;

    setParameters(m_adsrParameters);
}

void EnvelopeModule::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    noteOn();
}

void EnvelopeModule::stopNote(float velocity, bool allowTailOff)
{
    noteOff();
}
