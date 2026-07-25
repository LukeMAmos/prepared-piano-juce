
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PreparedSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PreparedSynthAudioProcessorEditor (PreparedSynthAudioProcessor&);
    ~PreparedSynthAudioProcessorEditor() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    
private:
    PreparedSynthAudioProcessor& audioProcessor;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PreparedSynthAudioProcessorEditor)
};
