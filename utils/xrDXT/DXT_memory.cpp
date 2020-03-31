#include "stdafx.h"
#include "DXT.h"

static void * __stdcall default_malloc(size_t size)
{
	return malloc(size);
}

static void __stdcall default_mfree(void *ptr)
{
	free(ptr);
}

static DXTMalloc mem_alloc	= default_malloc;
static DXTMfree  mem_free	= default_mfree;

DXT_API(void) DXTSetMemHooks(DXTMalloc alloc, DXTMfree free)
{
	mem_alloc = alloc;
	mem_free = free;
}

void *operator new (size_t size)
{
	return mem_alloc(size);
}

void operator delete (void *ptr)
{
	mem_free(ptr);
}

void *operator new [] (size_t size)
{
	return mem_alloc(size);
}

void operator delete [] (void *ptr)
{
	mem_free(ptr);
}