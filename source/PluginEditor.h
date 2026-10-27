#pragma once

#include "PluginProcessor.h"
#include <juce_audio_utils/juce_audio_utils.h>

//==============================================================================
/**
*/
class Synth0nmsAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    Synth0nmsAudioProcessorEditor (Synth0nmsAudioProcessor&);
    ~Synth0nmsAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider m_attackSlider;
    juce::Slider m_decaySlider;
    juce::Slider m_sustainSlider;
    juce::Slider m_releaseSlider;
    juce::ComboBox m_waveformSelector;
    juce::MidiKeyboardComponent m_keyboardComponent;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_attackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_decayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_sustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_releaseAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_waveformSelectorAttachment;

    Synth0nmsAudioProcessor& m_audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth0nmsAudioProcessorEditor)
};