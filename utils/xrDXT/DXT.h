#ifndef DXT_H
#define DXT_H

#ifdef DXT_EXPORTS
#define DXT_API(ret) extern "C" __declspec(dllexport) ret __stdcall
#else
#define DXT_API(ret) extern "C" __declspec(dllimport) ret __stdcall
#endif

typedef void * (__stdcall * DXTMalloc)(size_t size);
typedef void   (__stdcall * DXTMfree)(void *ptr);

struct STextureParams;

DXT_API(int) DXTCompress(LPCSTR out_name, u8* raw_data, u8* normal_map, u32 w, u32 h, u32 pitch, STextureParams* fmt, u32 depth);
//DXT_API(void)	DXTSetMemHooks(DXTMalloc alloc, DXTMfree free);

#endif
