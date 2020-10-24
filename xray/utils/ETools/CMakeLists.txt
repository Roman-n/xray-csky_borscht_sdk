cmake_minimum_required(VERSION 3.15)
project(ETools LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DETOOLS_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE StdAfx.h)
target_sources(${PROJECT_NAME} PRIVATE
	ArbitraryList.h
	audio.cpp
	audio.h
	BinaryHeap.h
	CreateDX.cpp
	D3DX_Wrapper.h
	DLink.h
	encode.cpp
	encode.h
	ETools.cpp
	ETools.h
	ETools_cm.cpp
	mesh.h
	object.cpp
	object.h
	object_sliding.cpp
	object_sliding.h
	ogg_enc.cpp
	optimize_vertex_order.cpp
	platform.cpp
	platform.h
	PropSlimTools.cpp
	PropSlimTools.h
	quad.h
	resample.cpp
	resample.h
	StdAfx.cpp
	StdAfx.h
	xrXRC.cpp
	xrXRC.h)
target_link_libraries(${PROJECT_NAME} PRIVATE libvorbis_static libogg xrCore xrCDB xrQSlim DxErr d3dx9.lib)
