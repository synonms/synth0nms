#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"

//==============================================================================
Synth0nmsAudioProcessor::Synth0nmsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                      #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_WantsMidiInput
                      .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                      #if ! JucePlugin_ProducesMidiOutput
                      .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                      #endif
                      #endif
                      )
    , audioProcessorValueTreeState (*this, nullptr, "Parameters", createParams())
#endif
{
    m_synth.addSound(new SynthSound());
    m_synth.addVoice(new SynthVoice());
}

Synth0nmsAudioProcessor::~Synth0nmsAudioProcessor() = default;

//==============================================================================
const juce::String Synth0nmsAudioProcessor::getName() const
{
    return "synth0nms";
}

bool Synth0nmsAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Synth0nmsAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Synth0nmsAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double Synth0nmsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth0nmsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't call the getNumPrograms() method, so this should be a supported fallback
}

int Synth0nmsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth0nmsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Synth0nmsAudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth0nmsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

void Synth0nmsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    m_synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < m_synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(m_synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    juce::dsp::ProcessSpec processSpec {};
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = getTotalNumOutputChannels();
    m_filter.prepareToPlay(processSpec);
}

void Synth0nmsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth0nmsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts do not support stereo layouts, so when a plugin has to support stereo,
    // it might be necessary to change this implementation to handle that.
    
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This means that we support the channel layout with 1 input and 2 outputs (stereo)
    if (layouts.getMainInputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainInputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
  #endif
}
#endif

void Synth0nmsAudioProcessor::processBlock (juce::AudioBuffer<float>& audioBuffer, juce::MidiBuffer& midiBuffer)
{
    juce::ScopedNoDenormals noDenormals;

    for (int i = 0; i < audioBuffer.getNumChannels(); ++i) {
        audioBuffer.clear(i, 0, audioBuffer.getNumSamples());
    }

    // Inject virtual keyboard events into the MIDI buffer
    keyboardState.processNextMidiBuffer (midiBuffer, 0, audioBuffer.getNumSamples(), true);

//    m_waveTableSynth.processBlock (audioBuffer, midiBuffer);

    // Update parameters
    for (int i = 0; i < m_synth.getNumVoices(); ++i) {
        if (auto* voice = dynamic_cast<SynthVoice*>(m_synth.getVoice(i)))
        {
            const float attack = audioProcessorValueTreeState.getRawParameterValue("ATTACK")->load();
            const float decay = audioProcessorValueTreeState.getRawParameterValue("DECAY")->load();
            const float sustain = audioProcessorValueTreeState.getRawParameterValue("SUSTAIN")->load();
            const float release = audioProcessorValueTreeState.getRawParameterValue("RELEASE")->load();
            voice->updateAdsr(attack, decay, sustain, release);

            auto osc1FunctionType = static_cast<OscillatorFunctionType>(audioProcessorValueTreeState.getRawParameterValue("OSC1FUNCTION")->load());
            voice->updateFunctionType(osc1FunctionType);

            const float fmFrequency = audioProcessorValueTreeState.getRawParameterValue("OSC1FMFREQ")->load();
            const float fmDepth = audioProcessorValueTreeState.getRawParameterValue("OSC1FMDEPTH")->load();
            voice->updateFrequencyModulation(fmFrequency, fmDepth);
        }
    }

    m_synth.renderNextBlock(audioBuffer, midiBuffer, 0, audioBuffer.getNumSamples());

    // Apply filter
    auto filterType = static_cast<juce::dsp::StateVariableTPTFilterType>(audioProcessorValueTreeState.getRawParameterValue("FILTERTYPE")->load());
    const float cutoff = audioProcessorValueTreeState.getRawParameterValue("FILTERCUTOFF")->load();
    const float resonance = audioProcessorValueTreeState.getRawParameterValue("FILTERRES")->load();
    m_filter.updateParameters(filterType, cutoff, resonance);
    m_filter.renderNextBlock(audioBuffer, midiBuffer, 0, audioBuffer.getNumSamples());
}

//==============================================================================
bool Synth0nmsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Synth0nmsAudioProcessor::createEditor()
{
    return new Synth0nmsAudioProcessorEditor (*this);
}

//==============================================================================
void Synth0nmsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the MemoryBlock.
    // When you load them back in the createEditor() method, use it to restore 
    // the state of your parameters. Make sure to also check that you're actually
    // using the right version number when loading.
}

void Synth0nmsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from the MemoryBlock.
    // When you save them in getStateInformation(), use it to restore 
    // the state of your parameters. Make sure to also check that you're actually
    // using the right version number when saving.
}

juce::AudioProcessorValueTreeState::ParameterLayout Synth0nmsAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;

    // ADSR
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f }, 0.1f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f }, 1.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f }, 0.4f ));

    // Oscillator options
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1FUNCTION", "Oscillator 1 Function", juce::StringArray { "Sine", "Saw", "Square" }, 0));
    // Frequency modulation
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "FM Frequency", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 5.0f ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "FM Depth", juce::NormalisableRange<float> { 0.0f, 1000.0f, 0.01f, 0.3f }, 500.0f ));

    // Filter options
    parameters.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type", juce::StringArray { "lowpass", "bandpass", "highpass" }, 0));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff", juce::NormalisableRange<float> { 20.0f, 20000.0f, 0.1f, 0.6f }, 0 ));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRES", "Filter Resonance", juce::NormalisableRange<float> { 1.0f, 10.0f, 0.1f }, 1.0f ));

    return { parameters.begin(), parameters.end() };
}

//==============================================================================
// Global function required by the JUCE build
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new Synth0nmsAudioProcessor();
}