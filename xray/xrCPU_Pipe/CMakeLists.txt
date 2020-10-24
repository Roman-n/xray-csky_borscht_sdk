cmake_minimum_required(VERSION 3.15)
project(xrCPU_Pipe LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_precompile_headers(${PROJECT_NAME} PRIVATE StdAfx.h)
target_sources(${PROJECT_NAME} PRIVATE
#	3DNow!Lib.cpp
	StdAfx.cpp
	StdAfx.h
#	xrBoneLerp.cpp
#	xrBoneLerp_3DNow!.cpp
	xrCPU_Pipe.cpp
	xrCPU_Pipe.h
#	xrM44mul.cpp
#	xrM44mul_3DNow!.cpp
#	xrMemCopy8_3DNow!.cpp
#	xrMemFill32_3DNow!.cpp
	xrQuatSlerp.cpp
	xrSkin1W.cpp
#	xrSkin1W_3DNow!.cpp
#	xrSkin1W_SSE.cpp
	xrSkin2W.cpp
#	xrSkin2W_3DNow!.cpp
#	xrSkin2W_SSE.cpp
	xrTransfer.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE xrCore)
