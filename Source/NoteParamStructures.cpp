#include "NoteParamStructures.h"


namespace NoteParamSerial {

std::unique_ptr<juce::XmlElement> createStateXml(const std::array<NoteParams, numMidiNotes>& params){
    
    //Create a new XML root
    auto root = std::make_unique<juce::XmlElement>("PARAMS");
    
    for(size_t i = 0 ; i < params.size() ; i++){
        
        //Child element of the root
        auto* noteElement = root->createNewChildElement("NOTE");
        
        //Fill the element with the data
        noteElement->setAttribute("index", static_cast<int>(i));
        
        noteElement->setAttribute("attack",params[i].attack.load());
        noteElement->setAttribute("decay",params[i].decay.load());
        noteElement->setAttribute("release",params[i].release.load());
        noteElement->setAttribute("sustain",params[i].sustain.load());
        
        noteElement->setAttribute("filterType",static_cast<int>(params[i].filterType.load()));
        noteElement->setAttribute("resonance",params[i].filterResonance.load());
        noteElement->setAttribute("cutoff",params[i].cutoffFrequency.load());
        
        noteElement->setAttribute("coe",params[i].coe.load());
        noteElement->setAttribute("roomsize",params[i].roomSize.load());
        noteElement->setAttribute("reverbWetLvl",params[i].wetLevel.load());
        
        noteElement->setAttribute("inputDistortion",params[i].inputDistortion.load());
        noteElement->setAttribute("outputDistortion",params[i].outputDistortion.load());
        
        noteElement->setAttribute("osc",static_cast<int>(params[i].oscType.load()));
        
        noteElement->setAttribute("delayLvl",params[i].delayedSampleLevel.load());
        noteElement->setAttribute("delayMs",params[i].delayMs.load());
        
    }
    
    return root;
}

void restoreStateFromXml(const juce::XmlElement& xml, std::array<NoteParams, numMidiNotes>& params){
    
    //Opposite of createStateXML, get the data from XML and store in the correct location 
    for(auto* noteElement : xml.getChildWithTagNameIterator("NOTE")){
        
        size_t i= static_cast<size_t>(noteElement->getIntAttribute("index"));
        
        params[i].attack.store(static_cast<float>(noteElement->getDoubleAttribute("attack" , 0.1)));
        params[i].decay.store(static_cast<float>(noteElement->getDoubleAttribute("decay" , 0.1)));
        params[i].release.store(static_cast<float>(noteElement->getDoubleAttribute("release" , 0.1)));
        params[i].sustain.store(static_cast<float>(noteElement->getDoubleAttribute("sustain" , 0.1)));
        
        params[i].filterType.store(static_cast<FilterTypeBiquad>(noteElement->getDoubleAttribute("filterType" , 0.1)));
        params[i].filterResonance.store(static_cast<float>(noteElement->getDoubleAttribute("resonance" , 0.1)));
        params[i].cutoffFrequency.store(static_cast<float>(noteElement->getDoubleAttribute("cutoff" , 0.1)));
        
        params[i].coe.store(static_cast<float>(noteElement->getDoubleAttribute("coe" , 0.1)));
        params[i].roomSize.store(static_cast<float>(noteElement->getDoubleAttribute("roomsize" , 0.1)));
        params[i].wetLevel.store(static_cast<float>(noteElement->getDoubleAttribute("reverbWetLvl" , 0.1)));
        
        params[i].inputDistortion.store(static_cast<float>(noteElement->getDoubleAttribute("inputDistortion" , 0.1)));
        params[i].outputDistortion.store(static_cast<float>(noteElement->getDoubleAttribute("outputDistortion" , 0.1)));
        
        params[i].oscType.store(static_cast<OSCType>(noteElement->getDoubleAttribute("osc" , 0.1)));
        
        params[i].delayedSampleLevel.store(static_cast<float>(noteElement->getDoubleAttribute("delayLvl" , 0.1)));
        params[i].delayMs.store(static_cast<float>(noteElement->getDoubleAttribute("delayMs" , 0.1)));
        
    }
    
    
    
}

}
