cmake_minimum_required(VERSION 3.15)
project(xrParticles LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DXR_PARTICLES_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)
target_sources(${PROJECT_NAME} PRIVATE
	noise.cpp
	noise.h
	particle_actions.cpp
	particle_actions.h
	particle_actions_collection.cpp
	particle_actions_collection.h
	particle_actions_collection_io.cpp
	particle_core.cpp
	particle_core.h
	particle_effect.cpp
	particle_effect.h
	particle_manager.cpp
	particle_manager.h
	psystem.h
	stdafx.cpp
	stdafx.h)
target_link_libraries(${PROJECT_NAME} PRIVATE xrCore)
