#include "CircularBuffer.h"

void CircularBuffer::storeBlock(juce::AudioBuffer<float>& audioBuffer)
{
    const int audioBufferSize = audioBuffer.getNumSamples();
    const int circularBufferSize = getNumSamples();

    for (int channel = 0; channel < audioBuffer.getNumChannels(); ++channel)
    {
        const float* channelData = audioBuffer.getWritePointer(channel);

        if (circularBufferSize > audioBufferSize + m_writePosition)
        {
            // Write entire block in one pop
            copyFromWithRamp(channel, m_writePosition, channelData, audioBufferSize, 1.f, 1.f);
            continue;
        }

        const int numSamplesToEnd = circularBufferSize - m_writePosition;

        // Take samples until circular buffer is full
        copyFromWithRamp(channel, m_writePosition, channelData, numSamplesToEnd, 1.f, 1.f);

        // Write remaining samples from start
        copyFromWithRamp(channel, 0, channelData + numSamplesToEnd, audioBufferSize - numSamplesToEnd, 1.f, 1.f);
    }

    m_writePosition += audioBufferSize;
    m_writePosition %= circularBufferSize;
}

juce::AudioBuffer<float> CircularBuffer::readBlock(const int startPositionOffset, const int numSamplesToRead) const
{
    const int circularBufferSize = getNumSamples();
    const int numChannels = getNumChannels();

    juce::AudioBuffer<float> buffer {numChannels, numSamplesToRead};

    if (numSamplesToRead > circularBufferSize)
    {
        throw;
    }

    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto readPosition = m_writePosition - startPositionOffset;

        if (readPosition < 0)
        {
            readPosition += circularBufferSize;
        }

        if (readPosition + numSamplesToRead < circularBufferSize)
        {
            buffer.addFrom(channel, 0, getReadPointer(channel, readPosition), numSamplesToRead);
        }
        else
        {
            const int numSamplesBeforeWrap = circularBufferSize - readPosition;
            const int numSamplesAfterWrap = numSamplesToRead - numSamplesBeforeWrap;

            buffer.addFrom(channel, 0, getReadPointer(channel, readPosition), numSamplesBeforeWrap);
            buffer.addFrom(channel, numSamplesBeforeWrap, getReadPointer(channel, 0), numSamplesAfterWrap);
        }
    }

    return buffer;
}
