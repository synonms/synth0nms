#include "SynthesiserComponent.h"

SynthesiserComponent::SynthesiserComponent(StateParameters& stateParameters, juce::MidiKeyboardState& keyboardState)
    : m_oscillator1Component (stateParameters, "OSC1", true)
    , m_oscillator2Component (stateParameters, "OSC2", false)
    , m_oscillator3Component (stateParameters, "OSC3", false)
    , m_filter1Component (stateParameters, "FILTER1")
    , m_filter2Component (stateParameters, "FILTER2")
    , m_delayComponent(stateParameters)
    , m_amplitudeAdsrComponent (stateParameters, "AMP")
    , m_masterComponent(stateParameters)
    , m_keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(m_oscillator1Component);
    addAndMakeVisible(m_oscillator2Component);
    addAndMakeVisible(m_oscillator3Component);

    addAndMakeVisible(m_filter1Component);
    addAndMakeVisible(m_filter2Component);

    addAndMakeVisible(m_delayComponent);

    addAndMakeVisible(m_amplitudeAdsrComponent);

    addAndMakeVisible(m_masterComponent);

    addAndMakeVisible(m_keyboardComponent);
}

void SynthesiserComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
}

void SynthesiserComponent::resized()
{
    //  sounds    dry       wet      master
    // | OSC 1 | FILTER 1 | DELAY  |  ADSR  |
    // | OSC 2 | FILTER 2 | REVERB |  ADSR  |
    // | OSC 3 |          |        |  ADSR  |
    // |       |          |        | MASTER |
    // |              KEYBOARD              |

    const int panelWidth = getWidth() / 4;
    const int panelHeight = getHeight() / 5;
    const int column0X = 0;
    const int column1X = column0X + panelWidth;
    const int column2X = column1X + panelWidth;
    const int column3X = column2X + panelWidth;
    const int row0Y = 0;
    const int row1Y = row0Y + panelHeight;
    const int row2Y = row1Y + panelHeight;
    const int row3Y = row2Y + panelHeight;
    const int row4Y = row3Y + panelHeight;

    m_oscillator1Component.setBounds(column0X, row0Y, panelWidth, panelHeight);
    m_oscillator2Component.setBounds(column0X, row1Y, panelWidth, panelHeight);
    m_oscillator3Component.setBounds(column0X, row2Y, panelWidth, panelHeight);

    m_filter1Component.setBounds(column1X, row0Y, panelWidth, panelHeight);
    m_filter2Component.setBounds(column1X, row1Y, panelWidth, panelHeight);

    m_delayComponent.setBounds(column2X, row0Y, panelWidth, panelHeight);

    m_amplitudeAdsrComponent.setBounds(column3X, row0Y, panelWidth, panelHeight * 3);
    m_masterComponent.setBounds(column3X, row3Y, panelWidth, panelHeight);

    m_keyboardComponent.setBounds(column0X, row4Y, panelWidth * 4, panelHeight);
}
