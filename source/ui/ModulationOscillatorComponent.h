#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class ModulationOscillatorComponent: public juce::Component
{
public:
    ModulationOscillatorComponent(StateParameters& stateParameters, const std::string& parameterPrefix);
    ~ModulationOscillatorComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::TextButton m_enabledButton;
    juce::ComboBox m_functionComboBox;

    void setSliderParams(juce::Slider& slider, juce::Label& label);
};
