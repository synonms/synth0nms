#include "FilterModule.h"

void FilterModule::apply(juce::AudioBuffer<float> &audioBuffer, int startSample, int numSamples)
{
    if (!isEnabled) return;

    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(audioBuffer).getSubBlock(startSample, numSamples);
    const juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    m_filter.process(context);
}

void FilterModule::initialise(const juce::dsp::ProcessSpec &processSpec)
{
    m_filter.reset();
    m_filter.prepare(processSpec);
}

void FilterModule::updateParameters(const juce::dsp::StateVariableTPTFilterType& type, const float cutoffFrequency, const float resonance, const float modulator)
{
    float modulatedFrequency = std::clamp(cutoffFrequency * modulator, 20.0f, 20000.0f);

    m_filter.setType(type);
    m_filter.setCutoffFrequency(modulatedFrequency);
    m_filter.setResonance(resonance);
}

void FilterModule::reset()
{
    m_filter.reset();
}
