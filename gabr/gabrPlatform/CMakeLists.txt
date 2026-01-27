cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrPlatform LANGUAGES CXX)


# --Library--
add_library(GabrPlatform INTERFACE)


# --Compile definitions--
if (WIN32)
	message(STATUS "Building for Windows (x64)")
	target_compile_definitions(GabrPlatform INTERFACE GABR_TARGET_WIN GABR_BUILD)
elseif (UNIX)
	message(STATUS "Building for Linux")
	target_compile_definitions(GabrPlatform INTERFACE GABR_TARGET_LINUX GABR_BUILD)
endif()


# --Other--

# Include directories
target_include_directories(GabrPlatform INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})