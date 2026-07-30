#include "SynthVoice.h"

SynthVoice::SynthVoice(std::array<NoteParams, 128>* ParamsArray) : paramsArray(ParamsArray){}



void SynthVoice::prepare(const juce::dsp::ProcessSpec& spec){
    
    setCurrentPlaybackSampleRate(spec.sampleRate);
    
    OSC.prepare(spec);
    OSC.initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;}); //Initalised as a square wave , implementing OSC switching for individual voicing
    
    ADSR.setSampleRate(spec.sampleRate);
    
    //For the number of channels we need a version of the effect for each of the channels
    
    privateBuffer.setSize((int)spec.numChannels , (int)spec.maximumBlockSize);
    privateBuffer.clear();
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
    privateBuffer.clear();
    
    juce::dsp::AudioBlock<float> block(privateBuffer);
    auto subBlock = block.getSubBlock(0, numSamples);
    juce::dsp::ProcessContextReplacing<float> context(subBlock);
    
    OSC.process(context);
    ADSR.applyEnvelopeToBuffer(privateBuffer, 0, numSamples);
    
    //Applying effects to the note 
    
}

void SynthVoice::pitchWheelMoved(int){}

void SynthVoice::controllerMoved(int, int){}

void SynthVoice::updateValues(int midiNoteNumber){
    
    auto& data = paramsArray->at((size_t)midiNoteNumber);
    
}
