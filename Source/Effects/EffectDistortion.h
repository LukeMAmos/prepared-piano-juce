class SoftDistortion{
    
public:
    
    void prepare(double sampleRateIn);
    
    void setParameters(float inputGainIn , float outputGainIn){
        
        inputGain = inputGainIn;
        outputGain = outputGainIn;
    }
    
    float process(float input){
        
        //Take the input multiply by the gain , if its over 1 set it to 1 , if its under minus 1 set it to -1
        
        input *= inputGain;
        
        if(input > 1.0f )
            input = 1.0f;
        else if(input < -1.0f)
            input = -1.0f;
        
        //Shape the rest of the signal
        //apply the output gain and return the value
        
        input = std::sin(0.5f * (float)M_PI * input);
        
        return (input * outputGain);
    }

private:
    
    float inputGain;
    float outputGain;
    
};
