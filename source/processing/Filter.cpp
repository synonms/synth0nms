#include "Filter.h"

void Filter::prepareToPlay (const juce::dsp::ProcessSpec& processSpec)
{
    m_filter.reset();
    m_filter.prepare(processSpec);
}

void Filter::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, const juce::MidiBuffer& midiBuffer, int startSample, int numSamples)
{
    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock(startSample, numSamples);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    m_filter.process(context);
}

void Filter::updateParameters(const juce::dsp::StateVariableTPTFilterType& type, const float cutoffFrequency, const float resonance)
{
    m_filter.setType(type);
    m_filter.setCutoffFrequency(cutoffFrequency);
    m_filter.setResonance(resonance);
}

void Filter::reset()
{
    m_filter.reset();
}
