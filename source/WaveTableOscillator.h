#pragma once

#include <vector>

class WaveTableOscillator
{
public:
    WaveTableOscillator(std::vector<float> waveTable, double sampleRate);

    void setFrequency(float frequency);
    float getSample();
    void stop();
    bool isPlaying() const;

private:
    float interpolateLinearly() const;

    std::vector<float> m_waveTable;
    double m_sampleRate = 0.f;
    float m_index = 0.f;
    float m_indexIncrement = 0.f;
};
