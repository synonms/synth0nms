#pragma once

#include "PluginProcessor.h"

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
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Synth0nmsAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth0nmsAudioProcessorEditor)
};