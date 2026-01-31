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


# --External modules--

# Bgfx
set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BGFX_INSTALL OFF CACHE BOOL "" FORCE)
if (WIN32)
	set(BGFX_CONFIG_RENDERER_OPENGL ON CACHE BOOL "" FORCE)
	set(BGFX_CONFIG_RENDERER_OPENGLES OFF CACHE BOOL "" FORCE)
	set(BGFX_CONFIG_RENDERER_DIRECT3D11 ON CACHE BOOL "" FORCE)
	set(BGFX_CONFIG_RENDERER_DIRECT3D12 ON CACHE BOOL "" FORCE)
	set(BGFX_CONFIG_RENDERER_VULKAN ON CACHE BOOL "" FORCE)
	set(BGFX_CONFIG_RENDERER_METAL OFF CACHE BOOL "" FORCE)
endif()
add_subdirectory(external/bgfxcmake)



#set(BGFX_INSTALL_EXAMPLES OFF CACHE BOOL "" FORCE)



# --Framework interface library that needs to link with game
add_library(GabrFramework INTERFACE)


# --Other--

target_link_libraries(GabrFramework INTERFACE
	GabrCore
	GabrLog
	GabrRender
)

# (ONLY FOR VISUAL STUDIO) Set default startup project to GABR instead cmake's ALL_BUILD
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GabrCore)

# Include directories
target_include_directories(GabrFramework INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/gabr)