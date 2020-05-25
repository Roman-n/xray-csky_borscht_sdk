cmake_minimum_required(VERSION 3.15)
project(openal32 LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
#target_compile_definitions(${PROJECT_NAME} PRIVATE -DXRCORE_EXPORTS)
target_sources(${PROJECT_NAME} PRIVATE
	al.cpp
	alc.cpp
	alList.cpp
	alList.h
	OpenAL32.cpp
	OpenAL32.h
	OpenAL32.rc
	resource.h)
target_link_libraries(${PROJECT_NAME} PRIVATE winmm.lib)
