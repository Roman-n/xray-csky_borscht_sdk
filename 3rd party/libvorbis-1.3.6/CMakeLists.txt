cmake_minimum_required(VERSION 3.15)
project(libvorbis LANGUAGES C CXX)

add_library(libvorbis_static STATIC)
target_include_directories(libvorbis_static PUBLIC include)
target_sources(libvorbis_static PRIVATE
#	lib/books\
#	lib/modes\
	lib/analysis.c
	lib/backends.h
#	lib/barkmel.c
	lib/bitrate.c
	lib/bitrate.h
	lib/block.c
	lib/codebook.c
	lib/codebook.h
	lib/codec_internal.h
	lib/envelope.c
	lib/envelope.h
	lib/floor0.c
	lib/floor1.c
	lib/highlevel.h
	lib/info.c
	lib/lookup.c
	lib/lookup.h
	lib/lookup_data.h
	lib/lookups.pl
	lib/lpc.c
	lib/lpc.h
	lib/lsp.c
	lib/lsp.h
	lib/Makefile.am
	lib/Makefile.in
	lib/mapping0.c
	lib/masking.h
	lib/mdct.c
	lib/mdct.h
	lib/misc.h
	lib/os.h
	lib/psy.c
	lib/psy.h
#	lib/psytune.c
	lib/registry.c
	lib/registry.h
	lib/res0.c
	lib/scales.h
	lib/sharedbook.c
	lib/smallft.c
	lib/smallft.h
	lib/synthesis.c
#	lib/tone.c
	lib/vorbisenc.c
	lib/window.c
	lib/window.h)
target_link_libraries(libvorbis_static PRIVATE libogg)

add_library(libvorbisfile STATIC)
target_include_directories(libvorbisfile PUBLIC include)
target_sources(libvorbisfile PRIVATE
	lib/vorbisfile.c)
target_link_libraries(libvorbisfile PRIVATE libogg libvorbis_static)
