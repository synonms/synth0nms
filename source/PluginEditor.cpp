#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth0nmsAudioProcessorEditor::Synth0nmsAudioProcessorEditor (Synth0nmsAudioProcessor& audioProcessor)
    : AudioProcessorEditor (&audioProcessor)
    , m_audioProcessor (audioProcessor)
    , m_adsrComponent (audioProcessor.audioProcessorValueTreeState)
    , m_oscillatorComponent (audioProcessor.audioProcessorValueTreeState)
    , m_keyboardComponent (audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (2048, 1024);
    addAndMakeVisible(m_adsrComponent);
    addAndMakeVisible(m_oscillatorComponent);
    addAndMakeVisible (m_keyboardComponent);
}

Synth0nmsAudioProcessorEditor::~Synth0nmsAudioProcessorEditor() = default;

//==============================================================================
void Synth0nmsAudioProcessorEditor::paint (juce::Graphics& graphics)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    graphics.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    graphics.setColour (juce::Colours::white);
    graphics.setFont (15.0f);
    graphics.drawFittedText ("Synth0nms", getLocalBounds(), juce::Justification::centred, 1);
}

void Synth0nmsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any subcomponents in your editor.
    m_adsrComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);
    m_oscillatorComponent.setBounds(0, 0, getWidth() / 2, getHeight() / 2);

    m_keyboardComponent.setBounds (10, getHeight() - 110, getWidth() - 20, 100);
}

