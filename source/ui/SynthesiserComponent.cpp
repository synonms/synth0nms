#include "SynthesiserComponent.h"

SynthesiserComponent::SynthesiserComponent(StateParameters& stateParameters, juce::MidiKeyboardState& keyboardState)
    : m_oscillator1Component (stateParameters, "OSC1", true)
    , m_oscillator2Component (stateParameters, "OSC2", false)
    , m_oscillator3Component (stateParameters, "OSC3", false)
    , m_modulationOscillatorComponent (stateParameters, "MODOSC1")
    , m_filter1Component (stateParameters, "FILTER1")
    , m_filter2Component (stateParameters, "FILTER2")
    , m_amplitudeAdsrComponent (stateParameters, "AMP")
    , m_meterLeftComponent (stateParameters, "METERL")
    , m_meterRightComponent (stateParameters, "METERR")
    , m_keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(m_oscillator1Component);
    addAndMakeVisible(m_oscillator2Component);
    addAndMakeVisible(m_oscillator3Component);
    addAndMakeVisible(m_modulationOscillatorComponent);

    addAndMakeVisible(m_filter1Component);
    addAndMakeVisible(m_filter2Component);

    addAndMakeVisible(m_amplitudeAdsrComponent);

    addAndMakeVisible(m_meterLeftComponent);
    addAndMakeVisible(m_meterRightComponent);

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
    m_modulationOscillatorComponent.setBounds (0, m_oscillator3Component.getBottom(), sidePanelWidth, panelHeight);

    m_filter1Component.setBounds(m_oscillator1Component.getRight(), 0, midPanelWidth, panelHeight);
    m_filter2Component.setBounds(m_oscillator1Component.getRight(), m_filter1Component.getBottom(), midPanelWidth, panelHeight);

    m_meterLeftComponent.setBounds(m_filter1Component.getRight(), 0, sidePanelWidth, panelHeight / 2);
    m_meterRightComponent.setBounds(m_filter1Component.getRight(), m_meterLeftComponent.getBottom(), sidePanelWidth, panelHeight / 2);

    m_amplitudeAdsrComponent.setBounds (m_oscillator1Component.getRight(), m_filter2Component.getBottom(), midPanelWidth, panelHeight * 2);

    m_keyboardComponent.setBounds(0, m_modulationOscillatorComponent.getBottom(), getWidth(), panelHeight);
}

void SynthesiserComponent::setRmsLevelInDecibels(const int channel, const float rmsLevelInDecibels)
{
    if (channel == 0)
    {
        m_meterLeftComponent.setRmsLevelInDecibels(rmsLevelInDecibels);
        m_meterLeftComponent.repaint();
    }
    else if (channel == 1)
    {
        m_meterRightComponent.setRmsLevelInDecibels(rmsLevelInDecibels);
        m_meterRightComponent.repaint();
    }
}
