#include "OscillatorModule.h"

OscillatorModule::OscillatorModule() : juce::dsp::Oscillator<float>([] (float x) { return std::sin (x); })
{
}

void OscillatorModule::apply(juce::AudioBuffer<float>& audioBuffer, const int startSample, const int numSamples)
{
    if (!isEnabled) return;

    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(audioBuffer).getSubBlock(startSample, numSamples);
    const juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    process(context);
}

void OscillatorModule::initialise(const juce::dsp::ProcessSpec& processSpec)
{
    prepare(processSpec);
}



void OscillatorModule::setBlendFunctionType(const OscillatorFunctionType &functionType)
{
    m_blendFunction = OscillatorFunction::getFunction(functionType);
    updateFunction();
}

void OscillatorModule::setBlendRatio(const float blendRatio)
{
    m_blendRatio = std::clamp(blendRatio, 0.0f, 1.0f);
    updateFunction();
}

void OscillatorModule::setFunctionType(const OscillatorFunctionType& functionType)
{
    m_function = OscillatorFunction::getFunction(functionType);
    updateFunction();
}

void OscillatorModule::startNote(const int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    const auto frequency = static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    setFrequency(frequency);
}

void OscillatorModule::stopNote(float velocity, bool allowTailOff)
{
}

void OscillatorModule::updateFunction()
{
    auto function = [this](float x)
    {
        const float a = m_function(x) * (1.0f - m_blendRatio);
        const float b = m_blendFunction(x) * m_blendRatio;
        return a + b;
    };
    juce::dsp::Oscillator<float>::initialise(function);
}