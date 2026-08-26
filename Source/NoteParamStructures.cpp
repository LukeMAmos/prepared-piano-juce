#include "NoteParamStructures.h"


namespace NoteParamSerial {

std::unique_ptr<juce::XmlElement> createStaticXml(const std::array<NoteParams, numMidiNotes>& params){
    
    auto root = std::make_unique<juce::XmlElement>("PARAMS");
    
    for(size_t i = 0 ; i < params.size() ; i++){
        
        
        
    }
    
    
}

void restoreStateFromXml(const juce::XmlElement& xml, std::array<NoteParams, numMidiNotes>& params){
    
    int i = 0 ;
    
    for(auto* noteElement : xml.getChildWithTagNameIterator("NOTE")){
        
        
        
        
    }
    
    
    
}

}
