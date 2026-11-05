#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

class StateParameters
{
public:
    StateParameters(juce::AudioProcessor& audioProcessor);

    juce::RangedAudioParameter* addFloatParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, juce::NormalisableRange<float> parameterRange, float defaultValue);
    juce::RangedAudioParameter* addChoiceParameter(const juce::ParameterID& parameterId, const juce::String& parameterName, const juce::StringArray& choices, int defaultItemIndex);

    void addSliderAttachment(const juce::String& parameterId, juce::Slider& slider);
    void addComboBoxAttachment(const juce::String& parameterId, juce::ComboBox& comboBox);

    float getParameterValue(const juce::String& parameterName) const;

private:
    juce::AudioProcessorValueTreeState m_valueTreeState;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> m_sliderAttachments;
    std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> m_comboBoxAttachments;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
};
