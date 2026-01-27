cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrCore LANGUAGES CXX)


# --Sources and Headers (Core)--

# Sources
set(GABR_CORE_CORE_SOURCES
	core/core.cpp
	core/application.cpp
)

# Headers
set(GABR_CORE_CORE_HEADERS
	core/core.h
	core/application.h
	core/entrypoint.h
)


# --Sources and Headers (Time)--

# Sources
set(GABR_CORE_TIME_SOURCES
	time/timer.cpp
	time/fpslimit.cpp
)

# Headers
set(GABR_CORE_TIME_HEADERS
	time/timer.h
	time/fpslimit.h
)


# --Sources and Headers combined--

# Sources
set(GABR_CORE_SOURCES 
	${GABR_CORE_CORE_SOURCES}
	${GABR_CORE_TIME_SOURCES}
)

# Headers
set(GABR_CORE_HEADERS 
	${GABR_CORE_CORE_HEADERS}
	${GABR_CORE_TIME_HEADERS}
)


# --Library--
add_library(GabrCore SHARED ${GABR_CORE_SOURCES} ${GABR_CORE_HEADERS})


# --Filtering--
set_property(TARGET GabrCore PROPERTY FOLDER "Gabr")


# --Library linking--

# Framework Precompiled headers module
target_link_libraries(GabrCore PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrCore PUBLIC GabrPlatform)


# --Other--

# Compile features
target_compile_features(GabrCore PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})