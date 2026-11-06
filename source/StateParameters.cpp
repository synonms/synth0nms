#include "StateParameters.h"

StateParameters::StateParameters(juce::AudioProcessor& audioProcessor) : m_audioProcessor(audioProcessor)
{
}

void StateParameters::build()
{
    // Make sure all components have registered their parameters before this call
    m_valueTreeState = std::make_unique<juce::AudioProcessorValueTreeState>(m_audioProcessor, nullptr, "Parameters", createParameters());

    for (auto sliderAttachmentRequest : m_sliderAttachmentRequests)
    {
        m_sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(*m_valueTreeState, sliderAttachmentRequest.first, sliderAttachmentRequest.second));
    }

    for (auto comboBoxAttachmentRequest : m_comboBoxAttachmentRequests)
    {
        m_comboBoxAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(*m_valueTreeState, comboBoxAttachmentRequest.first, comboBoxAttachmentRequest.second));
    }
}

void StateParameters::addFloatParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::NormalisableRange<float>& parameterRange, float defaultValue)
{
    m_parameters.push_back (std::make_unique<juce::AudioParameterFloat>(parameterId, parameterName, parameterRange, defaultValue));
}

void StateParameters::addChoiceParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::StringArray& choices, int defaultItemIndex)
{
    m_parameters.push_back (std::make_unique<juce::AudioParameterChoice>(parameterId, parameterName, choices, defaultItemIndex));
}

void StateParameters::registerSliderAttachment(const juce::String& parameterId, juce::Slider& slider)
{
    m_sliderAttachmentRequests.emplace(parameterId, slider);
}

void StateParameters::registerComboBoxAttachment(const juce::String& parameterId, juce::ComboBox& comboBox)
{
    m_comboBoxAttachmentRequests.emplace(parameterId, comboBox);
}

float StateParameters::getParameterValue(const juce::String &parameterName) const
{
    return m_valueTreeState->getRawParameterValue(parameterName)->load();
}

juce::AudioProcessorValueTreeState::ParameterLayout StateParameters::createParameters()
{
    return { m_parameters.begin(), m_parameters.end() };
}
