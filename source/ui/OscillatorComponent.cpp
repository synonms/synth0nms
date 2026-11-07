#include "OscillatorComponent.h"

OscillatorComponent::OscillatorComponent(StateParameters& stateParameters, const std::string& parameterPrefix, const bool isEnabledByDefault)
{
    m_enabledButton.setClickingTogglesState(true);
    m_enabledButton.setButtonText("Bypass");
    addAndMakeVisible(m_enabledButton);

    const juce::StringArray functions { "Sine", "Saw", "Square", "Triangle", "Pulse" };
    m_functionComboBox.addItemList(functions, 1);
    addAndMakeVisible(m_functionComboBox);
    m_blendFunctionComboBox.addItemList(functions, 1);
    addAndMakeVisible(m_blendFunctionComboBox);

    m_blendRatioSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_blendRatioSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(m_blendRatioSlider);

    stateParameters.addBoolParameter(parameterPrefix + "ENABLED", "Enabled", isEnabledByDefault);
    stateParameters.addChoiceParameter(parameterPrefix + "FUNCTION", "Oscillator Function", functions, 0);
    stateParameters.addChoiceParameter(parameterPrefix + "BLENDFUNCTION", "Blend Function", functions, 0);
    stateParameters.addFloatParameter(parameterPrefix + "BLENDRATIO", "Blend Ratio", {0.0f, 1.0f, 0.1f}, 0.0f);

    stateParameters.registerTextButtonAttachment(parameterPrefix + "ENABLED", m_enabledButton);
    stateParameters.registerComboBoxAttachment(parameterPrefix + "FUNCTION", m_functionComboBox);
    stateParameters.registerComboBoxAttachment(parameterPrefix + "BLENDFUNCTION", m_blendFunctionComboBox);
    stateParameters.registerSliderAttachment(parameterPrefix + "BLENDRATIO", m_blendRatioSlider);
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
    // |PPPPPPPPPPPPPPP|
    // |P x P xx P xx P|
    // |PPPPPPPPPPPPPPP|
    // |P o P ooooooo P|
    // |P o P ooooooo P|
    // |P o P ooooooo P|
    // |PPPPPPPPPPPPPPP|

    const int padding = 10;
    const int availableWidth = getLocalBounds().getWidth() - (padding * 2);
    const int availableHeight = getLocalBounds().getHeight() - (padding * 2);
    const int headerHeight = availableHeight / 4;
    const int bodyHeight = availableHeight - headerHeight - padding;
    const int contentWidth = availableWidth - (padding * 2);
    const int blockWidth = contentWidth / 5;

    m_enabledButton.setBounds(padding, padding, blockWidth, headerHeight);
    m_functionComboBox.setBounds (m_enabledButton.getRight() + padding, padding, blockWidth * 2, headerHeight);
    m_blendFunctionComboBox.setBounds (m_functionComboBox.getRight() + padding, padding, blockWidth * 2, headerHeight);

    m_blendRatioSlider.setBounds (m_functionComboBox.getX(), m_blendFunctionComboBox.getBottom() + padding, m_functionComboBox.getWidth() + m_blendFunctionComboBox.getWidth() + padding, bodyHeight);
}
