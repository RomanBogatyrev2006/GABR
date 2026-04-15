cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrInput LANGUAGES CXX)


# --Sources and Headers--

# Sources
set(GABR_INPUT_SOURCES
	input/input.cpp
)

# Headers
set(GABR_INPUT_HEADERS 
	input/input.h
)


# --Library--
add_library(GabrInput STATIC ${GABR_INPUT_SOURCES} ${GABR_INPUT_HEADERS})


# --Filtering--
set_property(TARGET GabrInput PROPERTY FOLDER "Gabr")


# --Library linking--

# Link module to GabrFramework interface
#target_link_libraries(GabrFramework INTERFACE GabrLog)

# Link logger module to core module
target_link_libraries(GabrCore PUBLIC GabrInput)

# Framework Precompiled headers module
target_link_libraries(GabrInput PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrInput PUBLIC GabrPlatform)

# SDL3
target_link_libraries(GabrInput PUBLIC SDL3::SDL3)


# --Other--

# Compile features
target_compile_features(GabrInput PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrInput PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})