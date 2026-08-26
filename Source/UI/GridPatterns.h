using GridPattern = std::array<std::array<bool , 6> , 3>;

//==============================================================================
//Patterns for OSC

//Sine Pattern
GridPattern sinePattern = {{
        { false, true, true, false, false, false },
        { true, false, false, true, false, false },
        { false, false, false, false, true, true }
}};

//Square
GridPattern squarePattern = {{
        { true, true, true, false, true, true },
        { true, false, true, false, true, false },
        { true, false, true, true, true, false }
}};


//Triangle
GridPattern trianglePattern = {{
        { false, false, true, false, false, false },
        { false, true, false, true, false, true },
        { true, false, false, false, true, false }
}};

//==============================================================================

//Patterns for filter

//lowpass
GridPattern lowpassPattern = {{
        { false, false, true, true, true, true },
        { false, true, false, false, false, false },
        { true, false, false, false, false, false }
    }};


//highpass
GridPattern highpassPattern = {{
        { true, true, true, true, false, false },
        { false, false, false, false, true, false },
        { false, false, false, false, false, true }
    }};


//bandpass
GridPattern bandpassPattern = {{
        { false, false, true, true, false, false },
        { false, true, false, false, true, false },
        { true, false, false, false, false, true }
    }};


//bandreject
GridPattern bandrejectPattern = {{
        { true, false, false, false, false, true },
        { false, true, false, false, true, false },
        { false, false, true, true, false, false }
    }};

