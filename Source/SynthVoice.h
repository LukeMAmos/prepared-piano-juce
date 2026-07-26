#pragma once
#include "SynthSound.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>
#include "NoteParamStructures.h"


class SynthVoice : public juce::SynthesiserVoice {
    
public:
    
    SynthVoice(std::array<NoteParams, 128>* paramsArray);
    
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
    
    //Method for checking the level of the voice when it is currently reverberating , when the level drops below the threshhold we then release the voice
    bool isSilent(){
        
        return {};
    }
    
private:
    
    //OSC and ADSR
    juce::dsp::Oscillator<float> OSC;
    juce::ADSR ADSR;
    
    static constexpr float silenceThreshhold = -60.0f;
    
    std::array<NoteParams , 128 >* paramsArray;
    
    //Allowing the Reverb to tail off , RingingReverb states if the voice is currently ringing the reverb
    bool ringingReverb;
    
    
    //Voice Effects 
    
    
};
