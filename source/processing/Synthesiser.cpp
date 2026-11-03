#include "Synthesiser.h"

#include "SynthSound.h"
#include "SynthVoice.h"

Synthesiser::Synthesiser()
{
    addSound(new SynthSound());
    addVoice(new SynthVoice());
}

juce::AudioProcessorValueTreeState::ParameterLayout Synthesiser::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // Oscillator options
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1FUNCTION", "Oscillator 1 Function", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 5.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 500.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2FUNCTION", "Oscillator 1 Function", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 5.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 500.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("OSC3FUNCTION", "Oscillator 1 Function", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 5.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC3FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 500.0f ));

    // Modulation envelope
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MODATTACK", "Mod Attack", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MODDECAY", "Mod Decay", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MODSUSTAIN", "Mod Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f }, 1.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("MODRELEASE", "Mod Release", juce::NormalisableRange<float> { 0.1f, 3.0f }, 0.4f ));

    // Filter options
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("FILTER1TYPE", "Filter Type", juce::StringArray { "lowpass", "bandpass", "highpass" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER1CUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 0 ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER1RES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("FILTER2TYPE", "Filter Type", juce::StringArray { "lowpass", "bandpass", "highpass" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER2CUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 0 ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER2RES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f ));

    // Amplitude ADSR
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPDECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPSUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f }, 1.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("AMPRELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f }, 0.4f ));

    return { parameters.begin(), parameters.end() };
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

void Synthesiser::processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer, const juce::AudioProcessorValueTreeState& audioProcessorValueTreeState)
{
    // Update parameters
    for (int i = 0; i < getNumVoices(); ++i) {
        if (auto* voice = dynamic_cast<SynthVoice*>(getVoice(i)))
        {
            auto osc1FunctionType = static_cast<OscillatorFunctionType>(audioProcessorValueTreeState.getRawParameterValue("OSC1FUNCTION")->load());
            voice->updateOscillator1FunctionType(osc1FunctionType);

            const float osc1FmFrequency = audioProcessorValueTreeState.getRawParameterValue("OSC1FMFREQ")->load();
            const float osc1FmDepth = audioProcessorValueTreeState.getRawParameterValue("OSC1FMDEPTH")->load();
            voice->updateOscillator1FrequencyModulation(osc1FmFrequency, osc1FmDepth);

            auto osc2FunctionType = static_cast<OscillatorFunctionType>(audioProcessorValueTreeState.getRawParameterValue("OSC2FUNCTION")->load());
            voice->updateOscillator2FunctionType(osc2FunctionType);

            const float osc2FmFrequency = audioProcessorValueTreeState.getRawParameterValue("OSC2FMFREQ")->load();
            const float osc2FmDepth = audioProcessorValueTreeState.getRawParameterValue("OSC2FMDEPTH")->load();
            voice->updateOscillator2FrequencyModulation(osc2FmFrequency, osc2FmDepth);

            auto osc3FunctionType = static_cast<OscillatorFunctionType>(audioProcessorValueTreeState.getRawParameterValue("OSC3FUNCTION")->load());
            voice->updateOscillator3FunctionType(osc3FunctionType);

            const float osc3FmFrequency = audioProcessorValueTreeState.getRawParameterValue("OSC3FMFREQ")->load();
            const float osc3FmDepth = audioProcessorValueTreeState.getRawParameterValue("OSC3FMDEPTH")->load();
            voice->updateOscillator3FrequencyModulation(osc3FmFrequency, osc3FmDepth);

            const float attack = audioProcessorValueTreeState.getRawParameterValue("AMPATTACK")->load();
            const float decay = audioProcessorValueTreeState.getRawParameterValue("AMPDECAY")->load();
            const float sustain = audioProcessorValueTreeState.getRawParameterValue("AMPSUSTAIN")->load();
            const float release = audioProcessorValueTreeState.getRawParameterValue("AMPRELEASE")->load();
            voice->updateAmplitudeAdsr(attack, decay, sustain, release);

            const float modAttack = audioProcessorValueTreeState.getRawParameterValue("MODATTACK")->load();
            const float modDecay = audioProcessorValueTreeState.getRawParameterValue("MODDECAY")->load();
            const float modSustain = audioProcessorValueTreeState.getRawParameterValue("MODSUSTAIN")->load();
            const float modRelease = audioProcessorValueTreeState.getRawParameterValue("MODRELEASE")->load();
            voice->updateModulationAdsr(modAttack, modDecay, modSustain, modRelease);

            auto filter1Type = static_cast<juce::dsp::StateVariableTPTFilterType>(audioProcessorValueTreeState.getRawParameterValue("FILTER1TYPE")->load());
            const float filter1Cutoff = audioProcessorValueTreeState.getRawParameterValue("FILTER1CUTOFF")->load();
            const float filter1Resonance = audioProcessorValueTreeState.getRawParameterValue("FILTER1RES")->load();
            voice->updateFilter1(filter1Type, filter1Cutoff, filter1Resonance);

            auto filter2Type = static_cast<juce::dsp::StateVariableTPTFilterType>(audioProcessorValueTreeState.getRawParameterValue("FILTER2TYPE")->load());
            const float filter2Cutoff = audioProcessorValueTreeState.getRawParameterValue("FILTER2CUTOFF")->load();
            const float filter2Resonance = audioProcessorValueTreeState.getRawParameterValue("FILTER2RES")->load();
            voice->updateFilter2(filter2Type, filter2Cutoff, filter2Resonance);
        }
    }

    renderNextBlock(audioBuffer, midiBuffer, 0, audioBuffer.getNumSamples());
}