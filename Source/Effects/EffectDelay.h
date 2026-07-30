
//Delay Line used individually as a delay function or used by other effects as a delay block 
class DelayLine{
    
public:
    
    void prepare(double sampleRateIn, float maxDelayMs){
        
        sampleRate = sampleRateIn;
        
        int maxBufferSize = sampleRate * (maxDelayMs / 1000.0f);
        buffer.resize(maxBufferSize, 0);
        writePosition = 0;
        
    }

    void setDelayLine(float ms){
        
        delaySamples = std::min((int)(sampleRate * (ms / 1000.0f)), (int)buffer.size() - 1.0f);
        
    }

    float processSample(float input){
        
        int readPosition = (int)(writePosition - delaySamples + buffer.size()) % buffer.size();
        
        float delayedSample = buffer[readPosition];
        
        buffer[writePosition] = input;
        writePosition = (writePosition + 1.0f ) % buffer.size();
        
        return delayedSample;
    }
    
    float bufferValue(int samplePos){
        
        return buffer[samplePos];
    }
    
private:
    
    std::vector<float> buffer;
    int writePosition;
    int delaySamples;
    double sampleRate;
    
};

//Uses the delay line function with wet/dry implementation
class Delay{

public:
    
    void prepare(double sampleRateIn , float maxDelayMs){
        
        delayLine.prepare(sampleRateIn, maxDelayMs);
        
    }
    
    void setParameters(float delayedSampleLevel , float delayInMs){
        
        delayLine.setDelayLine(delayInMs);
        wetLevel = delayedSampleLevel;
    }
    
    float process(float input){
        
        nextWetOut = delayLine.processSample(input);
        
        return ((nextWetOut * wetLevel) + (input * (1.0f - wetLevel)));
    }


private:
    
    float nextWetOut = 0.0f;
    DelayLine delayLine;
    float wetLevel;
}


