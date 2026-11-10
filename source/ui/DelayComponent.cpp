#include "DelayComponent.h"

DelayComponent::DelayComponent(StateParameters& stateParameters)
{
    setSliderParams(m_delayInSecondsSlider, m_delayInSecondsLabel);
    setSliderParams(m_intensitySlider, m_intensityLabel);

    stateParameters.addFloatParameter("DELAYINS", "Delay in secs", juce::NormalisableRange<float> { 0.0f, 2.0f, 0.1f }, 0.5f );
    stateParameters.addFloatParameter("DELAYINTENSITY", "Intensity", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.1f }, 0.5f );

    stateParameters.registerSliderAttachment("DELAYINS", m_delayInSecondsSlider);
    stateParameters.registerSliderAttachment("DELAYINTENSITY", m_intensitySlider);
}

void DelayComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
    graphics.setColour(juce::Colours::black);
    graphics.drawRect(getLocalBounds());
}

void DelayComponent::resized()
{
    const auto width = getBounds().getWidth();
    const auto height = getBounds().getHeight();

    const int padding = width / 100;
    const int dialSize = height / 2;
    const int labelHeight = dialSize / 4;

    m_delayInSecondsLabel.setBounds (padding, padding, dialSize, labelHeight);
    m_delayInSecondsSlider.setBounds (m_delayInSecondsLabel.getX(), m_delayInSecondsLabel.getBottom() + padding, dialSize, dialSize);

    m_intensityLabel.setBounds (m_delayInSecondsLabel.getRight() + padding, padding, dialSize, labelHeight);
    m_intensitySlider.setBounds (m_intensityLabel.getX(), m_intensityLabel.getBottom() + padding, dialSize, dialSize);
}

void DelayComponent::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
