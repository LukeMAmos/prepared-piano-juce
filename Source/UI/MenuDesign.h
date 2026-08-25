
//Oscillator menu design for selecting the oscillator type

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class OscMenu : public juce::ComboBox{
    
    OscMenu();
    void paint(juce::Graphics& g) override;
    
    void mouseDown(const MouseEvent&) override;
    
};
