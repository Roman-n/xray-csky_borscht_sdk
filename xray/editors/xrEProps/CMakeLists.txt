cmake_minimum_required(VERSION 3.15)
project(xrEProps LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DNO_VCL -D_EDITOR -DXR_EPROPS_EXPORTS)
target_include_directories(${PROJECT_NAME} PRIVATE ../..)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)
target_sources(${PROJECT_NAME} PRIVATE
	ChoseForm.cpp
#	ChoseForm.ddp
#	ChoseForm.dfm
	ChoseForm.h
#	ColorPicker.cpp
#	ColorPicker.h
	dllmain.cpp
	EditorChooseEvents.h
	FolderLib.cpp
	FolderLib.h
	framework.h
#	GameTypeForm.cpp
#	GameTypeForm.dfm
#	GameTypeForm.h
#	ItemDialog.cpp
#	ItemDialog.ddp
#	ItemDialog.dfm
#	ItemDialog.h
#	ItemList.cpp
#	ItemList.ddp
#	ItemList.dfm
#	ItemList.h
	ItemListHelper.cpp
	ItemListHelper.h
#	ItemListTypes.cpp
#	NumericVector.cpp
#	NumericVector.ddp
#	NumericVector.dfm
#	NumericVector.h
#	PropertiesList.cpp
#	PropertiesList.ddp
#	PropertiesList.dfm
	PropertiesList.h
	PropertiesListHelper.cpp
	PropertiesListTypes.cpp
#	ShaderFunction.cpp
#	ShaderFunction.ddp
#	ShaderFunction.dfm
#	ShaderFunction.h
	stdafx.cpp
	stdafx.h
#	TextForm.cpp
#	TextForm.ddp
#	TextForm.dfm
#	TextForm.h
#	WaveForm.h
#	xrEProps.cpp
)
target_link_libraries(${PROJECT_NAME} PRIVATE xrCore)
