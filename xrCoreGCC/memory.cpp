#include <stdlib.h>
#include "../xrCore/xrCore.h"

xrMemory Memory;

// Processor specific implementations
//extern		pso_MemCopy		xrMemCopy_MMX;
//extern		pso_MemCopy		xrMemCopy_x86;
extern		pso_MemFill		xrMemFill_x86;
extern		pso_MemFill32	xrMemFill32_MMX;
extern		pso_MemFill32	xrMemFill32_x86;

xrMemory::xrMemory()
{
	mem_fill = xrMemFill_x86;
	mem_fill32 = xrMemFill32_x86;	
}

void* xrMemory::mem_alloc(size_t size)
{
	return malloc(size);
}

void* xrMemory::mem_realloc(void* ptr, size_t size)
{
	return realloc(ptr, size);
}

void xrMemory::mem_free(void* ptr)
{
	return free(ptr);
}
