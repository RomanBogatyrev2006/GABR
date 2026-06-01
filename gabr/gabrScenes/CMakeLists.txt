cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrScenes LANGUAGES CXX)


# --Sources and Headers--

# Sources
set(GABR_SCENES_SOURCES
	scenes/scene.cpp
	scenes/sceneManager.cpp
)

# Headers
set(GABR_SCENES_HEADERS 
	scenes/scene.h
	scenes/sceneManager.h
)


# --Library--
add_library(GabrScenes STATIC ${GABR_SCENES_SOURCES} ${GABR_SCENES_HEADERS})


# --Filtering--
set_property(TARGET GabrScenes PROPERTY FOLDER "Gabr")


# --Library linking--

# Link scenes module to core module
target_link_libraries(GabrCore PUBLIC GabrScenes)

# Link logger module to scenes module
target_link_libraries(GabrScenes PUBLIC GabrLog)

# Framework Precompiled headers module
target_link_libraries(GabrScenes PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrScenes PUBLIC GabrPlatform)

# Link rendering module to scenes module
target_link_libraries(GabrScenes PUBLIC GabrRendering)

# Link entity module to scenes module
target_link_libraries(GabrScenes PUBLIC GabrEntity)


# --Other--

# Compile features
target_compile_features(GabrScenes PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrScenes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})