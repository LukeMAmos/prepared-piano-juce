#include "MenuDesign.h"


GridIconMenu::GridIconMenu(){
    
    //initaliser

}
GridIconMenu::~GridIconMenu(){
    
    setLookAndFeel(nullptr); 
    
}
void GridIconMenu::paint(juce::Graphics &g){
    
    setColour(ComboBox::textColourId, juce::Colours::transparentBlack); 
    
    //Draw evenly spaced circles based on the reduced bounds of the component and set the fill of the circle based on the current pattern being used
    auto bounds = getLocalBounds().reduced(5);
    
    auto selectedIndex = getSelectedItemIndex();
    if (selectedIndex < 0 || (size_t)selectedIndex > storedPatterns.size())
        return;
    auto& currentPattern = storedPatterns[(size_t) selectedIndex];
    
    //Get number of rows and columns
    size_t nRows = currentPattern.size();
    size_t nColumns = currentPattern[0].size();
    
    //Get the spacing for drawing the circles
    auto rSpacing = (float)bounds.getHeight() / nRows ;
    auto cSpacing = (float)bounds.getWidth() / nColumns;
    
    float circleSize = (float)(std::min(rSpacing , cSpacing) * 0.8);
    float lineThickness = 2.0f;
    
    //loop through the rows and columns at each point check whether to fill or no fill and then draw
    for(size_t r = 0; r < nRows ; r++ ){
        
        for(size_t c = 0; c < nColumns ; c++){
            
            //get the next position using rectangle bounding box
            juce::Rectangle<float> area;
            float centreX = bounds.getX() + (c * cSpacing) + (cSpacing / 2.0f);
            float centreY = bounds.getY() + (r * rSpacing) + (rSpacing / 2.0f);
            area.setCentre(centreX, centreY);
            area.setSize(circleSize, circleSize);
            
            //conditional drawing 
            if(currentPattern[r][c]){
                //current position is on and should be drawn with fill
                g.fillEllipse(area);
                
            }else{
                //current position is off state and should be drawn with no fill 
                g.drawEllipse(area, lineThickness);
                
            }
        }
    }
    
}

void GridIconMenu::mouseDown(const juce::MouseEvent &){
    
    //get the total number of elements
    int numItems = getNumItems();
    int currentIndex = getSelectedItemIndex();
    //loop around the number of elements
    int nextIndex = (currentIndex+1) % numItems;
    //set the new selected Index
    setSelectedItemIndex(nextIndex);
}

void GridIconMenu::setGridPatterns(std::vector<GridPattern> patterns){
    //take the patterns and store them inside our vector for use when drawing the grid circles
    storedPatterns = std::move(patterns);
}

