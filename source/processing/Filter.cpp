#include "Filter.h"

void Filter::prepareToPlay (const juce::dsp::ProcessSpec& processSpec)
{
    m_filter.reset();
    m_filter.prepare(processSpec);
}

void Filter::renderNextBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    m_filter.process(context);
}

void Filter::updateParameters(const juce::dsp::StateVariableTPTFilterType& type, const float cutoffFrequency, const float resonance, const float modulator)
{
    float modulatedFrequency = std::clamp(cutoffFrequency * modulator, 20.0f, 20000.0f);

    m_filter.setType(type);
    m_filter.setCutoffFrequency(modulatedFrequency);
    m_filter.setResonance(resonance);
}

void Filter::reset()
{
    m_filter.reset();
}
