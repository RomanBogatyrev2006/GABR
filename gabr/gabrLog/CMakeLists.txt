cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrLog LANGUAGES CXX)


# --Sources and Headers--

# Sources
set(GABR_LOGGER_SOURCES
	log/logger.cpp
)

# Headers
set(GABR_LOGGER_HEADERS 
	log/logger.h
	asserts/asserts.h
)


# --Library--
add_library(GabrLog STATIC ${GABR_LOGGER_SOURCES} ${GABR_LOGGER_HEADERS})


# --Filtering--
set_property(TARGET GabrLog PROPERTY FOLDER "Gabr")


# --Library linking--

# Link module to GabrFramework interface
#target_link_libraries(GabrFramework INTERFACE GabrLog)

# Link logger module to core module
target_link_libraries(GabrCore PUBLIC GabrLog)

# Framework Precompiled headers module
target_link_libraries(GabrLog PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrLog PUBLIC GabrPlatform)


# --Other--

# Compile features
target_compile_features(GabrLog PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrLog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})