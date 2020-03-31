#ifndef STRING_CONCATENATIONS_H
#define STRING_CONCATENATIONS_H

IC char*						strconcat				( size_t dest_sz,  char* dest, const char* S1, const char* S2)
{
	size_t L1 = strlen(S1), L2 = strlen(S2);
	if(L1+L2+1>dest_sz)
		FATAL("strconcat: buffer overflow");

	memcpy(dest, S1, L1);
	memcpy(dest+L1, S2, L2+1);

	return dest;
}

// dest = S1+S2+S3
IC char*						strconcat				( size_t dest_sz,  char* dest, const char* S1, const char* S2, const char* S3)
{
	size_t L1 = strlen(S1), L2 = strlen(S2), L3 = strlen(S3);
	if(L1+L2+L3+1>dest_sz)
		FATAL("strconcat: buffer overflow");

	memcpy(dest, S1, L1);
	memcpy(dest+L1, S2, L2);
	memcpy(dest+L1+L2, S3, L3+1);

	return dest;
}

// dest = S1+S2+S3+S4
IC char*						strconcat				( size_t dest_sz,  char* dest, const char* S1, const char* S2, const char* S3, const char* S4)
{
	size_t L1 = strlen(S1), L2 = strlen(S2), L3 = strlen(S3), L4 = strlen(S4);
	if(L1+L2+L3+L4+1>dest_sz)
		FATAL("strconcat: buffer overflow");

	memcpy(dest, S1, L1);
	memcpy(dest+L1, S2, L2);
	memcpy(dest+L1+L2, S3, L3);
	memcpy(dest+L1+L2+L3, S4, L4+1);

	return dest;
}

// dest = S1+S2+S3+S4+S5
IC char*						strconcat				( size_t dest_sz,  char* dest, const char* S1, const char* S2, const char* S3, const char* S4, const char* S5)
{
	size_t L1 = strlen(S1), L2 = strlen(S2), L3 = strlen(S3), L4 = strlen(S4), L5 = strlen(S5);
	if(L1+L2+L3+L4+L5+1>dest_sz)
		FATAL("strconcat: buffer overflow");

	memcpy(dest, S1, L1);
	memcpy(dest+L1, S2, L2);
	memcpy(dest+L1+L2, S3, L3);
	memcpy(dest+L1+L2+L3, S4, L4);
    memcpy(dest+L1+L2+L3+L4, S5, L5+1);

	return dest;
}

// dest = S1+S2+S3+S4+S5+S6
IC char*						strconcat				( size_t dest_sz,  char* dest, const char* S1, const char* S2, const char* S3, const char* S4, const char* S5, const char* S6)
{
	size_t L1 = strlen(S1), L2 = strlen(S2), L3 = strlen(S3), L4 = strlen(S4), L5 = strlen(S5), L6 = strlen(S6);
	if(L1+L2+L3+L4+L5+L6+1>dest_sz)
		FATAL("strconcat: buffer overflow");

	memcpy(dest, S1, L1);
	memcpy(dest+L1, S2, L2);
	memcpy(dest+L1+L2, S3, L3);
	memcpy(dest+L1+L2+L3, S4, L4);
    memcpy(dest+L1+L2+L3+L4, S5, L5);
    memcpy(dest+L1+L2+L3+L4+L5, S6, L6+1);

	return dest;
}


// warning: do not comment this macro, as stack overflow check is very light 
// (consumes ~1% performance of STRCONCAT macro)
#ifdef M_VISUAL
#define STRCONCAT_STACKOVERFLOW_CHECK

#ifdef STRCONCAT_STACKOVERFLOW_CHECK

#define STRCONCAT(dest, ...) \
	do { \
	xray::core::detail::string_tupples	STRCONCAT_tupples_unique_identifier(__VA_ARGS__); \
	u32 STRCONCAT_buffer_size = STRCONCAT_tupples_unique_identifier.size(); \
	xray::core::detail::check_stack_overflow(STRCONCAT_buffer_size); \
	(dest) = (LPSTR)_alloca(STRCONCAT_buffer_size); \
	STRCONCAT_tupples_unique_identifier.concat	(dest); \
	} while (0)

#else //#ifdef STRCONCAT_STACKOVERFLOW_CHECK

#define STRCONCAT(dest, ...) \
	do { \
	xray::core::detail::string_tupples	STRCONCAT_tupples_unique_identifier(__VA_ARGS__); \
	(dest)		       = (LPSTR)_alloca(STRCONCAT_tupples_unique_identifier.size()); \
	STRCONCAT_tupples_unique_identifier.concat	(dest); \
	} while (0)

#endif //#ifdef STRCONCAT_STACKOVERFLOW_CHECK

#endif // M_VISUAL
#include "string_concatenations_inline.h"


#endif // #ifndef STRING_CONCATENATIONS_H
