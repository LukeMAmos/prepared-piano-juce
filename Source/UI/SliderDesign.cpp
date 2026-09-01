#include "SliderDesign.h"

dottSlider::dottSlider(){
    
    setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    setRotaryParameters(juce::MathConstants<float>::pi * 1.2f, juce::MathConstants<float>::pi * 2.8f, true);
    
}

dottSlider::~dottSlider(){
    
    
}

void dottSlider::paint(juce::Graphics &g){
    
    auto wholeBounds = getLocalBounds();
    wholeBounds.reduced(8); 
    int x = wholeBounds.getX();
    int y = wholeBounds.getY();
    int width = wholeBounds.getWidth();
    int height = wholeBounds.getHeight();
    // getValue returns the actual value of the slider, need to normalise the value between 0 and 1
    float sliderPos = (float)((getValue() - getMinimum()) / (getMaximum() - getMinimum()));
    
    float rotaryStartAngle = getRotaryParameters().startAngleRadians;
    float rotaryEndAngle = getRotaryParameters().endAngleRadians;
    
    //Using same method as previous project
    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto angleStep = (rotaryEndAngle - rotaryStartAngle)/10.0f;
    
    auto lineW = juce::jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;
    
    int maxPosition = (int)(sliderPos * 10);
    

    //drawing dots
    for(int i = 0 ; i < 10 ; i++){
        auto dotAngle = rotaryStartAngle + (i * angleStep);
        
        juce::Point<float> dotPoint (bounds.getCentreX() + arcRadius * std::cos (dotAngle - juce::MathConstants<float>::halfPi),
                                     bounds.getCentreY() + arcRadius * std::sin (dotAngle - juce::MathConstants<float>::halfPi));
        
        if(i <= maxPosition){
            g.setColour (juce::Colours::grey.withBrightness(0.2f + sliderPos));
            g.fillEllipse (juce::Rectangle<float> (lineW, lineW).withCentre (dotPoint));
        }else {
            g.setColour (juce::Colours::grey.withBrightness(0.15f));
            g.fillEllipse (juce::Rectangle<float> (lineW, lineW).withCentre (dotPoint));
        }
        
    }

}
