#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class Adsr : public juce::ADSR
{
public:
    void update(float attack, float decay, float sustain, float release);

private:
    juce::ADSR::Parameters m_adsrParameters;

};

