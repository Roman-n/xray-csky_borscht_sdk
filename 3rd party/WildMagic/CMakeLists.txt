cmake_minimum_required(VERSION 3.15)
project(WildMagic LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_sources(${PROJECT_NAME} PRIVATE
	src/WmlApprGaussPointsFit3.cpp
	src/WmlBox3.cpp
	src/WmlContBox3.cpp
	src/WmlContMinBox3.cpp
	src/WmlEigen.cpp
	src/WmlMath.cpp
	src/WmlMatrix2.cpp
	src/WmlMatrix3.cpp
	src/WmlMatrix4.cpp
	src/WmlMinimize1.cpp
	src/WmlMinimizeN.cpp
	src/WmlQuaternion.cpp
	src/WmlSystem.cpp
	src/WmlVector2.cpp
	src/WmlVector3.cpp
	src/WmlVector4.cpp
	src/WmlWinSystem.cpp)
