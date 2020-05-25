cmake_minimum_required(VERSION 3.15)
project(libogg LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PRIVATE
	src/bitwise.c
	src/framing.c)
