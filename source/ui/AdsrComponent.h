#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class AdsrComponent : public juce::Component
{
public:
    AdsrComponent(StateParameters& stateParameters, const juce::String& parameterPrefix);
    ~AdsrComponent() override;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

private:
    juce::Slider m_attackSlider;
    juce::Slider m_decaySlider;
    juce::Slider m_sustainSlider;
    juce::Slider m_releaseSlider;

    void setSliderParams(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AdsrComponent)
};
