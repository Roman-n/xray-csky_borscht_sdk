cmake_minimum_required(VERSION 3.15)
project(xrXMLParser LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DXRXMLPARSER_EXPORTS)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)
target_sources(${PROJECT_NAME} PRIVATE
	StdAfx.cpp
	stdafx.h
	tinystr.cpp
	tinystr.h
	tinyxml.cpp
	tinyxml.h
	tinyxmlerror.cpp
	tinyxmlparser.cpp
	xrXMLParser.cpp
	xrXMLParser.h)
target_link_libraries(${PROJECT_NAME} PRIVATE xrCore)
