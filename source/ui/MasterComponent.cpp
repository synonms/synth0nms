#include "MasterComponent.h"

MasterComponent::MasterComponent(StateParameters& stateParameters)
{
    setSliderParams(m_gainSlider, m_gainLabel);

    stateParameters.addFloatParameter("GAIN", "Gain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01 }, 0.5f );

    stateParameters.registerSliderAttachment("GAIN", m_gainSlider);
}

void MasterComponent::paint(juce::Graphics& graphics)
{
    const auto localBounds = getLocalBounds();
    const int padding = 10;

    graphics.fillAll(juce::Colours::ivory);
    graphics.setColour(juce::Colours::black);
    graphics.drawRect(localBounds);

    const int meterWidth = localBounds.getWidth() / 20;
    const int meterHeight = localBounds.getHeight() - (padding * 2);
    const int rightMeterX = localBounds.getWidth() - padding - meterWidth;
    const int leftMeterX = rightMeterX - padding - meterWidth;

    const juce::Rectangle<int> leftMeterBounds {leftMeterX, padding, meterWidth, meterHeight};
    const juce::Rectangle<int> rightMeterBounds {leftMeterX, padding, meterWidth, meterHeight};

    paintMeter(graphics, leftMeterBounds.toFloat(), m_rmsLevelLeftInDecibels);
    paintMeter(graphics, rightMeterBounds.toFloat(), m_rmsLevelRightInDecibels);
}

void MasterComponent::resized()
{
    const int padding = 10; // TODO: Make dynamic
    const int blockSize = 200; // TODO: Make dynamic
    const int labelHeight = blockSize / 5;
    const int dialSize = blockSize - labelHeight - padding;

    m_gainLabel.setBounds (padding, padding, blockSize, labelHeight);
    m_gainSlider.setBounds (m_gainLabel.getX(), m_gainLabel.getBottom() + padding, dialSize, dialSize);
}

void MasterComponent::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

void MasterComponent::paintMeter(juce::Graphics& graphics, juce::Rectangle<float> bounds, const float rmsLevelInDecibels)
{
    graphics.setColour(juce::Colours::white.withBrightness(0.4f));
    graphics.fillRoundedRectangle(bounds, 5.f);

    graphics.setColour(juce::Colours::white);
    // Map level from [-60..6f] to [0..height]
    const auto filledHeight = juce::jmap(rmsLevelInDecibels, -60.f, 6.f, 0.f, bounds.getHeight());
    graphics.fillRoundedRectangle(bounds.removeFromBottom(filledHeight), 5.f);
}