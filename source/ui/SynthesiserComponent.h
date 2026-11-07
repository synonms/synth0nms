#pragma once

#include "AdsrComponent.h"
#include "FilterComponent.h"
#include "OscillatorComponent.h"
#include "ModulationOscillatorComponent.h"
#include "MeterComponent.h"

#include "../StateParameters.h"

class SynthesiserComponent : public juce::Component
{
public:
    SynthesiserComponent(StateParameters& stateParameters, juce::MidiKeyboardState& keyboardState);
    ~SynthesiserComponent() override = default;

    void paint(juce::Graphics& graphics) override;
    void resized() override;
    void setRmsLevelInDecibels(int channel, float rmsLevelInDecibels);

private:
    OscillatorComponent m_oscillator1Component;
    OscillatorComponent m_oscillator2Component;
    OscillatorComponent m_oscillator3Component;
    ModulationOscillatorComponent m_modulationOscillatorComponent;
    FilterComponent m_filter1Component;
    FilterComponent m_filter2Component;
    AdsrComponent m_amplitudeAdsrComponent;
    MeterComponent m_meterLeftComponent;
    MeterComponent m_meterRightComponent;

    juce::MidiKeyboardComponent m_keyboardComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SynthesiserComponent)
};
