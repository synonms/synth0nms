#include "FilterComponent.h"

FilterComponent::FilterComponent(StateParameters& stateParameters, const std::string& parameterPrefix)
{
    juce::StringArray filterTypes { "lowpass", "bandpass", "highpass" };
    m_filterTypeComboBox.addItemList(filterTypes, 1);
    addAndMakeVisible(m_filterTypeComboBox);

    setSliderParams(m_cutoffSlider, m_cutoffLabel);
    setSliderParams(m_resonanceSlider, m_resonanceLabel);

    stateParameters.addChoiceParameter(parameterPrefix + "TYPE", "Filter Type", juce::StringArray { "lowpass", "bandpass", "highpass" }, 0);
    stateParameters.addFloatParameter(parameterPrefix + "CUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 0 );
    stateParameters.addFloatParameter(parameterPrefix + "RES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f );

    stateParameters.registerComboBoxAttachment(parameterPrefix + "TYPE", m_filterTypeComboBox);
    stateParameters.registerSliderAttachment(parameterPrefix + "CUTOFF", m_cutoffSlider);
    stateParameters.registerSliderAttachment(parameterPrefix + "RES", m_resonanceSlider);
}

FilterComponent::~FilterComponent() = default;

void FilterComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
    graphics.setColour(juce::Colours::black);
    graphics.drawRect(getLocalBounds());
}

void FilterComponent::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds().reduced(10);
    const int padding = 10;
    const int width = bounds.getWidth() - (padding * 2);
    const int height = 40;
    const int x = 0 + padding;
    const int y = 0 + padding;

    m_filterTypeComboBox.setBounds (x, y, width, height);

    const int fmBlockTop = m_filterTypeComboBox.getBottom() + padding;
    const int fmBlockWidth = 200;
    const int fmLabelHeight = 40;
    const int fmDialHeight = 100;

    m_cutoffLabel.setBounds (x, fmBlockTop, fmBlockWidth, fmLabelHeight);
    m_cutoffSlider.setBounds (m_cutoffLabel.getX(), m_cutoffLabel.getBottom() + padding, fmBlockWidth, fmDialHeight);

    m_resonanceLabel.setBounds (m_cutoffLabel.getRight() + padding, fmBlockTop, fmBlockWidth, fmLabelHeight);
    m_resonanceSlider.setBounds (m_resonanceLabel.getX(), m_resonanceLabel.getBottom() + padding, fmBlockWidth, fmDialHeight);
}

void FilterComponent::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
