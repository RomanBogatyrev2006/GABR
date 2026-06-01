cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrAudio LANGUAGES CXX)


# --Sources and Headers--

# Sources
set(GABR_AUDIO_SOURCES
	audio/audioManager.cpp
)

# Headers
set(GABR_AUDIO_HEADERS 
	audio/audioManager.h
)


# --Library--
add_library(GabrAudio STATIC ${GABR_AUDIO_SOURCES} ${GABR_AUDIO_HEADERS})


# --Filtering--
set_property(TARGET GabrAudio PROPERTY FOLDER "Gabr")


# --Library linking--

# Link entity module to core module
target_link_libraries(GabrCore PUBLIC GabrAudio)

# Link logger module to entity module
target_link_libraries(GabrAudio PUBLIC GabrLog)

# Framework Precompiled headers module
target_link_libraries(GabrAudio PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrAudio PUBLIC GabrPlatform)

# SoLoud library
target_link_libraries(GabrAudio PUBLIC soloud)


# --Other--

# Compile features
target_compile_features(GabrAudio PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrAudio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})