#include "ModulationOscillatorComponent.h"

ModulationOscillatorComponent::ModulationOscillatorComponent(StateParameters& stateParameters, const std::string& parameterPrefix)
{
    m_enabledButton.setClickingTogglesState(true);
    m_enabledButton.setButtonText("Bypass");
    addAndMakeVisible(m_enabledButton);

    const juce::StringArray functions { "Sine", "Saw", "Square", "Triangle", "Pulse" };
    m_functionComboBox.addItemList(functions, 1);
    addAndMakeVisible(m_functionComboBox);

    stateParameters.addBoolParameter(parameterPrefix + "ENABLED", "Enabled", false);
    stateParameters.addChoiceParameter(parameterPrefix + "FUNCTION", "Oscillator Function", juce::StringArray { "Sine", "Saw", "Square", "Triangle", "Pulse" }, 0);

    stateParameters.registerTextButtonAttachment(parameterPrefix + "ENABLED", m_enabledButton);
    stateParameters.registerComboBoxAttachment(parameterPrefix + "FUNCTION", m_functionComboBox);
}

ModulationOscillatorComponent::~ModulationOscillatorComponent() = default;


void ModulationOscillatorComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
    graphics.setColour(juce::Colours::black);
    graphics.drawRect(getLocalBounds());
}

void ModulationOscillatorComponent::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds().reduced(10);
    const int padding = 10;
    const int availableWidth = bounds.getWidth() - (padding * 2);
    const int availableHeight = bounds.getHeight() - (padding * 2);
    const int headerHeight = availableHeight / 4;

    m_enabledButton.setBounds(0 + padding, 0 + padding, availableWidth / 4, headerHeight);
    m_functionComboBox.setBounds (m_enabledButton.getRight() + padding, 0 + padding, availableWidth - m_enabledButton.getWidth() - padding, headerHeight);
}

void ModulationOscillatorComponent::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}