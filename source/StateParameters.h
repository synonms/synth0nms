#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class StateParameters
{
public:
    StateParameters(juce::AudioProcessor& audioProcessor);

    void addBoolParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, bool defaultValue);
    void addFloatParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::NormalisableRange<float>& parameterRange, float defaultValue);
    void addChoiceParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::StringArray& choices, int defaultItemIndex);
    void build();
    float getParameterValue(const juce::String& parameterName) const;
    void registerComboBoxAttachment(const juce::String& parameterId, juce::ComboBox& comboBox);
    void registerSliderAttachment(const juce::String& parameterId, juce::Slider& slider);
    void registerTextButtonAttachment(const juce::String& parameterId, juce::TextButton& textButton);

private:
    juce::AudioProcessor& m_audioProcessor;
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> m_parameters;
    std::unique_ptr<juce::AudioProcessorValueTreeState> m_valueTreeState;
    std::map<const juce::String, juce::Slider&> m_sliderAttachmentRequests;
    std::map<const juce::String, juce::ComboBox&> m_comboBoxAttachmentRequests;
    std::map<const juce::String, juce::TextButton&> m_textButtonAttachmentRequests;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> m_comboBoxAttachments;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> m_sliderAttachments;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> m_buttonAttachments;

    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
};
