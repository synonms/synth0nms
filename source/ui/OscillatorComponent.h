#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class OscillatorComponent : public juce::Component
{
public:
    OscillatorComponent(StateParameters& stateParameters, const std::string& parameterPrefix, bool isEnabledByDefault);
    ~OscillatorComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::TextButton m_enabledButton;
    juce::ComboBox m_functionComboBox;
    juce::ComboBox m_blendFunctionComboBox;
    juce::Slider m_blendRatioSlider;
};
