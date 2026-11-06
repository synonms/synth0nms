#include "SynthVoice.h"

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannelCount)
{
    juce::dsp::ProcessSpec processSpec {};
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = outputChannelCount;

    m_oscillator1.prepareToPlay(processSpec);
    m_oscillator2.prepareToPlay(processSpec);
    m_oscillator3.prepareToPlay(processSpec);
    m_amplitudeAdsr.prepareToPlay(processSpec);
    m_filter1.prepareToPlay(processSpec);
    m_filter2.prepareToPlay(processSpec);
    m_modulationAdsr.prepareToPlay(processSpec);

    m_gain.prepare(processSpec);
    m_gain.setGainLinear(0.1f);
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    m_oscillator1.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_oscillator2.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_oscillator3.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_amplitudeAdsr.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_modulationAdsr.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    m_oscillator1.stopNote(velocity, allowTailOff);
    m_oscillator2.stopNote(velocity, allowTailOff);
    m_oscillator3.stopNote(velocity, allowTailOff);
    m_amplitudeAdsr.stopNote(velocity, allowTailOff);
    m_modulationAdsr.stopNote(velocity, allowTailOff);

    if (!allowTailOff || !m_amplitudeAdsr.isActive()) {
        clearCurrentNote();
    }
}

// bool SynthVoice::isVoiceActive() const
// {
// }

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{

}

// void SynthVoice::aftertouchChanged (int newAftertouchValue)
// {
// }

// void SynthVoice::channelPressureChanged (int newChannelPressureValue)
// {
// }

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive()) return;

    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock(startSample, numSamples);
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    // Apply Modulation ADSR before any data has been written (prepares the ADSR)
//    m_modulationAdsr.applyToBuffer(outputBuffer, startSample, numSamples);

    // Write oscillator waves to audio buffer
    m_oscillator1.renderNextBlock(context);
    m_oscillator2.renderNextBlock(context);
    m_oscillator3.renderNextBlock(context);

    // Apply Amplitude ADSR Function (Attack, Decay, Sustain, Release)
    m_amplitudeAdsr.applyToBuffer(outputBuffer, startSample, numSamples);

    // Apply filters
//    m_filter1.renderNextBlock(context);
//    m_filter2.renderNextBlock(context);

    // Bring down gain to avoid blowing ear drums
    m_gain.process(context);

    if (!m_amplitudeAdsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::updateOscillator1FunctionType(const OscillatorFunctionType &functionType)
{
    m_oscillator1.setFunctionType(functionType);
}

void SynthVoice::updateOscillator1FrequencyModulation(float frequency, float depth)
{
    m_oscillator1.setFrequencyModulation(frequency, depth);
}

void SynthVoice::updateOscillator2FunctionType(const OscillatorFunctionType &functionType)
{
    m_oscillator2.setFunctionType(functionType);
}

void SynthVoice::updateOscillator2FrequencyModulation(float frequency, float depth)
{
    m_oscillator2.setFrequencyModulation(frequency, depth);
}

void SynthVoice::updateOscillator3FunctionType(const OscillatorFunctionType &functionType)
{
    m_oscillator3.setFunctionType(functionType);
}

void SynthVoice::updateOscillator3FrequencyModulation(float frequency, float depth)
{
    m_oscillator3.setFrequencyModulation(frequency, depth);
}

void SynthVoice::updateAmplitudeAdsr(const float attack, const float decay, const float sustain, const float release)
{
    m_amplitudeAdsr.update(attack, decay, sustain, release);
}

void SynthVoice::updateFilter1(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance)
{
    float modulator = m_modulationAdsr.getNextSample();
    m_filter1.updateParameters(type, cutoffFrequency, resonance, modulator);
}

void SynthVoice::updateFilter2(const juce::dsp::StateVariableTPTFilterType& type, float cutoffFrequency, float resonance)
{
    float modulator = m_modulationAdsr.getNextSample();
    m_filter2.updateParameters(type, cutoffFrequency, resonance, modulator);
}

void SynthVoice::updateModulationAdsr(const float attack, const float decay, const float sustain, const float release)
{
    m_modulationAdsr.update(attack, decay, sustain, release);
}
