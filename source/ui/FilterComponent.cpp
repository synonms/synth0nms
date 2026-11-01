#include "FilterComponent.h"

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& audioProcessorValueTreeState)
    : juce::Component()
    , m_audioProcessorValueTreeState(audioProcessorValueTreeState)
{
    juce::StringArray filterTypes { "lowpass", "bandpass", "highpass" };
    m_filterTypeComboBox.addItemList(filterTypes, 1);
    addAndMakeVisible(m_filterTypeComboBox);
    m_filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessorValueTreeState, "FILTERTYPE", m_filterTypeComboBox);

    setSliderParams(m_cutoffSlider, m_cutoffLabel, m_cutoffAttachment, "FILTERCUTOFF");
    setSliderParams(m_resonanceSlider, m_resonanceLabel, m_resonanceAttachment, "FILTERRES");
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

void FilterComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& attachment, const std::string& parameterId)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);

    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(m_audioProcessorValueTreeState, parameterId, slider);
}
