#pragma once
#include "SynthSound.h"
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_dsp/juce_dsp.h>
#include "NoteParamStructures.h"
#include "Effects/MultichannelEffects.h"



class SynthVoice : public juce::SynthesiserVoice {
    
public:
    
    SynthVoice(std::array<NoteParams, 12>* ParamsArray);
    
    void prepare(const juce::dsp::ProcessSpec& spec);
    
    bool canPlaySound(juce::SynthesiserSound* sound) override;
        
    void startNote(int midiNoteNumber , float velocity , juce::SynthesiserSound* sound , int currentPitchWheelPosition) override;
    
    void stopNote(float velocity , bool allowTailOff) override;
    
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer , int startSample , int numSamples) override;
    
    void pitchWheelMoved(int newValue) override;
    
    void controllerMoved(int controllerNumber, int newValue) override;
    
    bool isVoiceActive() const override{
        
        return ADSR.isActive() || tailPending;
    }
    
    //Method for checking the level of the voice when it is currently reverberating , when the level drops below the threshhold we then release the voice
    bool isSilent(){
        
        float leftDb = juce::Decibels::gainToDecibels(privateBuffer.getRMSLevel(0, 0, privateBuffer.getNumSamples()));
        float rightDb = juce::Decibels::gainToDecibels(privateBuffer.getRMSLevel(1, 0, privateBuffer.getNumSamples()));
        
        if( leftDb < silenceThreshhold && rightDb < silenceThreshhold){
            tailPending = false;
            clearCurrentNote(); 
            return true;
        }
        
        return false;
    }
    
    void updateValues(int midiNoteNumber);
    
    void updateOscillator(OSCType type);
    
private:
    
    //OSC and ADSR
    juce::dsp::Oscillator<float> OSC;
    juce::ADSR ADSR;
    juce::ADSR::Parameters adsrParams; 
    int noteParamPosition = 0; 
    juce::AudioBuffer<float> privateBuffer;
    
    static constexpr float silenceThreshhold = -60.0f;
    
    std::array<NoteParams , 12>* paramsArray;
    
    //Allowing the Reverb to tail off , tailPending states if the voice is currently ringing the reverb , and the adsr has moved into release stage
    bool tailPending;
    
    //Voice Effects, multichannel voice effects , each channel needs its own effect
    MultichannelEffect<SoftDistortion> softDistortion;
    MultichannelEffect<SchroReverb> reverb;
    MultichannelEffect<BiquadFilter> filter;
    MultichannelEffect<Delay> delay; 
};
