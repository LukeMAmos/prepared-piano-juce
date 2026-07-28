#include "SynthVoice.h"

SynthVoice::SynthVoice(std::array<NoteParams, 128>* ParamsArray) : paramsArray(ParamsArray){}



void SynthVoice::prepare(const juce::dsp::ProcessSpec& spec){
    
    setCurrentPlaybackSampleRate(spec.sampleRate);
    
}

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound){
    
    return true;
}
    
void SynthVoice::startNote(int midiNoteNumber , float velocity , juce::SynthesiserSound* sound , int currentPitchWheelPosition){
    
    //Update values to be used , start the adsr
    updateValues(midiNoteNumber);
    OSC.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    ADSR.noteOn();
}

void SynthVoice::stopNote(float  , bool ){
    
    //Move into release stage , set the tailpending to be true so that the voice is allowed to stay active when the reverb is running
    ADSR.noteOff();
    tailPending = true;
    
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer , int startSample , int numSamples){
    
    juce::ScopedNoDenormals noDenormals;
    
}

void SynthVoice::pitchWheelMoved(int){}

void SynthVoice::controllerMoved(int, int){}

void SynthVoice::updateValues(int midiNoteNumber){
    
    
    
}
