#include "Synthesiser.h"

#include "SynthSound.h"
#include "SynthVoice.h"

Synthesiser::Synthesiser(StateParameters& stateParameters)
    : m_stateParameters(stateParameters)
{
    addSound(new SynthSound());
    addVoice(new SynthVoice());
}

void Synthesiser::initialise (const double sampleRate, const int samplesPerBlock, int numOutputChannels)
{
    setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, numOutputChannels);
        }
    }
}

void Synthesiser::processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer)
{
    // Update parameters
    for (int i = 0; i < getNumVoices(); ++i) {
        if (auto* voice = dynamic_cast<SynthVoice*>(getVoice(i)))
        {
            auto osc1FunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC1FUNCTION"));
            voice->updateOscillator1FunctionType(osc1FunctionType);

            const float osc1FmFrequency = m_stateParameters.getParameterValue("OSC1FMFREQ");
            const float osc1FmDepth = m_stateParameters.getParameterValue("OSC1FMDEPTH");
            voice->updateOscillator1FrequencyModulation(osc1FmFrequency, osc1FmDepth);

            auto osc2FunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC2FUNCTION"));
            voice->updateOscillator2FunctionType(osc2FunctionType);

            const float osc2FmFrequency = m_stateParameters.getParameterValue("OSC2FMFREQ");
            const float osc2FmDepth = m_stateParameters.getParameterValue("OSC2FMDEPTH");
            voice->updateOscillator2FrequencyModulation(osc2FmFrequency, osc2FmDepth);

            auto osc3FunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC3FUNCTION"));
            voice->updateOscillator3FunctionType(osc3FunctionType);

            const float osc3FmFrequency = m_stateParameters.getParameterValue("OSC3FMFREQ");
            const float osc3FmDepth = m_stateParameters.getParameterValue("OSC3FMDEPTH");
            voice->updateOscillator3FrequencyModulation(osc3FmFrequency, osc3FmDepth);

            const float attack = m_stateParameters.getParameterValue("AMPATTACK");
            const float decay = m_stateParameters.getParameterValue("AMPDECAY");
            const float sustain = m_stateParameters.getParameterValue("AMPSUSTAIN");
            const float release = m_stateParameters.getParameterValue("AMPRELEASE");
            voice->updateAmplitudeAdsr(attack, decay, sustain, release);

            const float modAttack = m_stateParameters.getParameterValue("MODATTACK");
            const float modDecay = m_stateParameters.getParameterValue("MODDECAY");
            const float modSustain = m_stateParameters.getParameterValue("MODSUSTAIN");
            const float modRelease = m_stateParameters.getParameterValue("MODRELEASE");
            voice->updateModulationAdsr(modAttack, modDecay, modSustain, modRelease);

            auto filter1Type = static_cast<juce::dsp::StateVariableTPTFilterType>(m_stateParameters.getParameterValue("FILTER1TYPE"));
            const float filter1Cutoff = m_stateParameters.getParameterValue("FILTER1CUTOFF");
            const float filter1Resonance = m_stateParameters.getParameterValue("FILTER1RES");
            voice->updateFilter1(filter1Type, filter1Cutoff, filter1Resonance);

            auto filter2Type = static_cast<juce::dsp::StateVariableTPTFilterType>(m_stateParameters.getParameterValue("FILTER2TYPE"));
            const float filter2Cutoff = m_stateParameters.getParameterValue("FILTER2CUTOFF");
            const float filter2Resonance = m_stateParameters.getParameterValue("FILTER2RES");
            voice->updateFilter2(filter2Type, filter2Cutoff, filter2Resonance);
        }
    }

    renderNextBlock(audioBuffer, midiBuffer, 0, audioBuffer.getNumSamples());
}