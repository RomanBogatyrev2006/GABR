cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GABR LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# --Framework modules--

# Core
add_subdirectory(gabr/gabrCore)

# Precompiled headers global module
add_subdirectory(gabr/gabrPch)

# Platform global module
add_subdirectory(gabr/gabrPlatform)

# Logger module
add_subdirectory(gabr/gabrLog)

# Rendering module
add_subdirectory(gabr/gabrRender)

# Entity module
add_subdirectory(gabr/gabrEntity)

# Input module
add_subdirectory(gabr/gabrInput)


# --External modules--

# SDL
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_AUDIO ON CACHE BOOL "" FORCE)
set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_FILESYSTEM OFF CACHE BOOL "" FORCE)
set(SDL_VIDEO ON CACHE BOOL "" FORCE)
set(SDL_EVENTS ON CACHE BOOL "" FORCE)
set(SDL_TIMER ON CACHE BOOL "" FORCE)
set(SDL_RENDER ON CACHE BOOL "" FORCE)
add_subdirectory(external/sdl)

# GLM
add_subdirectory(external/glm)


# --Framework interface library that needs to link with game
add_library(GabrFramework INTERFACE)


# --Other--

target_link_libraries(GabrFramework INTERFACE
	GabrCore
	GabrLog
	GabrRendering
	GabrEntity
)

# (ONLY FOR VISUAL STUDIO) Set default startup project to GABR instead cmake's ALL_BUILD
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GabrCore)

# Include directories
target_include_directories(GabrFramework INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/gabr)