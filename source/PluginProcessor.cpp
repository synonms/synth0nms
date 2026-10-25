#include "PluginProcessor.h"
#include "PluginEditor.h"

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
#endif
{
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
    m_waveTableSynth.prepareToPlay(sampleRate, samplesPerBlock);
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

void Synth0nmsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    for (auto i = 0; i < buffer.getNumChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    m_waveTableSynth.processBlock (buffer, midiMessages);
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

//==============================================================================
// Global function required by the JUCE build
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter ()
{
    return new Synth0nmsAudioProcessor();
}