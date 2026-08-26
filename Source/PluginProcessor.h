#pragma once
#include <JuceHeader.h>
#include "SynthVoice.h"
#include "NoteParamStructures.h"


class PreparedSynthAudioProcessor : public juce::AudioProcessor
{
    
public:
    
    PreparedSynthAudioProcessor();
    ~PreparedSynthAudioProcessor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    
    NoteParams& getNoteParams(int noteNumber){
        
        //every type of note shares the same paramter so only 12 notes are saved
        noteNumber = noteNumber % 12; 
        return paramsArray[(size_t)noteNumber];
    }
    
    
    //Changing the stored data values for all 128 notes to the currently selected note value
    void updateAll(int currentPos){
        
        //Update all paramters to the current note selected
        for(decltype(paramsArray.size()) i = 0 ; i < paramsArray.size() ; i++){

            paramsArray[i].attack.store(paramsArray[(size_t)currentPos].attack.load());
            paramsArray[i].decay.store(paramsArray[(size_t)currentPos].decay.load());
            paramsArray[i].release.store(paramsArray[(size_t)currentPos].release.load());
            paramsArray[i].sustain.store(paramsArray[(size_t)currentPos].sustain.load());
            
            paramsArray[i].filterType.store(paramsArray[(size_t)currentPos].filterType.load());
            paramsArray[i].filterResonance.store(paramsArray[(size_t)currentPos].filterResonance.load());
            paramsArray[i].cutoffFrequency.store(paramsArray[(size_t)currentPos].cutoffFrequency.load());
            
            paramsArray[i].coe.store(paramsArray[(size_t)currentPos].coe.load());
            paramsArray[i].roomSize.store(paramsArray[(size_t)currentPos].roomSize.load());
            paramsArray[i].wetLevel.store(paramsArray[(size_t)currentPos].wetLevel.load());
            
            paramsArray[i].inputDistortion.store(paramsArray[(size_t)currentPos].inputDistortion.load());
            paramsArray[i].outputDistortion.store(paramsArray[(size_t)currentPos].outputDistortion.load());
            
            paramsArray[i].oscType.store(paramsArray[(size_t)currentPos].oscType.load());
        }
        
    }
    
    juce::MidiKeyboardState keyboardState;
    
private:
    
    juce::Synthesiser synth;
    const int numVoices = 16;
    
    //Structure to hold data for all the notes
    std::array<NoteParams , numMidiNotes> paramsArray;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreparedSynthAudioProcessor)
};
