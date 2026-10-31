#include "OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState)
    : juce::Component()
    , m_audioProcessorValueTreeState(audioProcessorValueTreeState)
{
    juce::StringArray functions { "Sine", "Saw", "Square" };
    m_functionComboBox.addItemList(functions, 1);
    addAndMakeVisible(m_functionComboBox);

    m_functionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessorValueTreeState, "OSC1FUNCTION", m_functionComboBox);
}

OscillatorComponent::~OscillatorComponent() = default;

void OscillatorComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
}

void OscillatorComponent::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds().reduced(10);
    const int padding = 10;
    const int width = bounds.getWidth() - (padding * 2);
    const int height = 40;
    const int x = 0 + padding;
    const int y = 0 + padding;

    m_functionComboBox.setBounds (x, y, width, height);
}