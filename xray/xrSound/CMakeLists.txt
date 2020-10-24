cmake_minimum_required(VERSION 3.15)
project(xrSound LANGUAGES C CXX)

add_library(${PROJECT_NAME} SHARED)
target_compile_definitions(${PROJECT_NAME} PRIVATE -DXRSOUND_EXPORTS)
target_link_directories(${PROJECT_NAME} PRIVATE SDK/libraries/x64)
target_precompile_headers(${PROJECT_NAME} PRIVATE stdafx.h)
target_sources(${PROJECT_NAME} PRIVATE
	guids.cpp
#	MusicStream.cpp
#	MusicStream.h
	OpenALDeviceList.cpp
	OpenALDeviceList.h
	sound.cpp
	Sound.h
	SoundRender.h
	SoundRender_Cache.cpp
	SoundRender_Cache.h
	SoundRender_Core.cpp
	SoundRender_Core.h
	SoundRender_Core_Processor.cpp
	SoundRender_Core_SourceManager.cpp
	SoundRender_Core_StartStop.cpp
	SoundRender_CoreA.cpp
	SoundRender_CoreA.h
	SoundRender_CoreD.cpp
	SoundRender_CoreD.h
	SoundRender_Emitter.cpp
	SoundRender_Emitter.h
	SoundRender_Emitter_FSM.cpp
	SoundRender_Emitter_StartStop.cpp
	SoundRender_Emitter_streamer.cpp
	SoundRender_Environment.cpp
	SoundRender_Environment.h
	SoundRender_NoSound.h
	SoundRender_Source.cpp
	SoundRender_Source.h
	SoundRender_Source_loader.cpp
	SoundRender_Target.cpp
	SoundRender_Target.h
	SoundRender_TargetA.cpp
	SoundRender_TargetA.h
	SoundRender_TargetD.cpp
	SoundRender_TargetD.h
	stdafx.cpp
	stdafx.h
#	xr_cda.cpp
#	xr_cda.h
#	xr_streamsnd.cpp
#	xr_streamsnd.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE xrCore xrCDB openal32 libvorbisfile libogg)
