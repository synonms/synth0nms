#include "ModulationOscillator.h"

ModulationOscillator::ModulationOscillator() : juce::dsp::Oscillator<float>([] (float x) { return std::sin (x); })
{

}

void ModulationOscillator::prepareToPlay(const juce::dsp::ProcessSpec& processSpec)
{
    prepare(processSpec);
}

void ModulationOscillator::setFunctionType(const OscillatorFunctionType& functionType)
{
    auto function = OscillatorFunction::getFunction(functionType);
    initialise(function);
}

void ModulationOscillator::startNote(const int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    double frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    setFrequency(static_cast<float>(frequency));
}

void ModulationOscillator::stopNote(float velocity, bool allowTailOff)
{
}
