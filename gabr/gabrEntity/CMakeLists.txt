cmake_minimum_required(VERSION 3.20)

# --Project setup--
project(GabrEntity LANGUAGES CXX)


# --Sources and Headers--

# Sources
set(GABR_ENTITY_SOURCES
	entity/entity.cpp
	entity/entityManager.cpp
)

# Headers
set(GABR_ENTITY_HEADERS 
	entity/entity.h
	entity/entityManager.h
)


# --Library--
add_library(GabrEntity STATIC ${GABR_ENTITY_SOURCES} ${GABR_ENTITY_HEADERS})


# --Filtering--
set_property(TARGET GabrEntity PROPERTY FOLDER "Gabr")


# --Library linking--

# Link entity module to core module
target_link_libraries(GabrCore PUBLIC GabrEntity)

# Link logger module to entity module
target_link_libraries(GabrEntity PUBLIC GabrLog)

# Framework Precompiled headers module
target_link_libraries(GabrEntity PUBLIC GabrPch)

# Framework platform module
target_link_libraries(GabrEntity PUBLIC GabrPlatform)

# Link rendering module to entity module
target_link_libraries(GabrEntity PUBLIC GabrRendering)


# --Other--

# Compile features
target_compile_features(GabrEntity PUBLIC cxx_std_17)

# Include directories
target_include_directories(GabrEntity PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})