
//Oscillator menu design for selecting the oscillator type

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

using GridPattern = std::array<std::array<bool , 6> , 3>;

class OscMenu : public juce::ComboBox{
    
public:
    OscMenu();
    //Override the paint and mouse down functions, mouse down functionality should loop through elements with each press 
    void paint(juce::Graphics& g) override;
    void mouseDown(const MouseEvent&) override;
    
    //Functions for passing through the grid arrays
    void setGridPatterns(std::vector<GridPattern> patterns);
    
private:
    
    std::vector<GridPattern> storedPatterns;
    
};
