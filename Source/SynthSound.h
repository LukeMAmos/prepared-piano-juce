#pragma once
#include <juce_audio_basics/juce_audio_basics.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    
    bool appliesToNote(int midiNoteNumber) override{
        
        if(midiNoteNumber > -1) return true;
        
        return false
    }
    
    bool appliesToChannel(int midiChannel) override{
        
        if(midiChannel > -1) return true;
        
        return false;
    }
    
private:
    
    
};
