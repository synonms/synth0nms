cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET "synth0nms")
set(CURRENT_VERSION "0.0.1")
set(PRODUCT_NAME "synth0nms")
set(COMPANY_NAME "Candidate Studio")
set(BUNDLE_ID "studio.candidate.synth0nms")
set(FORMATS Standalone AU VST3)

project(${TARGET} VERSION ${CURRENT_VERSION})

# Add JUCE as a subdirectory
add_subdirectory(modules/JUCE)

# Add the JUCE plugin - this creates preprocessor macros e.g. JucePlugin_Name
juce_add_plugin(synth0nms
    COMPANY_NAME ${COMPANY_NAME}
    PRODUCT_NAME ${PRODUCT_NAME}
    VERSION ${CURRENT_VERSION}
    BUNDLE_ID ${BUNDLE_ID}
    FORMATS ${FORMATS}
    IS_SYNTH TRUE                          # Tells hosts this is an instrument, not an effect
    NEEDS_MIDI_INPUT TRUE                  # Enables MIDI input for the synth
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
)

# Add all source files
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.h"
)

target_sources(synth0nms PRIVATE ${SOURCE_FILES})

# Link standard JUCE modules 
target_link_libraries(synth0nms PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
)

# Include JUCE modules for CLion IDE indexing
target_include_directories(synth0nms PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/JUCE/modules
)