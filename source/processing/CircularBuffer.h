#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class CircularBuffer : public juce::AudioBuffer<float>
{
public:
    void storeBlock(juce::AudioBuffer<float>& audioBuffer);

private:
    int m_writePosition {0};
};

