#pragma once
#include "SynthSound.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>
#include "NoteParamStructures.h"


class SynthVoice : public juce::SynthesiserVoice {
    
public:
    
    SynthVoice();
    
    void prepare(const juce::dsp::ProcessSpec& spec);
    
    bool canPlaySound(juce::SynthesiserSound* sound) override;
        
    void startNote(int midiNoteNumber , float velocity , juce::SynthesiserSound* sound , int currentPitchWheelPosition) override;
    
    void stopNote(float velocity , bool allowTailOff) override;
    
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer , int startSample , int numSamples) override;
    
    void pitchWheelMoved(int newValue) override;
    
    void controllerMoved(int controllerNumber, int newValue) override;
    
    bool isVoiceActive() const override{
        
        return ADSR.isActive() || ringingReverb ;
    }
    
    
private:
    
    //OSC and ADSR
    juce::dsp::Oscillator<float> OSC;
    juce::ADSR ADSR;
    
    
    //Allowing the Reverb to tail off , RingingReverb states if the voice is currently ringing the reverb
    bool ringingReverb;
    
    
    
    
    
};
