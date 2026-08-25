#include "PluginProcessor.h"
#include "PluginEditor.h"

PreparedSynthAudioProcessor::PreparedSynthAudioProcessor() : AudioProcessor(BusesProperties().withOutput("Output" , juce::AudioChannelSet::stereo() , true ))
{
    for(int i = 0; i < numVoices ; i++)
        synth.addVoice(new SynthVoice(&paramsArray));
    
    synth.addSound(new SynthSound());
}

PreparedSynthAudioProcessor::~PreparedSynthAudioProcessor()
{
    
}

bool PreparedSynthAudioProcessor::acceptsMidi() const {return true;}

bool PreparedSynthAudioProcessor::producesMidi() const {return false;}

bool PreparedSynthAudioProcessor::isMidiEffect()const { return false;}

double PreparedSynthAudioProcessor::getTailLengthSeconds() const {
    return 0.0f;
}



void PreparedSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock){
    
    juce::dsp::ProcessSpec processSpec;
    processSpec.sampleRate = sampleRate;
    processSpec.numChannels = 2;
    processSpec.maximumBlockSize = (uint32)samplesPerBlock;
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for(int i = 0; i < numVoices ; i++){
        
        auto voice = static_cast<SynthVoice*>(synth.getVoice(i));
        
        if(voice != nullptr)
            voice->prepare(processSpec);
    }
    
    
}

void PreparedSynthAudioProcessor::releaseResources(){
    
    
}

bool PreparedSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo() ;
}


void PreparedSynthAudioProcessor::processBlock(juce::AudioBuffer<float> & buffer , juce::MidiBuffer & midiMessages){
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //Process Audio
    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    //Pass the the midi messages through into the synth
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

const juce::String PreparedSynthAudioProcessor::getName() const {
    
    return "Prepared Synth";
}


int PreparedSynthAudioProcessor::getNumPrograms(){
    return 1;
}

int PreparedSynthAudioProcessor::getCurrentProgram(){
    return 0;
}

void PreparedSynthAudioProcessor::setCurrentProgram (int){
}

const juce::String PreparedSynthAudioProcessor::getProgramName (int){
    return {};
}

void PreparedSynthAudioProcessor::changeProgramName (int, const juce::String&){
}



void PreparedSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData){
    
    
}

void PreparedSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes){
    
    
    
}


juce::AudioProcessorEditor* PreparedSynthAudioProcessor::createEditor()
{
    return new PreparedSynthAudioProcessorEditor (*this);
}

bool PreparedSynthAudioProcessor::hasEditor() const {
    return true;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PreparedSynthAudioProcessor();
}
