#include "Oscillator.h"

Oscillator::Oscillator() : juce::dsp::Oscillator<float>([] (float x) { return std::sin (x); })
{

}

void Oscillator::prepareToPlay(const juce::dsp::ProcessSpec &processSpec)
{
    prepare(processSpec);

    m_modulationOscillator.prepare(processSpec);
}

void Oscillator::setFunctionType(const OscillatorFunctionType& functionType)
{
    switch (functionType) {
        case SINE: {
            auto sineFunction = [] (const float x) { return std::sin (x); };
            initialise(sineFunction);
            break;
        }
        case SAW: {
            auto sawFunction = [] (const float x) { return x / juce::MathConstants<float>::pi; };
            initialise(sawFunction);
            break;
        }
        case SQUARE: {
            auto squareFunction = [] (const float x) { return x < 0.f ? -1.f : 1.f; };
            initialise(squareFunction);
            break;
        }
        default:
            break;
    }
}

void Oscillator::setFrequencyModulation(float frequency, float depth)
{
    m_modulationOscillator.setFrequency(frequency);
    m_fmDepth = depth;

    auto newFrequency = static_cast<float>(juce::MidiMessage::getMidiNoteInHertz(m_lastMidiNoteNumber) + m_frequencyModifier);

    setFrequency(newFrequency >= 0 ? newFrequency : 0 - newFrequency);
}

void Oscillator::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    double frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);// + m_frequencyModifier;
    setFrequency(static_cast<float>(frequency));

    m_lastMidiNoteNumber = midiNoteNumber;
}

void Oscillator::stopNote(float velocity, bool allowTailOff)
{
}

void Oscillator::renderNextBlock(juce::dsp::ProcessContextReplacing<float>& context)
{
    juce::dsp::AudioBlock<const float> block = context.getInputBlock();

    for (int channel = 0; channel < block.getNumChannels(); ++channel)
    {
        for (int sample = 0; sample < block.getNumSamples(); ++sample)
        {
            // Get the modulation oscillator value at the sample point
            m_frequencyModifier = m_modulationOscillator.processSample(block.getSample(channel, sample)) * m_fmDepth;
        }
    }

    process(context);
}
