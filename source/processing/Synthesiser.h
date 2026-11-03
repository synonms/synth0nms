#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class Synthesiser : public juce::Synthesiser
{
public:
    Synthesiser();

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    void initialise (double sampleRate, int samplesPerBlock, int numOutputChannels);
    void processBlock (juce::AudioBuffer<float>& audioBuffer, const juce::MidiBuffer& midiBuffer, const juce::AudioProcessorValueTreeState& audioProcessorValueTreeState);

private:

};

