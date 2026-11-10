#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include "../StateParameters.h"

class MasterComponent : public juce::Component
{
public:
    MasterComponent(StateParameters& stateParameters);
    ~MasterComponent() override = default;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

    void setRmsLevelsInDecibels(const float rmsLevelLeftInDecibels, const float rmsLevelRightInDecibels)
    {
        m_rmsLevelLeftInDecibels = rmsLevelLeftInDecibels;
        m_rmsLevelRightInDecibels = rmsLevelRightInDecibels;
    }

private:
    juce::Slider m_gainSlider;
    juce::Label m_gainLabel {"GAINLABEL", "Gain"};

    float m_rmsLevelLeftInDecibels { -60.f };
    float m_rmsLevelRightInDecibels { -60.f };

    void setSliderParams(juce::Slider& slider, juce::Label& label);

    static void paintMeter(juce::Graphics& graphics, juce::Rectangle<float> bounds, float rmsLevelInDecibels);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterComponent)
};
