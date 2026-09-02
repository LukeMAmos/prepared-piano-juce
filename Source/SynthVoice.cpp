#include "SynthVoice.h"

SynthVoice::SynthVoice(std::array<NoteParams, 12>* ParamsArray) : paramsArray(ParamsArray){}



void SynthVoice::prepare(const juce::dsp::ProcessSpec& spec){
    
    OSC.prepare(spec);
    OSC.initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;}); //Initalised as a square wave , implementing OSC switching for individual voicing
    
    ADSR.setSampleRate(spec.sampleRate);
    
    //For the number of channels we need a version of the effect for each of the channels
    softDistortion.prepare((int)spec.numChannels, spec.sampleRate);
    reverb.prepare((int)spec.numChannels,spec.sampleRate,315.0f);
    filter.prepare((int)spec.numChannels, spec.sampleRate);
    delay.prepare((int)spec.numChannels,spec.sampleRate ,10.0f);
    
    privateBuffer.setSize((int)spec.numChannels , (int)spec.maximumBlockSize);
    privateBuffer.clear();
    
    forceCacheReset(); 
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
    currentMidiNote = midiNoteNumber;
}

void SynthVoice::stopNote(float  , bool ){
    
    //Move into release stage , set the tailpending to be true so that the voice is allowed to stay active when the reverb is running
    ADSR.noteOff();
    tailPending = true;
    
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer , int startSample , int numSamples){
    
    if(isVoiceActive())
        updateValues(currentMidiNote%12);
    
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
            
            float sample = privateBuffer.getSample(ch, s);
            sample = softDistortion.process(ch, sample);
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
    
    
    juce::ADSR::Parameters adsrParams;
    
    auto& data = paramsArray->at(midiNoteNumber); //getting the data at the specific midi note , then using that data to control the effects/ parameters of that voice
    adsrParams.attack  = data.attack;
    adsrParams.decay   = data.decay;
    adsrParams.sustain = data.sustain;
    adsrParams.release = data.release;
    ADSR.setParameters(adsrParams);
    
    float coe = data.coe.load();
    float roomSize = data.roomSize.load();
    float wetAm = data.wetLevel.load();

    float cutoff = data.cutoffFrequency.load();
    float resonance = data.filterResonance.load();
    auto type = data.filterType.load();
    
    float inGainDis = data.inputDistortion.load();
    float outGainDis = data.outputDistortion.load();
    
    float delayedSampleLevel = data.delayedSampleLevel.load();
    float delayInMS = data.delayMs.load();

    //Guard Values if nothing has been updated, implement epsliom if statements
    if(cachedParamState.inputDistortion != inGainDis || cachedParamState.outputDistortion != outGainDis){
        softDistortion.setParameters(inGainDis, outGainDis);
    }
    
    if(coe != cachedParamState.coe || roomSize != cachedParamState.roomSize || wetAm != cachedParamState.wetLevel){
        reverb.setParameters(coe,2500.0f, roomSize, wetAm);
    }
    
    if(cutoff != cachedParamState.cutoffFrequency || resonance != cachedParamState.filterResonance || (int)type != cachedParamState.filterType){
        filter.setParameters(cutoff, resonance, type);
    }
    
    if(delayedSampleLevel != cachedParamState.delayedSampleLevel || delayInMS != cachedParamState.delayMs){
        delay.setParameters(delayedSampleLevel, delayInMS);
    }
    
    if((int)data.oscType != cachedParamState.oscType){
        updateOscillator(data.oscType);
    }
}

void SynthVoice::updateOscillator(OSCType type){
    
    switch (type) {
        case Sine:
            OSC.initialise([](float x){return std::sin(x * 2 * M_PI);}); // type mismatch here
            break;
        case Square:
            OSC.initialise([](float x){return x < 0.0f ? -1.0f : 1.0f;});
            break;
        case Triangle:
            OSC.initialise([](float x){return x < 0.5f ? x * 4 - 1 : -x * 4 + 3 ;});
            break;
        default:
            break;
    }
    
    
}

void SynthVoice::forceCacheReset(){
    //reset the cache each time data is reloaded from XML
    
    cachedParamState.attack = -1.0f;
    cachedParamState.coe = -1.0f;
    cachedParamState.cutoffFrequency = -1.0f;
    cachedParamState.decay = -1.0f;
    cachedParamState.delayMs = -1.0f;
    cachedParamState.delayedSampleLevel = -1.0f;
    cachedParamState.filterResonance = -1.0f;
    cachedParamState.filterType = -1;
    cachedParamState.inputDistortion = -1.0f; ;
    cachedParamState.oscType = -1;
    cachedParamState.outputDistortion = -1.0f;
    cachedParamState.release = -1.0f;
    cachedParamState.roomSize = -1.0f;
    cachedParamState.sustain = -1.0f;
    cachedParamState.wetLevel = -1.0f;
    
}
