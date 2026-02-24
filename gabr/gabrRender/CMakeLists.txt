cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrRendering LANGUAGES CXX)


# --Sources and Headers--

# Sources
set(GABR_RENDER_SOURCES
	rendering/renderingManager.cpp
	rendering/sprite.cpp
	rendering/texture.cpp
	rendering/shader.cpp
)

# Headers
set(GABR_RENDER_HEADERS 
	rendering/renderingManager.h
	rendering/sprite.h
	rendering/texture.h
	rendering/shader.h
	rendering/stb_image.h
)


# --Library--
add_library(GabrRendering STATIC ${GABR_RENDER_SOURCES} ${GABR_RENDER_HEADERS})


# --Filtering--
set_property(TARGET GabrRendering PROPERTY FOLDER "Gabr")


# --Library linking--

# Link logger module to core module
target_link_libraries(GabrCore PUBLIC GabrRendering)

# Logger module
target_link_libraries(GabrRendering PUBLIC GabrLog)

# Framework Precompiled headers module
target_link_libraries(GabrRendering PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrRendering PUBLIC GabrPlatform)

# Bgfx library
target_link_libraries(GabrRendering PUBLIC bgfx)

# SDL library
target_link_libraries(GabrRendering PUBLIC SDL3::SDL3)

# GLM library
target_link_libraries(GabrRendering PUBLIC glm)


# --Other--

# Compile features
target_compile_features(GabrRendering PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrRendering PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})