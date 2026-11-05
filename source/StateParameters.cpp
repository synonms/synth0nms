#include "StateParameters.h"

StateParameters::StateParameters(juce::AudioProcessor& audioProcessor)
    : m_valueTreeState (audioProcessor, nullptr, "Parameters", createParameters())
{
}

juce::RangedAudioParameter* StateParameters::addFloatParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, juce::NormalisableRange<float> parameterRange, float defaultValue)
{
    return m_valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterFloat>(parameterId, parameterName, parameterRange, defaultValue));
}

juce::RangedAudioParameter* StateParameters::addChoiceParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::StringArray& choices, int defaultItemIndex)
{
    return m_valueTreeState.createAndAddParameter(std::make_unique<juce::AudioParameterChoice>(parameterId, parameterName, choices, defaultItemIndex));
}

void StateParameters::addSliderAttachment(const juce::String& parameterId, juce::Slider& slider)
{
    m_sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_valueTreeState, parameterId, slider));
}

void StateParameters::addComboBoxAttachment(const juce::String& parameterId, juce::ComboBox& comboBox)
{
    m_comboBoxAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(m_valueTreeState, parameterId, comboBox));
}

float StateParameters::getParameterValue(const juce::String &parameterName) const
{
    return m_valueTreeState.getRawParameterValue(parameterName)->load();
}

juce::AudioProcessorValueTreeState::ParameterLayout StateParameters::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // Add any general options here. Components register their own parameters.

    return { parameters.begin(), parameters.end() };
}
