#pragma once

#include "PluginProcessor.h"
#include "ui/AdsrComponent.h"

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
    Synth0nmsAudioProcessor& m_audioProcessor;
    AdsrComponent m_adsrComponent;

    juce::ComboBox m_waveformSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> m_waveformSelectorAttachment;

    juce::MidiKeyboardComponent m_keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth0nmsAudioProcessorEditor)
};