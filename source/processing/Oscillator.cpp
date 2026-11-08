#include "Oscillator.h"

Oscillator::Oscillator() : juce::dsp::Oscillator<float>([] (float x) { return std::sin (x); })
{
}

void Oscillator::apply(juce::AudioBuffer<float>& audioBuffer, const int startSample, const int numSamples)
{
    if (!isEnabled) return;

    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(audioBuffer).getSubBlock(startSample, numSamples);
    const juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    process(context);
}

void Oscillator::initialise(const juce::dsp::ProcessSpec& processSpec)
{
    prepare(processSpec);
}



void Oscillator::setBlendFunctionType(const OscillatorFunctionType &functionType)
{
    m_blendFunction = OscillatorFunction::getFunction(functionType);
    updateFunction();
}

void Oscillator::setBlendRatio(const float blendRatio)
{
    m_blendRatio = std::clamp(blendRatio, 0.0f, 1.0f);
    updateFunction();
}

void Oscillator::setFunctionType(const OscillatorFunctionType& functionType)
{
    m_function = OscillatorFunction::getFunction(functionType);
    updateFunction();
}

void Oscillator::startNote(const int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    const auto frequency = static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    setFrequency(frequency);
}

void Oscillator::stopNote(float velocity, bool allowTailOff)
{
}

void Oscillator::updateFunction()
{
    auto function = [this](float x)
    {
        const float a = m_function(x) * (1.0f - m_blendRatio);
        const float b = m_blendFunction(x) * m_blendRatio;
        return a + b;
    };
    juce::dsp::Oscillator<float>::initialise(function);
}