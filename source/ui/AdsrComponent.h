#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class AdsrComponent : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState);
    ~AdsrComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& m_audioProcessorValueTreeState;

    juce::Slider m_attackSlider;
    juce::Slider m_decaySlider;
    juce::Slider m_sustainSlider;
    juce::Slider m_releaseSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_releaseAttachment;

    void setSliderParams(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AdsrComponent)
};
