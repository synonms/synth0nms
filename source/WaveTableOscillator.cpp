#include "WaveTableOscillator.h"
#include <cmath>

WaveTableOscillator::WaveTableOscillator(std::vector<float> waveTable, const double sampleRate)
    : m_waveTable(std::move(waveTable))
    , m_sampleRate(sampleRate)
{
}

void WaveTableOscillator::setFrequency(const float frequency)
{
    m_indexIncrement = frequency * static_cast<float>(m_waveTable.size()) / static_cast<float>(m_sampleRate);
}

float WaveTableOscillator::getSample()
{
    const float sample = interpolateLinearly();
    m_index += m_indexIncrement;
    m_index = std::fmod(m_index, static_cast<float>(m_waveTable.size()));

    return sample;
}

void WaveTableOscillator::stop()
{
    m_index = 0;
    m_indexIncrement = 0;
}

bool WaveTableOscillator::isPlaying() const
{
    return m_indexIncrement != 0;
}

float WaveTableOscillator::interpolateLinearly() const
{
    const int truncatedIndex = static_cast<int>(m_index);
    const int nextIndex = (truncatedIndex + 1) % static_cast<int>(m_waveTable.size());

    const float nextIndexWeight = m_index - static_cast<float>(truncatedIndex);
    const float truncatedIndexWeight = 1.f - nextIndexWeight;

    return (truncatedIndexWeight * m_waveTable[truncatedIndex]) + (nextIndexWeight * m_waveTable[nextIndex]);
}
