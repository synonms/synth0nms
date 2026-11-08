#include "SynthVoice.h"

void SynthVoice::prepareToPlay (const double sampleRate, const int samplesPerBlock, const int outputChannelCount)
{
    juce::dsp::ProcessSpec processSpec {};
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = outputChannelCount;

    m_oscillator1.initialise(processSpec);
    m_oscillator1.setIsEnabled(true);
    m_oscillator2.initialise(processSpec);
    m_oscillator2.setIsEnabled(false);
    m_oscillator3.initialise(processSpec);
    m_oscillator3.setIsEnabled(false);

    m_filter1.initialise(processSpec);
    m_filter2.initialise(processSpec);

    m_amplitudeAdsr.initialise(processSpec);

    m_gain.prepare(processSpec);
    m_gain.setGainLinear(0.1f);
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return sound != nullptr;
}

void SynthVoice::startNote (const int midiNoteNumber, const float velocity, juce::SynthesiserSound* sound, const int currentPitchWheelPosition)
{
    m_oscillator1.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_oscillator2.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_oscillator3.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_amplitudeAdsr.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
}

void SynthVoice::stopNote (const float velocity, const bool allowTailOff)
{
    m_oscillator1.stopNote(velocity, allowTailOff);
    m_oscillator2.stopNote(velocity, allowTailOff);
    m_oscillator3.stopNote(velocity, allowTailOff);
    m_amplitudeAdsr.stopNote(velocity, allowTailOff);

    if (!allowTailOff || !m_amplitudeAdsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{

}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float>& outputBuffer, const int startSample, const int numSamples)
{
    if (!isVoiceActive()) return;

    juce::dsp::AudioBlock<float> audioBlock = juce::dsp::AudioBlock<float>(outputBuffer).getSubBlock(startSample, numSamples);
    const juce::dsp::ProcessContextReplacing<float> context(audioBlock);

    // Write oscillator waves to audio buffer
    m_oscillator1.apply(outputBuffer, startSample, numSamples);
    m_oscillator2.apply(outputBuffer, startSample, numSamples);
    m_oscillator3.apply(outputBuffer, startSample, numSamples);

    // Apply filters
    m_filter1.apply(outputBuffer, startSample, numSamples);
    m_filter2.apply(outputBuffer, startSample, numSamples);

    // Apply Amplitude ADSR Function (Attack, Decay, Sustain, Release)
    m_amplitudeAdsr.apply(outputBuffer, startSample, numSamples);

    // Bring down gain to avoid blowing ear drums
    m_gain.process(context);

    if (!m_amplitudeAdsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::updateOscillator1(const bool isEnabled, const OscillatorFunctionType& functionType, const OscillatorFunctionType& blendFunctionType, const float blendRatio)
{
    m_oscillator1.setIsEnabled(isEnabled);
    m_oscillator1.setFunctionType(functionType);
    m_oscillator1.setBlendFunctionType(blendFunctionType);
    m_oscillator1.setBlendRatio(blendRatio);
}

void SynthVoice::updateOscillator2(const bool isEnabled, const OscillatorFunctionType& functionType, const OscillatorFunctionType& blendFunctionType, const float blendRatio)
{
    m_oscillator2.setIsEnabled(isEnabled);
    m_oscillator2.setFunctionType(functionType);
    m_oscillator2.setBlendFunctionType(blendFunctionType);
    m_oscillator2.setBlendRatio(blendRatio);
}

void SynthVoice::updateOscillator3(const bool isEnabled, const OscillatorFunctionType& functionType, const OscillatorFunctionType& blendFunctionType, const float blendRatio)
{
    m_oscillator3.setIsEnabled(isEnabled);
    m_oscillator3.setFunctionType(functionType);
    m_oscillator3.setBlendFunctionType(blendFunctionType);
    m_oscillator3.setBlendRatio(blendRatio);
}

void SynthVoice::updateFilter1(const juce::dsp::StateVariableTPTFilterType& type, const float cutoffFrequency, const float resonance)
{
//    float modulator = m_modulationAdsr.getNextSample();
    m_filter1.updateParameters(type, cutoffFrequency, resonance, 1.f);
}

void SynthVoice::updateFilter2(const juce::dsp::StateVariableTPTFilterType& type, const float cutoffFrequency, const float resonance)
{
//    float modulator = m_modulationAdsr.getNextSample();
    m_filter2.updateParameters(type, cutoffFrequency, resonance, 1.f);
}

void SynthVoice::updateAmplitudeAdsr(const float attack, const float decay, const float sustain, const float release)
{
    m_amplitudeAdsr.update(attack, decay, sustain, release);
}
