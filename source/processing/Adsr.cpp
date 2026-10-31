#include "Adsr.h"

void Adsr::prepareToPlay(const juce::dsp::ProcessSpec &processSpec)
{
    setSampleRate(processSpec.sampleRate);
}

void Adsr::update(const float attack, const float decay, const float sustain, const float release)
{
    m_adsrParameters.attack = attack;
    m_adsrParameters.decay = decay;
    m_adsrParameters.sustain = sustain;
    m_adsrParameters.release = release;

    setParameters(m_adsrParameters);
}

void Adsr::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    noteOn();
}

void Adsr::stopNote(float velocity, bool allowTailOff)
{
    noteOff();
}

void Adsr::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}
