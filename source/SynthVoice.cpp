#include "SynthVoice.h"

#include <juce_dsp/juce_dsp.h>

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannelCount)
{
    juce::dsp::ProcessSpec processSpec {};
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = outputChannelCount;

    m_oscillator.prepare(processSpec);
    m_gain.prepare(processSpec);

    m_gain.setGainLinear(0.1f);

    m_adsr.setSampleRate(sampleRate);
}

void SynthVoice::updateAdsr(const float attack, const float decay, const float sustain, const float release)
{
    m_adsrParameters.attack = attack;
    m_adsrParameters.decay = decay;
    m_adsrParameters.sustain = sustain;
    m_adsrParameters.release = release;

    m_adsr.setParameters(m_adsrParameters);
}

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    double frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    m_oscillator.setFrequency(static_cast<float>(frequency));
    m_adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    m_adsr.noteOff();

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
    m_oscillator.process(context);

    // Bring down gain to avoid blowing ear drums
    m_gain.process(context);

    // Apply ADSR (Attack, Decay, Sustain, Release)
    m_adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);

    if (!m_adsr.isActive()) {
        clearCurrentNote();
    }
}

