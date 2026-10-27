#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    /**
     * Returns true if this sound should be played when a given midi note is pressed.
     * The Synthesiser will use this information when deciding which sounds to trigger for a given note.
    */
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }

    /**
     * Returns true if the sound should be triggered by midi events on a given channel.
     * The Synthesiser will use this information when deciding which sounds to trigger for a given note.
    */
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
};
