#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class FilterComponent : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState);
    ~FilterComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& m_audioProcessorValueTreeState;

    juce::ComboBox m_filterTypeComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_filterTypeAttachment;

    juce::Slider m_cutoffSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_cutoffAttachment;
    juce::Label m_cutoffLabel {"CUTOFFLABEL", "Cutoff"};

    juce::Slider m_resonanceSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_resonanceAttachment;
    juce::Label m_resonanceLabel {"RESONANCELABEL", "Resonance"};

    void setSliderParams(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, const std::string& parameterId);
};
