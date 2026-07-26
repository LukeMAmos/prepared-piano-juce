#include "SynthVoice.h"

SynthVoice::SynthVoice(std::array<NoteParams, 128>* ParamsArray) : paramsArray(ParamsArray){}

void SynthVoice::prepare(const juce::dsp::ProcessSpec& spec){
    
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound){
    
}
    
void SynthVoice::startNote(int midiNoteNumber , float velocity , juce::SynthesiserSound* sound , int currentPitchWheelPosition){
    
}

void SynthVoice::stopNote(float velocity , bool allowTailOff){
    
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer , int startSample , int numSamples){
    
}

void SynthVoice::pitchWheelMoved(int newValue){
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newValue){
    
}
