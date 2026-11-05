#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class OscillatorComponent : public juce::Component
{
public:
    OscillatorComponent(StateParameters& stateParameters, const std::string& parameterPrefix);
    ~OscillatorComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::ComboBox m_functionComboBox;
    juce::Slider m_fmFrequencySlider;
    juce::Label m_fmFrequencyLabel {"FMFREQLABEL", "Frequency"};
    juce::Slider m_fmDepthSlider;
    juce::Label m_fmDepthLabel {"FMDEPTHLABEL", "Depth"};

    void setSliderParams(juce::Slider& slider, juce::Label& label);
};
