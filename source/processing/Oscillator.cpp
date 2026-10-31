#include "Oscillator.h"

Oscillator::Oscillator() : juce::dsp::Oscillator<float>([] (float x) { return std::sin (x); })
{

}

void Oscillator::prepareToPlay(const juce::dsp::ProcessSpec &processSpec)
{
    prepare(processSpec);
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

void Oscillator::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    double frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    setFrequency(static_cast<float>(frequency));
}

void Oscillator::stopNote(float velocity, bool allowTailOff)
{
}

void Oscillator::renderNextBlock(juce::dsp::ProcessContextReplacing<float> &context)
{
    process(context);
}
