#include "AdsrComponent.h"

AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState, const std::string& attackId, const std::string& decayId, const std::string& sustainId, const std::string& releaseId)
    : juce::Component()
    , m_audioProcessorValueTreeState(audioProcessorValueTreeState)
{
    m_attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_audioProcessorValueTreeState, attackId, m_attackSlider);
    m_decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_audioProcessorValueTreeState, decayId, m_decaySlider);
    m_sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_audioProcessorValueTreeState, sustainId, m_sustainSlider);
    m_releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_audioProcessorValueTreeState, releaseId, m_releaseSlider);

    setSliderParams(m_attackSlider);
    setSliderParams(m_decaySlider);
    setSliderParams(m_sustainSlider);
    setSliderParams(m_releaseSlider);
}

AdsrComponent::~AdsrComponent() = default;

void AdsrComponent::paint(juce::Graphics& graphics)
{
    graphics.fillAll(juce::Colours::ivory);
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