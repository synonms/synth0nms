#include "OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(StateParameters& stateParameters, const std::string& parameterPrefix)
{
    juce::StringArray functions { "Sine", "Saw", "Square" };
    m_functionComboBox.addItemList(functions, 1);
    addAndMakeVisible(m_functionComboBox);

    setSliderParams(m_fmFrequencySlider, m_fmFrequencyLabel);
    setSliderParams(m_fmDepthSlider, m_fmDepthLabel);

    stateParameters.addChoiceParameter(parameterPrefix + "FUNCTION", "Oscillator Function", juce::StringArray { "Sine", "Saw", "Square" }, 0);
    stateParameters.addFloatParameter(parameterPrefix + "FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 5.0f );
    stateParameters.addFloatParameter(parameterPrefix + "FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 500.0f );

    stateParameters.registerComboBoxAttachment(parameterPrefix + "FUNCTION", m_functionComboBox);
    stateParameters.registerSliderAttachment(parameterPrefix + "FMFREQ", m_fmFrequencySlider);
    stateParameters.registerSliderAttachment(parameterPrefix + "FMDEPTH", m_fmDepthSlider);
}

OscillatorComponent::~OscillatorComponent() = default;

void OscillatorComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
    graphics.setColour(juce::Colours::black);
    graphics.drawRect(getLocalBounds());
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

    const int fmBlockTop = m_functionComboBox.getBottom() + padding;
    const int fmBlockWidth = 200;
    const int fmLabelHeight = 40;
    const int fmDialHeight = 100;

    m_fmFrequencyLabel.setBounds (x, fmBlockTop, fmBlockWidth, fmLabelHeight);
    m_fmFrequencySlider.setBounds (m_fmFrequencyLabel.getX(), m_fmFrequencyLabel.getBottom() + padding, fmBlockWidth, fmDialHeight);

    m_fmDepthLabel.setBounds (m_fmFrequencyLabel.getRight() + padding, fmBlockTop, fmBlockWidth, fmLabelHeight);
    m_fmDepthSlider.setBounds (m_fmDepthLabel.getX(), m_fmDepthLabel.getBottom() + padding, fmBlockWidth, fmDialHeight);
}

void OscillatorComponent::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}