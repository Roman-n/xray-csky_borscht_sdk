cmake_minimum_required(VERSION 3.15)
project(LWO LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_precompile_headers(${PROJECT_NAME} PRIVATE StdAfx.h)
target_sources(${PROJECT_NAME} PRIVATE
	clip.c
	envelope.c
	envelope.h
	list.c
	lwio.c
	LWO.cpp
	lwo2.c
	lwo2.h
	lwob.c
#	main.c
	pntspols.c
	ReadMe.txt
	StdAfx.h
	surface.c
	vecmath.c
	vmap.c)
