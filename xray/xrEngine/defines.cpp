#include "stdafx.h"

#ifdef DEBUG
	ECORE_API BOOL bDebug	= FALSE;
#endif

// Video
//. u32			psCurrentMode		= 1024;
u32			psCurrentVidMode[2] = {1024,768};
u32			psCurrentBPP		= 32;
// release version always has "mt_*" enabled
#ifdef DEBUG
Flags32		psDeviceFlags		= {             rsDetails|mtPhysics|mtSound|mtNetwork|rsDrawStatic|rsDrawDynamic};
#else
Flags32		psDeviceFlags		= {rsFullscreen|rsDetails|mtPhysics|mtSound|mtNetwork|rsDrawStatic|rsDrawDynamic};
#endif

// textures 
int			psTextureLOD		= 0;
u32			renderer_value		= 0;
