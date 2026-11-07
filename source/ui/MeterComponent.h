#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

#include "../StateParameters.h"

class MeterComponent : public juce::Component
{
public:
    MeterComponent(StateParameters& stateParameters, const juce::String& parameterPrefix);

    void paint(juce::Graphics& graphics) override;
    void resized() override;
    void setRmsLevelInDecibels(const float rmsLevelInDecibels)
    {
        m_rmsLevelInDecibels = rmsLevelInDecibels;
    }

private:
    float m_rmsLevelInDecibels { -60.f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MeterComponent)
};
