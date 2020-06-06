cmake_minimum_required(VERSION 3.15)
project(libtheora LANGUAGES C CXX)

add_library(libtheora_static STATIC)
target_include_directories(libtheora_static PUBLIC include)
target_sources(libtheora_static PRIVATE
#	lib/x86\
#	lib/x86_vc\
	lib/analyze.c
	lib/apiwrapper.c
	lib/apiwrapper.h
	lib/bitpack.c
	lib/bitpack.h
	lib/cpu.c
	lib/cpu.h
	lib/dct.h
	lib/decapiwrapper.c
	lib/decinfo.c
	lib/decint.h
	lib/decode.c
	lib/dequant.c
	lib/dequant.h
	lib/encapiwrapper.c
	lib/encfrag.c
	lib/encinfo.c
	lib/encint.h
	lib/encode.c
#	lib/encoder_disabled.c
	lib/enquant.c
	lib/enquant.h
	lib/fdct.c
	lib/fragment.c
	lib/huffdec.c
	lib/huffdec.h
	lib/huffenc.c
	lib/huffenc.h
	lib/huffman.h
	lib/idct.c
	lib/info.c
	lib/internal.c
	lib/internal.h
	lib/Makefile.am
	lib/Makefile.in
	lib/mathops.c
	lib/mathops.h
	lib/mcenc.c
	lib/modedec.h
	lib/ocintrin.h
	lib/quant.c
	lib/quant.h
	lib/rate.c
	lib/state.c
	lib/theora.exp
	lib/theoradec.exp
	lib/theoraenc.exp
	lib/tokenize.c
	lib/Version_script
	lib/Version_script-dec
	lib/Version_script-enc)
target_link_libraries(libtheora_static PUBLIC libogg)
