#include "DelayModule.h"

DelayModule::DelayModule(CircularBuffer& circularBuffer)
    : m_circularBuffer(circularBuffer)
{
}

void DelayModule::apply(juce::AudioBuffer<float>& audioBuffer, const int startSample, const int numSamples)
{
    if (!isEnabled) return;

    const float numSamplesToGoBack = (m_delayInSeconds * m_sampleRate) + numSamples;

    const juce::AudioBuffer<float> delayBuffer = m_circularBuffer.readBlock(numSamplesToGoBack, numSamples);

    for (int channel = 0; channel < audioBuffer.getNumChannels(); ++channel)
    {
        audioBuffer.addFrom(channel, 0, delayBuffer, channel, 0, numSamples, m_intensity);
    }
}

void DelayModule::initialise(const juce::dsp::ProcessSpec& processSpec)
{
    m_sampleRate = processSpec.sampleRate;
}
