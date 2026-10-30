#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth0nmsAudioProcessorEditor::Synth0nmsAudioProcessorEditor (Synth0nmsAudioProcessor& audioProcessor)
    : AudioProcessorEditor (&audioProcessor)
    , m_audioProcessor (audioProcessor)
    , m_keyboardComponent (audioProcessor.keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (2048, 1024);
    addAndMakeVisible (m_keyboardComponent);
    m_keyboardComponent.setBounds (0, 0, 2048, 256);

    m_attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.audioProcessorValueTreeState, "ATTACK", m_attackSlider);
    m_decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.audioProcessorValueTreeState, "DECAY", m_decaySlider);
    m_sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.audioProcessorValueTreeState, "SUSTAIN", m_sustainSlider);
    m_releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.audioProcessorValueTreeState, "RELEASE", m_releaseSlider);
    m_waveformSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.audioProcessorValueTreeState, "OSC", m_waveformSelector);

    setSliderParams(m_attackSlider);
    setSliderParams(m_decaySlider);
    setSliderParams(m_sustainSlider);
    setSliderParams(m_releaseSlider);
}

Synth0nmsAudioProcessorEditor::~Synth0nmsAudioProcessorEditor() = default;

//==============================================================================
void Synth0nmsAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Synth0nms", getLocalBounds(), juce::Justification::centred, 1);
}

void Synth0nmsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any subcomponents in your editor.
    m_keyboardComponent.setBounds (10, getHeight() - 110, getWidth() - 20, 100);

    const juce::Rectangle<int> bounds = getLocalBounds().reduced(10);
    const int padding = 10;
    const int sliderWidth = bounds.getWidth() / 4 - padding;
    const int sliderHeight = bounds.getHeight() / 4 - padding;
    const int sliderStartX = 0;
    const int sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    m_attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    m_decaySlider.setBounds (m_attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    m_sustainSlider.setBounds (m_decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    m_releaseSlider.setBounds (m_sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void Synth0nmsAudioProcessorEditor::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}