#include <juce_gui_basics/juce_gui_basics.h>
 
class dottedRotarySlider : public juce::Slider{

public:
    
    dottedRotarySlider();
    ~dottedRotarySlider() override ;
    
    //Override Paint function
    void paint(juce::Graphics &g) override;
    
private:
    
};
