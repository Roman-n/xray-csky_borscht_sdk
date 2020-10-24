cmake_minimum_required(VERSION 3.15)
project(xrQSlim LANGUAGES C CXX)

add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PUBLIC SRC)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/stdafx.h)
target_sources(${PROJECT_NAME} PRIVATE
	src/geom3d.h
	src/mat2.cpp
	src/mat2.h
	src/mat3.cpp
	src/mat3.h
	src/mat4.cpp
	src/mat4.h
	src/mixmops.cpp
	src/mixmops.h
	src/mixvops.h
	src/MxBlock.h
	src/MxBlock2.h
	src/MxBlockModel.cpp
	src/MxBlockModel.h
	src/MxDefines.h
	src/MxDynBlock.h
	src/MxGeom3D.cpp
	src/MxGeom3D.h
	src/MxGeoPrims.h
	src/MxHeap.cpp
	src/MxHeap.h
	src/MxMat2.h
	src/MxMat3.h
	src/MxMat3-jacobi.cpp
	src/MxMat4.h
	src/MxMat4-jacobi.cpp
	src/MxMatrix.cpp
	src/MxMatrix.h
	src/MxPropSlim.cpp
	src/MxPropSlim.h
	src/MxQMetric.cpp
	src/MxQMetric.h
	src/MxQMetric3.cpp
	src/MxQMetric3.h
	src/MxQSlim.cpp
	src/MxQSlim.h
	src/MxStdModel.cpp
	src/MxStdModel.h
	src/MxStdSlim.cpp
	src/MxStdSlim.h
	src/MxVec3.h
	src/MxVec4.h
	src/MxVector.h
	src/stdafx.h
	src/vec2.h
	src/vec3.h
	src/vec4.h)
