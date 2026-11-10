#pragma once

#include "AdsrComponent.h"
#include "DelayComponent.h"
#include "FilterComponent.h"
#include "MasterComponent.h"
#include "OscillatorComponent.h"

#include "../StateParameters.h"

class SynthesiserComponent : public juce::Component
{
public:
    SynthesiserComponent(StateParameters& stateParameters, juce::MidiKeyboardState& keyboardState);
    ~SynthesiserComponent() override = default;

    void paint(juce::Graphics& graphics) override;
    void resized() override;

    MasterComponent& getMasterComponent()
    {
        return m_masterComponent;
    }

private:
    OscillatorComponent m_oscillator1Component;
    OscillatorComponent m_oscillator2Component;
    OscillatorComponent m_oscillator3Component;
    FilterComponent m_filter1Component;
    FilterComponent m_filter2Component;
    DelayComponent m_delayComponent;
    AdsrComponent m_amplitudeAdsrComponent;
    MasterComponent m_masterComponent;

    juce::MidiKeyboardComponent m_keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthesiserComponent)
};
