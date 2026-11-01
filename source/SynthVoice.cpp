#include "SynthVoice.h"

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannelCount)
{
    juce::dsp::ProcessSpec processSpec {};
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = outputChannelCount;

    m_oscillator.prepareToPlay(processSpec);
    m_adsr.prepareToPlay(processSpec);

    m_gain.prepare(processSpec);
    m_gain.setGainLinear(0.1f);
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    m_oscillator.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
    m_adsr.startNote(midiNoteNumber, velocity, sound, currentPitchWheelPosition);
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    m_oscillator.stopNote(velocity, allowTailOff);
    m_adsr.stopNote(velocity, allowTailOff);

    if (!allowTailOff || !m_adsr.isActive()) {
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

    // Write oscillator waves to audio buffer
    m_oscillator.renderNextBlock(context);

    // Bring down gain to avoid blowing ear drums
    m_gain.process(context);

    // Apply ADSR Function (Attack, Decay, Sustain, Release)
    m_adsr.renderNextBlock(outputBuffer, startSample, numSamples);

    if (!m_adsr.isActive()) {
        clearCurrentNote();
    }
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    m_adsr.update(attack, decay, sustain, release);
}

void SynthVoice::updateFunctionType(const OscillatorFunctionType &functionType)
{
    m_oscillator.setFunctionType(functionType);
}

void SynthVoice::updateFrequencyModulation(float frequency, float depth)
{
    m_oscillator.setFrequencyModulation(frequency, depth);
}
