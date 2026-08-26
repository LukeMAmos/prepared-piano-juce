#include "SynthVoice.h"

SynthVoice::SynthVoice(std::array<NoteParams, 12>* ParamsArray) : paramsArray(ParamsArray){}



void SynthVoice::prepare(const juce::dsp::ProcessSpec& spec){
    
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
    noteParamPosition = midiNoteNumber % 12;
    updateValues(noteParamPosition);
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
    auto subBlock = block.getSubBlock(0, (size_t)numSamples);
    juce::dsp::ProcessContextReplacing<float> context(subBlock);
    
    OSC.process(context);
    ADSR.applyEnvelopeToBuffer(privateBuffer, 0, numSamples);
    
    //Applying effects to the note after the oscillator and the adsr are applied, using multichannel effects
    for(int ch = 0 ; ch < outputBuffer.getNumChannels() ; ch++){
        
        for(int s = 0 ; s < numSamples ; s++){
            float sample = softDistortion.process(ch, sample);
            sample = reverb.process(ch, sample);
            sample = filter.process(ch, sample);
            sample = delay.process(ch, sample);
            privateBuffer.setSample(ch, s, sample);
            
        }
    }
    
    //After applying effects if we are in tail out phase of the note , then check if we have passed the threshold for killing the note
    if(tailPending){
        
        isSilent(); //If isSilent is true then tail pending will be set to false which will allow the note to be released by the synth
    }
    
    for (int ch = 0; ch < outputBuffer.getNumChannels(); ++ch)
        outputBuffer.addFrom(ch, startSample, privateBuffer, ch, 0, numSamples);
}

void SynthVoice::pitchWheelMoved(int){}

void SynthVoice::controllerMoved(int, int){}

void SynthVoice::updateValues(int midiNoteNumber){
    
    auto& data = paramsArray->at((size_t)(midiNoteNumber));
    
}
