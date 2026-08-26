
//Oscillator menu design for selecting the oscillator type

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>


using GridPattern = std::array<std::array<bool , 6> , 3>;

class GridIconMenu : public juce::ComboBox, public juce::LookAndFeel_V4{
    
public:
    GridIconMenu();
    ~GridIconMenu() override;
    //Override the paint and mouse down functions, mouse down functionality should loop through elements with each press
    void paint(juce::Graphics& g) override;
    void mouseDown(const juce::MouseEvent&) override;
    
    //Functions for passing through the grid arrays
    void setGridPatterns(std::vector<GridPattern> patterns);
    
    //remove the text drawing capabilities 
    void drawComboBox(juce::Graphics&, int, int, bool, int, int, int, int, juce::ComboBox&) override;
    
    void positionComboBoxText(juce::ComboBox&, juce::Label& labelToPosition) override;
    
private:
    
    std::vector<GridPattern> storedPatterns;
    GridPattern currentPattern;
    
    //initalising the number of columns and rows
    const int numCol = 3;
    const int numRow = 6;
    
};
