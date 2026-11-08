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
