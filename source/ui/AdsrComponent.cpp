#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(StateParameters& stateParameters, const juce::String& parameterPrefix)
{
    stateParameters.addFloatParameter(parameterPrefix + "ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f );
    stateParameters.addFloatParameter(parameterPrefix + "DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f );
    stateParameters.addFloatParameter(parameterPrefix + "SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f }, 1.0f );
    stateParameters.addFloatParameter(parameterPrefix + "RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f }, 0.4f );

    stateParameters.addSliderAttachment(parameterPrefix + "ATTACK", m_attackSlider);
    stateParameters.addSliderAttachment(parameterPrefix + "DECAY", m_decaySlider);
    stateParameters.addSliderAttachment(parameterPrefix + "SUSTAIN", m_sustainSlider);
    stateParameters.addSliderAttachment(parameterPrefix + "RELEASE", m_releaseSlider);

    setSliderParams(m_attackSlider);
    setSliderParams(m_decaySlider);
    setSliderParams(m_sustainSlider);
    setSliderParams(m_releaseSlider);
}

AdsrComponent::~AdsrComponent() = default;

void AdsrComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
    setSliderParams(m_attackSlider);
}

void AdsrComponent::resized()
{
    const juce::Rectangle<int> bounds = getLocalBounds().reduced(10);
    const int padding = 10;
    const int sliderWidth = bounds.getWidth() / 4 - padding;
    const int sliderHeight = bounds.getHeight() / 2;
    const int sliderStartX = 0;
    const int sliderStartY = 0;

    m_attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    m_decaySlider.setBounds (m_attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    m_sustainSlider.setBounds (m_decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    m_releaseSlider.setBounds (m_sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}