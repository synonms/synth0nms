#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class DelayComponent : public juce::Component
{
public:
    DelayComponent(StateParameters& stateParameters);
    ~DelayComponent() override = default;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::ComboBox m_filterTypeComboBox;

    juce::Slider m_delayInSecondsSlider;
    juce::Label m_delayInSecondsLabel {"DELAYLABEL", "Delay (s)"};

    juce::Slider m_intensitySlider;
    juce::Label m_intensityLabel {"INTENSITYLABEL", "Intensity"};

    void setSliderParams(juce::Slider& slider, juce::Label& label);
};

