cmake_minimum_required(VERSION 3.15)
project(DXT LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE
#	dds\
	dds.h
	DXT.cpp
	ETextureParams.cpp
	ETextureParams.h
	Image_DXTC.cpp
	Image_DXTC.h
	NormalMapGen.cpp
	NV_Common.h
	NVI_Convolution.cpp
	NVI_Convolution.h
	NVI_Image.cpp
	NVI_Image.h
	ReadMe.txt
	StdAfx.cpp
	StdAfx.h
	tga.cpp
	tga.h)
target_link_libraries(${PROJECT_NAME} PRIVATE xrCore nvtt.lib)
