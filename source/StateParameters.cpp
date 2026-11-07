#include "StateParameters.h"

StateParameters::StateParameters(juce::AudioProcessor& audioProcessor) : m_audioProcessor(audioProcessor)
{
}

void StateParameters::addBoolParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const bool defaultValue)
{
    m_parameters.push_back (std::make_unique<juce::AudioParameterBool>(parameterId, parameterName, defaultValue));
}

void StateParameters::addChoiceParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::StringArray& choices, int defaultItemIndex)
{
    m_parameters.push_back (std::make_unique<juce::AudioParameterChoice>(parameterId, parameterName, choices, defaultItemIndex));
}

void StateParameters::addFloatParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::NormalisableRange<float>& parameterRange, float defaultValue)
{
    m_parameters.push_back (std::make_unique<juce::AudioParameterFloat>(parameterId, parameterName, parameterRange, defaultValue));
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

    for (auto textButtonAttachmentRequest : m_textButtonAttachmentRequests)
    {
        m_buttonAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(*m_valueTreeState, textButtonAttachmentRequest.first, textButtonAttachmentRequest.second));
    }
}

float StateParameters::getParameterValue(const juce::String &parameterName) const
{
    return m_valueTreeState->getRawParameterValue(parameterName)->load();
}

void StateParameters::registerComboBoxAttachment(const juce::String& parameterId, juce::ComboBox& comboBox)
{
    m_comboBoxAttachmentRequests.emplace(parameterId, comboBox);
}

void StateParameters::registerSliderAttachment(const juce::String& parameterId, juce::Slider& slider)
{
    m_sliderAttachmentRequests.emplace(parameterId, slider);
}

void StateParameters::registerTextButtonAttachment(const juce::String& parameterId, juce::TextButton& textButton)
{
    m_textButtonAttachmentRequests.emplace(parameterId, textButton);
}

juce::AudioProcessorValueTreeState::ParameterLayout StateParameters::createParameters()
{
    return { m_parameters.begin(), m_parameters.end() };
}
