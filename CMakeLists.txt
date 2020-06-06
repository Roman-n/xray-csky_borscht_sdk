message("CMAKE_VERSION " ${CMAKE_VERSION})
cmake_minimum_required(VERSION 3.15)
project(xray15)

include_directories(SDK/include)
link_directories(SDK/libraries/x64)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/intermediate/cmake-${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}-${CMAKE_BUILD_TYPE}")
set(USE_FOLDERS ON)
add_compile_definitions(
	$<$<CONFIG:Debug>:DEBUG>
	#$<$<CXX_COMPILER_ID:GNU>:_MT>
	)
add_compile_options(
	$<$<CXX_COMPILER_ID:GNU>:-fpermissive>
	$<$<CXX_COMPILER_ID:Clang>:-Wno-microsoft-template>)

message("CMAKE_CXX_COMPILER_ID " ${CMAKE_CXX_COMPILER_ID})

add_subdirectory("3rd_party/libogg-1.3.3")
add_subdirectory("3rd_party/libvorbis-1.3.6")
add_subdirectory("3rd_party/libtheora-1.1.1")
add_subdirectory("3rd_party/openal/OpenAL-Windows/Router")
add_subdirectory("3rd_party/DxErr")
add_subdirectory("3rd_party/WildMagic")
add_subdirectory("3rd_party/imdexlib")
add_subdirectory("3rd_party/luabind")
add_subdirectory("3rd_party/nvidia-texture-tools")
add_subdirectory("3rd_party/MagicSoftware/FreeMagic")
add_subdirectory(xray/xrCore)
add_subdirectory(xray/xrCDB)
add_subdirectory(xray/xrSound)
add_subdirectory(xray/xrParticles)
add_subdirectory(xray/xrCPU_Pipe)
add_subdirectory(xray/xrXMLParser)
add_subdirectory(xray/utils/xrQSlim)
add_subdirectory(xray/utils/ETools)
add_subdirectory(xray/utils/LWO)
add_subdirectory(xray/utils/xrDXT)
add_subdirectory(xray/utils/xrSE_Factory)
add_subdirectory(xray/editors/xrEProps)
add_subdirectory(xray/editors/ECore)
add_subdirectory(xray/editors/LevelEditor)

set_target_properties(DxErr libogg libtheora_static libvorbis_static libvorbisfile luabind openal32 LWO WildMagic PROPERTIES FOLDER "3rd_party")
set_target_properties(squish rg_etc1 posh nvthread nvmath nvimage nvcore bc7 bc6h nvtt PROPERTIES FOLDER "3rd_party/nvtt")
set_target_properties(MagicFM MagicFM_Core MagicFM_Distance2D MagicFM_Distance3D MagicFM_Core2D MagicFM_Core3D PROPERTIES FOLDER "3rd_party/MagicFM")