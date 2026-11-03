#include "SynthesiserComponent.h"

SynthesiserComponent::SynthesiserComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, juce::MidiKeyboardState& keyboardState)
    : m_oscillator1Component (audioProcessorValueTreeState, "OSC1")
    , m_oscillator2Component (audioProcessorValueTreeState, "OSC2")
    , m_oscillator3Component (audioProcessorValueTreeState, "OSC3")
    , m_modulationAdsrComponent (audioProcessorValueTreeState, "MOD")
    , m_filter1Component (audioProcessorValueTreeState, "FILTER1")
    , m_filter2Component (audioProcessorValueTreeState, "FILTER2")
    , m_amplitudeAdsrComponent (audioProcessorValueTreeState, "AMP")
    , m_keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(m_oscillator1Component);
    addAndMakeVisible(m_oscillator2Component);
    addAndMakeVisible(m_oscillator3Component);
    addAndMakeVisible(m_modulationAdsrComponent);

    addAndMakeVisible(m_filter1Component);
    addAndMakeVisible(m_filter2Component);

    addAndMakeVisible(m_amplitudeAdsrComponent);

    addAndMakeVisible(m_keyboardComponent);
}

void SynthesiserComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
}

void SynthesiserComponent::resized()
{
    const int sidePanelWidth = getWidth() / 3;
    const int midPanelWidth = getWidth() - sidePanelWidth - sidePanelWidth;
    const int panelHeight = getHeight() / 5;

    m_oscillator1Component.setBounds (0, 0, sidePanelWidth, panelHeight);
    m_oscillator2Component.setBounds (0, m_oscillator1Component.getBottom(), sidePanelWidth, panelHeight);
    m_oscillator3Component.setBounds (0, m_oscillator2Component.getBottom(), sidePanelWidth, panelHeight);
    m_modulationAdsrComponent.setBounds (0, m_oscillator3Component.getBottom(), sidePanelWidth, panelHeight);

    m_filter1Component.setBounds(m_oscillator1Component.getRight(), 0, midPanelWidth, panelHeight);
    m_filter2Component.setBounds(m_oscillator1Component.getRight(), m_filter1Component.getBottom(), midPanelWidth, panelHeight);

    m_amplitudeAdsrComponent.setBounds (m_oscillator1Component.getRight(), m_filter2Component.getBottom(), midPanelWidth, panelHeight * 2);

    m_keyboardComponent.setBounds(0, m_modulationAdsrComponent.getBottom(), getWidth(), panelHeight);
}