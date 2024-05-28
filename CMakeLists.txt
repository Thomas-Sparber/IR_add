cmake_minimum_required (VERSION 3.12)

project ("IR_add" VERSION 1.0.0
                     DESCRIPTION "A simple Tool to add impulse response to an audio file"
                     HOMEPAGE_URL "https://github.com/Thomas-Sparber/IR_add")

file(GLOB_RECURSE SOURCES Source/*.cpp Source*.h)
file(GLOB_RECURSE NAM_SOURCES Dependencies/AudioDSPTools/dsp/*.cpp Dependencies/AudioDSPTools/dsp/*.h)

include_directories(${PROJECT_NAME} Dependencies/AudioFile)
include_directories(${PROJECT_NAME} Dependencies/AudioDSPTools/Dependencies/eigen)
include_directories(${PROJECT_NAME} Dependencies/AudioDSPTools/Dependencies/nlohmann)
include_directories(${PROJECT_NAME} Dependencies/AudioDSPTools)

add_executable (${PROJECT_NAME} ${SOURCES} ${NAM_SOURCES})
target_compile_features (${PROJECT_NAME} INTERFACE cxx_std_17)
target_compile_options(${PROJECT_NAME} PUBLIC -g -O3)
