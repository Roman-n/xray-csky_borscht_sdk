#include <stdlib.h>
#include "../xrCore/xrCore.h"

xrDebug Debug;

void xrDebug::_initialize(const bool&)
{
}

void xrDebug::fatal(const char* file, int line, const char* function, const char* F, ...)
{
	abort();
}

void xrDebug::fail(const char* e1, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}

void xrDebug::fail(const char* e1, const char* e2, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}

void xrDebug::fail(const char* e1, const std::string& e2, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}

void xrDebug::fail(const char* e1, const char* e2, const char* e3, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}

void xrDebug::fail(const char* e1, const char* e2, const char* e3, const char* e4, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}

void xrDebug::error(long code, const char* e1, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}

void xrDebug::error(long code, const char* e1, const char* e2, 
	const char* file, int line, const char* function, bool& ignore_always)
{
	abort();
}
