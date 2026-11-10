#include "MasterModule.h"

void MasterModule::apply(juce::AudioBuffer<float>& audioBuffer, const int startSample, const int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(audioBuffer).getSubBlock(startSample, numSamples);
    const juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    m_gain.process(context);

    // Get RMS in range [0.0..1.0]
    float rmsLevelLeft = audioBuffer.getRMSLevel(0, 0, audioBuffer.getNumSamples());
    float rmsLevelRight = audioBuffer.getRMSLevel(1, 0, audioBuffer.getNumSamples());
    // Convert to dB and store
    float rmsLevelLeftInDecibels = juce::Decibels::gainToDecibels(rmsLevelLeft);
    float rmsLevelRightInDecibels = juce::Decibels::gainToDecibels(rmsLevelRight);

    m_rmsLevelsInDecibels[0].skip(audioBuffer.getNumSamples());
    m_rmsLevelsInDecibels[1].skip(audioBuffer.getNumSamples());

    if (rmsLevelLeftInDecibels < m_rmsLevelsInDecibels[0].getCurrentValue())
    {
        m_rmsLevelsInDecibels[0].setTargetValue(rmsLevelLeftInDecibels);
    }
    else
    {
        m_rmsLevelsInDecibels[0].setCurrentAndTargetValue(rmsLevelLeftInDecibels);
    }

    if (rmsLevelRightInDecibels < m_rmsLevelsInDecibels[1].getCurrentValue())
    {
        m_rmsLevelsInDecibels[1].setTargetValue(rmsLevelRightInDecibels);
    }
    else
    {
        m_rmsLevelsInDecibels[1].setCurrentAndTargetValue(rmsLevelRightInDecibels);
    }
}

void MasterModule::initialise(const juce::dsp::ProcessSpec& processSpec)
{
    m_gain.prepare(processSpec);
    m_gain.setGainLinear(0.5f);

    m_rmsLevelsInDecibels[0].reset(processSpec.sampleRate, 0.5);
    m_rmsLevelsInDecibels[1].reset(processSpec.sampleRate, 0.5);
    m_rmsLevelsInDecibels[0].setCurrentAndTargetValue(-100.f);
    m_rmsLevelsInDecibels[1].setCurrentAndTargetValue(-100.f);
}
