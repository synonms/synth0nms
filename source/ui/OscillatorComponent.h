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

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_functionAttachment;

    juce::ComboBox m_functionComboBox;
};
