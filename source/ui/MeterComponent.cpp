#include "MeterComponent.h"

MeterComponent::MeterComponent(StateParameters& stateParameters, const juce::String& parameterPrefix)
{
}

void MeterComponent::paint(juce::Graphics& graphics)
{
    juce::Rectangle<float> bounds = getLocalBounds().toFloat();

    graphics.setColour(juce::Colours::white.withBrightness(0.4f));
    graphics.fillRoundedRectangle(bounds, 5.f);

    graphics.setColour(juce::Colours::white);
    // Map level from [-60..6f] to [0..width]
    const auto scaledX = juce::jmap(m_rmsLevelInDecibels, -60.f, 6.f, 0.f, static_cast<float>(getWidth()));
    graphics.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.f);
}

void MeterComponent::resized()
{
}
