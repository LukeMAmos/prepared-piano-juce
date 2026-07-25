
enum OSCType{

    Sine,
    Square,
    Triangle
};

enum FilterTypeBiquad{
    
    lowpass,
    highpass,
    bandpass,
    bandreject
};

struct NoteParams{
    
    float attack = 0.1f;
    float decay = 0.1f;
    float release = 0.1f;
    float sustain = 1.0f;
    
    std::atomic<FilterTypeBiquad> filterType{FilterTypeBiquad::lowpass};
    std::atomic<float> filterResonance{0.5f};
    std::atomic<float> cutoffFrequency{2500.0f};
    
    std::atomic<float> coe{0.5f};
    std::atomic<float> roomSize{0.5f};
    std::atomic<float> wetLevel{0.2f};
    
    std::atomic<float> inputDistortion{1.0f};
    std::atomic<float> outputDistortion{1.0f};
    
    std::atomic<OSCType> oscType{OSCType::Square};
    
    std::atomic<float> delayedSampleLevel{1.0f};
    std::atomic<float> delayMs{1.0f};
    
};
