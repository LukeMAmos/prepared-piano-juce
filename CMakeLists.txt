cmake_minimum_required(VERSION 3.22)
project(PreparedSynth VERSION 0.0.1)

include(FetchContent)

FetchContent_Declare(
	JUCE
	GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
	GIT_TAG 8.0.12
)

FetchContent_MakeAvailable(JUCE)

juce_add_plugin(PreparedSynth
	COMPANY_NAME                "Luke Amos"
    BUNDLE_ID                   com.lukeamos.preparedsynth
    IS_SYNTH                    TRUE 
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           FALSE
    IS_MIDI_EFFECT              FALSE
    COPY_PLUGIN_AFTER_BUILD     TRUE
    PLUGIN_MANUFACTURER_CODE    Lkam
    PLUGIN_CODE                 Prsy
    FORMATS                     AU VST3 Standalone
    PRODUCT_NAME                "Prepared Synth"
)

juce_generate_juce_header(PreparedSynth)


target_sources(PreparedSynth
    PRIVATE
		Source/PluginProcessor.cpp
        Source/PluginProcessor.h
        Source/PluginEditor.cpp
        Source/PluginEditor.h
        Source/SynthSound.h
        Source/SynthVoice.h
        Source/SynthVoice.cpp
)

source_group("Source" FILES
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/SynthSound.h
    Source/SynthVoice.h
    Source/SynthVoice.cpp
)

target_compile_definitions(PreparedSynth
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(PreparedSynth
    PRIVATE
        juce::juce_audio_utils
	juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)