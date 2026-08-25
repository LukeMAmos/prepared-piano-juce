#include "MenuDesign.h"


GridIconMenu::GridIconMenu(){
    
    //initaliser
    

}

void GridIconMenu::paint(juce::Graphics &g){
    
    //Draw evenly spaced circles based on the reduced bounds of the component and set the fill of the circle based on the current pattern being used
    auto bounds = getBounds().reduced(5);
    
    //Get number of rows and columns
    size_t nRows = currentPattern.size();
    size_t nColumns = currentPattern[0].size();
    
    //Get the spacing for drawing the circles
    auto rSpacing = bounds.getHeight() / nColumns ;
    auto nSpacing = bounds.getWidth() / nRows;
    
    //loop through the rows and columns at each point check whether to fill or no fill and then draw
    for(size_t r = 0; r < nRows ; r++ ){
        
        for(size_t c = 0; c < nRows ; c++){
            
            if(currentPattern[r][c]){
                //current position is on and should be drawn with fill
                
            }else{
                //current position is off state and should be drawn with no fill 
                
            }
            
            
        }
    }
    
}

void GridIconMenu::mouseDown(const juce::MouseEvent &){
    
    //get the total number of elements
    int numItems = getNumItems();
    int currentIndex = getSelectedItemIndex();
    //loop around the number of elements
    int nextIndex = currentIndex+1 % numItems;
    //set the new selected Index
    setSelectedItemIndex(nextIndex);
    
    //set the current pattern to be used
    currentPattern = storedPatterns[(size_t)nextIndex];
}

void GridIconMenu::setGridPatterns(std::vector<GridPattern> patterns){
    //take the patterns and store them inside our vector for use when drawing the grid circles
    storedPatterns = std::move(patterns);
}
