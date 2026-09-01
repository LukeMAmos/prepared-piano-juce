#include <juce_gui_basics/juce_gui_basics.h>
 
class dottSlider : public juce::Slider{

public:
    
    dottSlider();
    ~dottSlider() override ;
    
    //Override Paint function
    void paint(juce::Graphics &g) override;
    
private:
    
};
