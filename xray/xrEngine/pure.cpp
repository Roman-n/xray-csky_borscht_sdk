#include "stdafx.h"


#include "pure.h"

ENGINE_API int	__cdecl	_REG_Compare(const void *e1, const void *e2)
{
	using REG_INFO = REG_INFO_T<void*>;
	REG_INFO* p1 = (REG_INFO*)e1;
	REG_INFO* p2 = (REG_INFO*)e2;
	return (p2->Prio - p1->Prio);
}

void __fastcall rp_Frame(void *p)
{
	((pureFrame *)p)->OnFrame();
}

void __fastcall rp_Render(void *p)
{
	((pureRender *)p)->OnRender();
}

void __fastcall rp_AppActivate(void *p)
{
	((pureAppActivate *)p)->OnAppActivate();
}

void __fastcall rp_AppDeactivate(void *p)
{
	((pureAppDeactivate *)p)->OnAppDeactivate();
}

void __fastcall rp_AppStart(void *p)
{
	((pureAppStart *)p)->OnAppStart();
}

void __fastcall rp_AppEnd(void *p)
{
	((pureAppEnd *)p)->OnAppEnd();
}

void __fastcall rp_DeviceReset(void *p)
{
	((pureDeviceReset *)p)->OnDeviceReset();
}

