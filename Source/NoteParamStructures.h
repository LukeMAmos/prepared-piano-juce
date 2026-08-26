#pragma once
#include <juce_core/juce_core.h>

#define numMidiNotes 12

enum OSCType{

    Sine,
    Square,
    Triangle
};

enum FilterTypeBiquad{
    
    lowpass,
    highpass,
    bandpass,
    bandreject
};

struct NoteParams{
    
    std::atomic<float> attack = 0.1f;
    std::atomic<float> decay = 0.1f;
    std::atomic<float> release = 0.1f;
    std::atomic<float> sustain = 1.0f;
    
    std::atomic<FilterTypeBiquad> filterType{FilterTypeBiquad::lowpass};
    std::atomic<float> filterResonance{0.5f};
    std::atomic<float> cutoffFrequency{2500.0f};
    
    std::atomic<float> coe{0.5f};
    std::atomic<float> roomSize{0.5f};
    std::atomic<float> wetLevel{0.2f};
    
    std::atomic<float> inputDistortion{1.0f};
    std::atomic<float> outputDistortion{1.0f};
    
    std::atomic<OSCType> oscType{OSCType::Square};
    
    std::atomic<float> delayedSampleLevel{1.0f};
    std::atomic<float> delayMs{1.0f};
    
};

//Namespace to hold the functiosn for creating the Xml and restoring the state of the 
namespace NoteParamSerial {

    std::unique_ptr<juce::XmlElement> createStaticXml(const std::array<NoteParams, numMidiNotes>& params);
    void restoreStateFromXml(const juce::XmlElement& xml, std::array<NoteParams, numMidiNotes>& params);

}
