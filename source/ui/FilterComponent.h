#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class FilterComponent : public juce::Component
{
public:
    FilterComponent(StateParameters& stateParameters, const std::string& parameterPrefix);
    ~FilterComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::ComboBox m_filterTypeComboBox;

    juce::Slider m_cutoffSlider;
    juce::Label m_cutoffLabel {"CUTOFFLABEL", "Cutoff"};

    juce::Slider m_resonanceSlider;
    juce::Label m_resonanceLabel {"RESONANCELABEL", "Resonance"};

    void setSliderParams(juce::Slider& slider, juce::Label& label);
};
