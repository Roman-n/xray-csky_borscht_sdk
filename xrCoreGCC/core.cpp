#include <string.h>
#include "../xrCore/xrCore.h"
#include "../xrCore/cpuid.h"

xrCore Core;

void xrCore::_initialize(LPCSTR ApplicationName, LogCallback cb, BOOL init_fs, LPCSTR fs_name)
{
	strcpy(this->ApplicationName, ApplicationName);
	strcpy(this->Params, GetCommandLine());
	
	CPU::ID.feature = _CPU_FEATURE_SSE|_CPU_FEATURE_SSE2;
	CPU::ID.os_support = _CPU_FEATURE_SSE|_CPU_FEATURE_SSE2;
}

void xrCore::_destroy()
{
}

namespace FPU
{
	void m64r() 
	{
	}
}

namespace CPU
{
	_processor_info ID;
}

void _initialize_cpu_thread()
{
}

void thread_spawn(thread_t* entry_point, const char* name, unsigned stack, void* args)
{
}
