#pragma once

enum OscillatorFunctionType
{
    SINE,
    SAW,
    SQUARE,
    TRIANGLE,
    PULSE
};

class OscillatorFunction
{
public:
    static std::function<float(float)> getFunction(const OscillatorFunctionType& functionType)
    {
        switch (functionType) {
            case SINE: return [] (const float x) { return std::sin (x); };
            case SAW: return [] (const float x) { return x / juce::MathConstants<float>::pi; };
            case SQUARE: return [] (const float x) { return x < 0.f ? -1.f : 1.f; };
            case TRIANGLE: return [] (const float x) { return 2.0f * std::abs (x / juce::MathConstants<float>::pi) - 1.0f; };
            case PULSE:
            {
                float pulseWidth = 0.0f; // Map your 0.0–1.0 UI parameter to range [-3, 3]
                return [pulseWidth] (const float x) { return x < pulseWidth ? -1.0f : 1.0f; };
            }
            default:
                return [] (const float x) { return std::sin (x); };
        }
    }
};
