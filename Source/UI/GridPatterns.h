using GridPattern = std::array<std::array<bool , 6> , 3>;

//==============================================================================
//Patterns for OSC


//Sine Pattern
inline const GridPattern sinePattern = {{
        { false, true, true, false, false, false },
        { true, false, false, true, false, false },
        { false, false, false, false, true, true }
}};

//Square
inline const GridPattern squarePattern = {{
        { true, true, true, false, true, true },
        { true, false, true, false, true, false },
        { true, false, true, true, true, false }
}};


//Triangle
inline const GridPattern trianglePattern = {{
        { false, false, true, false, false, false },
        { false, true, false, true, false, true },
        { true, false, false, false, true, false }
}};

//==============================================================================

//Patterns for filter

//lowpass
inline const GridPattern lowpassPattern = {{
        { false, false, true, true, true, true },
        { false, true, false, false, false, false },
        { true, false, false, false, false, false }
    }};


//highpass
inline const GridPattern highpassPattern = {{
        { true, true, true, true, false, false },
        { false, false, false, false, true, false },
        { false, false, false, false, false, true }
    }};


//bandpass
inline const GridPattern bandpassPattern = {{
        { false, false, true, true, false, false },
        { false, true, false, false, true, false },
        { true, false, false, false, false, true }
    }};


//bandreject
inline const GridPattern bandrejectPattern = {{
        { true, false, false, false, false, true },
        { false, true, false, false, true, false },
        { false, false, true, true, false, false }
    }};

