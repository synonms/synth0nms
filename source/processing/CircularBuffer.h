#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class CircularBuffer : public juce::AudioBuffer<float>
{
public:
    void storeBlock(juce::AudioBuffer<float>& audioBuffer);
    juce::AudioBuffer<float> readBlock(int startPositionOffset, int numSamplesToRead) const;

private:
    int m_writePosition {0};
};

