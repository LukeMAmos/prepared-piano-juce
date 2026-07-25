#pragma once
#include "SynthSound.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>

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
    
    
private:
    
    juce::dsp::Oscillator<float> OSC;
    juce::ADSR ADSR;
    
    
};
