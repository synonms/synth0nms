#include "OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState)
    : juce::Component()
    , m_audioProcessorValueTreeState(audioProcessorValueTreeState)
{
    juce::StringArray functions { "Sine", "Saw", "Square" };
    m_functionComboBox.addItemList(functions, 1);
    addAndMakeVisible(m_functionComboBox);
    m_functionAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessorValueTreeState, "OSC1FUNCTION", m_functionComboBox);

    setSliderParams(m_fmFrequencySlider, m_fmFrequencyLabel, m_fmFrequencyAttachment, "OSC1FMFREQ");
    setSliderParams(m_fmDepthSlider, m_fmDepthLabel, m_fmDepthAttachment, "OSC1FMDEPTH");
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

void OscillatorComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, const std::string& parameterId)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_audioProcessorValueTreeState, parameterId, slider);
}