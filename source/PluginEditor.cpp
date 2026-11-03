#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth0nmsAudioProcessorEditor::Synth0nmsAudioProcessorEditor (Synth0nmsAudioProcessor& audioProcessor)
    : AudioProcessorEditor (&audioProcessor)
    , m_audioProcessor (audioProcessor)
    , m_synthesiserComponent (audioProcessor.getValueTreeState(), audioProcessor.getKeyboardState())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (2048, 1024);
    addAndMakeVisible(m_synthesiserComponent);
}

Synth0nmsAudioProcessorEditor::~Synth0nmsAudioProcessorEditor() = default;

//==============================================================================
void Synth0nmsAudioProcessorEditor::paint (juce::Graphics& graphics)
{
    // Our component is opaque, so we must completely fill the background with a solid colour
    graphics.fillAll (juce::Colours::ivory);
}

void Synth0nmsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any subcomponents in your editor.
    m_synthesiserComponent.setBounds(0, 0, getWidth(), getHeight());
}

