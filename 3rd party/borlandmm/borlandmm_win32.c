//---------------------------------------------------------------------------

#include <windows.h>
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#define BORLANDMM_API __cdecl

#define Message(msg) MessageBox(NULL, msg, NULL, MB_OK)
//#define MessageOnce(msg) do { static BOOL done = FALSE; if(!done) { MessageBox(NULL, msg, NULL, MB_OK); done = TRUE; } } while(0)
#define MessageOnce(msg)

HANDLE ProcessHeap;
ULONG  AllocCount, AllocSize;

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
/*
	if(reason == DLL_PROCESS_ATTACH)
    {
		MessageOnce("DllEntryPoint");
		ProcessHeap = GetProcessHeap();

        if(ProcessHeap == NULL)
        {
        	MessageBox(NULL, "GetProcessHeap failed", NULL, MB_OK);
            ExitProcess(-1);
        }
    }
*/
	return 1;
}

unsigned BORLANDMM_API GetAllocMemSize()
{
	MessageOnce("GetAllocMemSize");
	return AllocSize;
}


unsigned BORLANDMM_API GetAllocMemCount()
{
	MessageOnce("GetAllocMemCount");
	return AllocCount;
}

struct THeapStatus
{
	unsigned TotalAddrSpace;
	unsigned TotalUncommitted;
	unsigned TotalCommitted;
	unsigned TotalAllocated;
	unsigned TotalFree;
	unsigned FreeSmall;
	unsigned FreeBig;
	unsigned Unused;
	unsigned Overhead;
	unsigned HeapErrorCode;
};

struct THeapStatus BORLANDMM_API GetHeapStatus()
{
	struct THeapStatus status = {0};
	MessageOnce("GetHeapStatus");
    return status;
}

void BORLANDMM_API DumpBlocks()
{
	MessageOnce("DumpBlocks");
}

int BORLANDMM_API FreeMemory(void *ptr)
{
	BOOL ret;
	DWORD size;
	MessageOnce("FreeMemory");
	if(ptr == NULL)	
		return FALSE;
	size = HeapSize(ProcessHeap, NULL, ptr);
	if(size == 0xFFFFFFFF)
	{
		Message("HeapSize failed");
		size = 0;
	}
	ret = HeapFree(ProcessHeap, NULL, ptr);
	if(ret)
	{
		AllocCount--;
		AllocSize -= size;
	}
	else
		Message("HeapFree failed");
					
	return !ret; 
}

void * BORLANDMM_API GetMemory(int size)
{
	PVOID ret; 
	MessageOnce("GetMemory");
	if(size == 0)
		return NULL;
	ret = HeapAlloc(ProcessHeap, NULL, size);
	if(ret)
	{
		AllocCount++;
		AllocSize += size;
	}
	else
		Message("HeapAlloc failed");

	return ret;
}

void * BORLANDMM_API ReallocMemory(void *ptr, int size)
{
	MessageOnce("ReallocMemory");
	if(ptr && size == 0)
    {
    	int ret = FreeMemory(ptr);

		if(ret != 0) 
			Message("FreeMemory failed");

        return NULL;
    }
    else if(!ptr && size)
    {
		PVOID ret = GetMemory(size);
		
		if(ret == NULL)
			Message("HeapAlloc failed");

		return ret;
    }
    else if(ptr && size)
    {
		DWORD old_size;
    	PVOID ret;

		old_size = HeapSize(ProcessHeap, NULL, ptr);
		if(old_size == 0xFFFFFFFF)
		{
			Message("HeapSize failed");
			size = 0;
		}

		ret = HeapReAlloc(ProcessHeap, NULL, ptr, size);
		if(!ret)
			Message("HeapRealloc failed");
		else
		{
			AllocSize -= old_size;
			AllocSize += size;
		}

		return ret;
    }
	else // if(!ptr && !size)
		return NULL;
}


void * __fastcall SysReallocMem(void *ptr, int size)
{
	return ReallocMemory(ptr, size);
}

void * __fastcall SysGetMem(int size)
{
	return GetMemory(size);
}

int __fastcall SysFreeMem(void *ptr)					
{
	return FreeMemory(ptr);			
}

void __fastcall HeapAddRef()
{
//	ULONG lfh = 2;
	MessageOnce("HeapAddRef");
	ProcessHeap = GetProcessHeap();

	if(ProcessHeap == NULL)
	{
		MessageBox(NULL, "GetProcessHeap failed", NULL, MB_OK);
		ExitProcess(-1);
	} 

//	HeapSetInformation(ProcessHeap, HeapCompatibilityInformation, &lfh, sizeof(lfh));
}

void __fastcall HeapRelease()							
{ 
}

//---------------------------------------------------------------------------




