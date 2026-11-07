#include "Synthesiser.h"

#include "SynthSound.h"
#include "SynthVoice.h"

Synthesiser::Synthesiser(StateParameters& stateParameters)
    : m_stateParameters(stateParameters)
{
    addSound(new SynthSound());
    addVoice(new SynthVoice());
    addVoice(new SynthVoice());
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

    m_rmsLevelsInDecibels[0].reset(sampleRate, 0.5);
    m_rmsLevelsInDecibels[1].reset(sampleRate, 0.5);
    m_rmsLevelsInDecibels[0].setCurrentAndTargetValue(-100.f);
    m_rmsLevelsInDecibels[1].setCurrentAndTargetValue(-100.f);
}

void Synthesiser::processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer)
{
    // Get state and update parameters
    // TODO: Only do this on change
    auto osc1Enabled = static_cast<bool>(m_stateParameters.getParameterValue("OSC1ENABLED"));
    auto osc1FunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC1FUNCTION"));
    auto osc1BlendFunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC1BLENDFUNCTION"));
    const float osc1BlendRatio = m_stateParameters.getParameterValue("OSC1BLENDRATIO");
    auto osc2Enabled = static_cast<bool>(m_stateParameters.getParameterValue("OSC2ENABLED"));
    auto osc2FunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC2FUNCTION"));
    auto osc2BlendFunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC2BLENDFUNCTION"));
    const float osc2BlendRatio = m_stateParameters.getParameterValue("OSC2BLENDRATIO");
    auto osc3Enabled = static_cast<bool>(m_stateParameters.getParameterValue("OSC3ENABLED"));
    auto osc3FunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC3FUNCTION"));
    auto osc3BlendFunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("OSC3BLENDFUNCTION"));
    const float osc3BlendRatio = m_stateParameters.getParameterValue("OSC3BLENDRATIO");

    auto modulationOscEnabled = static_cast<bool>(m_stateParameters.getParameterValue("MODOSC1ENABLED"));
    auto modulationOscFunctionType = static_cast<OscillatorFunctionType>(m_stateParameters.getParameterValue("MODOSC1FUNCTION"));

    const float ampAttack = m_stateParameters.getParameterValue("AMPATTACK");
    const float ampDecay = m_stateParameters.getParameterValue("AMPDECAY");
    const float ampSustain = m_stateParameters.getParameterValue("AMPSUSTAIN");
    const float ampRelease = m_stateParameters.getParameterValue("AMPRELEASE");

    auto filter1Type = static_cast<juce::dsp::StateVariableTPTFilterType>(m_stateParameters.getParameterValue("FILTER1TYPE"));
    const float filter1Cutoff = m_stateParameters.getParameterValue("FILTER1CUTOFF");
    const float filter1Resonance = m_stateParameters.getParameterValue("FILTER1RES");

    auto filter2Type = static_cast<juce::dsp::StateVariableTPTFilterType>(m_stateParameters.getParameterValue("FILTER2TYPE"));
    const float filter2Cutoff = m_stateParameters.getParameterValue("FILTER2CUTOFF");
    const float filter2Resonance = m_stateParameters.getParameterValue("FILTER2RES");

    for (int i = 0; i < getNumVoices(); ++i) {
        if (auto* voice = dynamic_cast<SynthVoice*>(getVoice(i)))
        {
            voice->updateOscillator1(osc1Enabled, osc1FunctionType, osc1BlendFunctionType, osc1BlendRatio);
            voice->updateOscillator2(osc2Enabled, osc2FunctionType, osc2BlendFunctionType, osc2BlendRatio);
            voice->updateOscillator3(osc3Enabled, osc3FunctionType, osc3BlendFunctionType, osc3BlendRatio);

            voice->updateModulationOscillator(modulationOscEnabled, modulationOscFunctionType);

            voice->updateAmplitudeAdsr(ampAttack, ampDecay, ampSustain, ampRelease);

            voice->updateFilter1(filter1Type, filter1Cutoff, filter1Resonance);
            voice->updateFilter2(filter2Type, filter2Cutoff, filter2Resonance);
        }
    }

    renderNextBlock(audioBuffer, midiBuffer, 0, audioBuffer.getNumSamples());

    // Get RMS in range [0.0..1.0]
    float rmsLevelLeft = audioBuffer.getRMSLevel(0, 0, audioBuffer.getNumSamples());
    float rmsLevelRight = audioBuffer.getRMSLevel(1, 0, audioBuffer.getNumSamples());
    // Convert to dB and store
    float rmsLevelLeftInDecibels = juce::Decibels::gainToDecibels(rmsLevelLeft);
    float rmsLevelRightInDecibels = juce::Decibels::gainToDecibels(rmsLevelRight);

    m_rmsLevelsInDecibels[0].skip(audioBuffer.getNumSamples());
    m_rmsLevelsInDecibels[1].skip(audioBuffer.getNumSamples());

    if (rmsLevelLeftInDecibels < m_rmsLevelsInDecibels[0].getCurrentValue())
    {
        m_rmsLevelsInDecibels[0].setTargetValue(rmsLevelLeftInDecibels);
    }
    else
    {
        m_rmsLevelsInDecibels[0].setCurrentAndTargetValue(rmsLevelLeftInDecibels);
    }

    if (rmsLevelRightInDecibels < m_rmsLevelsInDecibels[1].getCurrentValue())
    {
        m_rmsLevelsInDecibels[1].setTargetValue(rmsLevelRightInDecibels);
    }
    else
    {
        m_rmsLevelsInDecibels[1].setCurrentAndTargetValue(rmsLevelRightInDecibels);
    }
}