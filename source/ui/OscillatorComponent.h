#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class OscillatorComponent : public juce::Component
{
public:
    OscillatorComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState);
    ~OscillatorComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& m_audioProcessorValueTreeState;

    juce::ComboBox m_functionComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_functionAttachment;

    juce::Slider m_fmFrequencySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_fmFrequencyAttachment;
    juce::Label m_fmFrequencyLabel {"FMFREQLABEL", "Frequency"};

    juce::Slider m_fmDepthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_fmDepthAttachment;
    juce::Label m_fmDepthLabel {"FMDEPTHLABEL", "Depth"};

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, const std::string& parameterId);
};
