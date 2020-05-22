cmake_minimum_required(VERSION 3.15)
project(DxErr LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE
	src/dxerr.cpp
	src/dxerr.h
	src/DXGetErrorDescription.inl
	src/DXGetErrorString.inl
	src/DXTrace.inl
	src/stdafx.cpp
	src/stdafx.h)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wno-c++11-narrowing>)
