#include "PluginProcessor.h"
#include "PluginEditor.h"

PreparedSynthAudioProcessor::PreparedSynthAudioProcessor() : AudioProcessor(BusesProperties().withOutput("Output" , juce::AudioChannelSet::stereo() , true ))
{
    
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
    
    
    
}

void PreparedSynthAudioProcessor::releaseResources(){
    
    
}

bool PreparedSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
    
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo() ;
}


void PreparedSynthAudioProcessor::processBlock(juce::AudioBuffer<float> & buffer , juce::MidiBuffer & midiMessages){
    
    //Process Audio
    
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
