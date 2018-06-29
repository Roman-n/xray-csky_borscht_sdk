#include "stdafx.h"
#include <malloc.h>
#include <errno.h>

XRCORE_API void vminfo (size_t *_free, size_t *reserved, size_t *committed) {
	MEMORY_BASIC_INFORMATION memory_info;
	memory_info.BaseAddress = 0;
	*_free = *reserved = *committed = 0;
	while (VirtualQuery (memory_info.BaseAddress, &memory_info, sizeof (memory_info))) {
		switch (memory_info.State) {
		case MEM_FREE:
			*_free		+= memory_info.RegionSize;
			break;
		case MEM_RESERVE:
			*reserved	+= memory_info.RegionSize;
			break;
		case MEM_COMMIT:
			*committed += memory_info.RegionSize;
			break;
		}
		memory_info.BaseAddress = (char *) memory_info.BaseAddress + memory_info.RegionSize;
	}
}

XRCORE_API void log_vminfo	()
{
	size_t  w_free, w_reserved, w_committed;
	vminfo	(&w_free, &w_reserved, &w_committed);
	Msg		(
		"* [win32]: free[%d K], reserved[%d K], committed[%d K]",
		w_free/1024,
		w_reserved/1024,
		w_committed/1024
	);
}

u32 mem_usage_impl(HANDLE heap_handle, u32* pBlocksUsed, u32* pBlocksFree)
{
	R_ASSERT2(HeapValidate(heap_handle, 0, NULL), "Memory corruption");

	size_t	allocated	= 0;
	size_t	free		= 0;
	u32	blocks_free		= 0;
	u32	blocks_used		= 0;

	PROCESS_HEAP_ENTRY entry;
	entry.lpData	= NULL;

	HeapLock		( heap_handle );

	while ( HeapWalk( heap_handle, &entry ) ) {
		if ( entry.wFlags & PROCESS_HEAP_ENTRY_BUSY ) {
			blocks_used ++;
			allocated += entry.cbData;
		}
		else {
			blocks_free ++;
			free += entry.cbData;
		}
	}

	R_ASSERT2(GetLastError() == ERROR_NO_MORE_ITEMS, "Memory corruption");

	HeapUnlock		( heap_handle );

	if (pBlocksFree)	*pBlocksFree = blocks_free;
	if (pBlocksUsed)	*pBlocksUsed = blocks_used;

	return allocated;
}

u32		xrMemory::mem_usage		(u32* pBlocksUsed, u32* pBlocksFree)
{
	return				(mem_usage_impl((HANDLE)_get_heap_handle(),pBlocksUsed,pBlocksFree));
}
