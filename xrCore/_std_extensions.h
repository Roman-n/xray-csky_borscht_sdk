#ifndef _STD_EXT_internal
#define _STD_EXT_internal

#define	BREAK_AT_STRCMP
#ifndef DEBUG
#undef  BREAK_AT_STRCMP
#endif
#ifdef  _EDITOR
#undef  BREAK_AT_STRCMP
#endif

#ifdef abs
#undef abs
#endif

#ifdef _MIN
#undef _MIN
#endif

#ifdef _MAX
#undef _MAX
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef M_BORLAND
#define _REDIFINE_SECURE_FUNCS
#endif

#ifdef M_GCC
// MinGW know about new functions, but this need to winXP support
#define _REDIFINE_SECURE_FUNCS
#endif

#ifdef _REDIFINE_SECURE_FUNCS

#ifdef M_BORLAND
typedef int errno_t;
#endif

IC errno_t strcpy_s(char* dest, size_t dest_sz, const char* src)
{
	strcpy(dest, src);
	return 0;
}

IC errno_t _strlwr_s(char* str, size_t size)
{
	strlwr(str);
	return 0;
}

IC errno_t strcat_s(char* dest, size_t dest_size, const char* str)
{
	strcat(dest, str);
	return 0;
}

IC int sprintf_s(char* dest, size_t sizeOfBuffer, const char* format, ...)
{
	va_list 	mark;
	va_start	(mark, format );
	int sz		= _vsnprintf(dest, sizeOfBuffer, format, mark );
    dest		[sizeOfBuffer-1]=0;
    va_end		(mark);
    return 		sz;
}

IC errno_t strncpy_s(char* dest, size_t dest_sz, const char* src, size_t maxlen)
{
	strncpy(dest, src, maxlen);
	return 0;
}

IC errno_t wcstombs_s(size_t* result, char* mbstr, size_t mbstrsize, const wchar_t* wstr, size_t wstrsize)
{
	*result = wcstombs(mbstr, wstr, mbstrsize);
	return 0;
}

// actually must be templates
IC errno_t strcpy_s(char* dest, const char* src)
{
	strcpy(dest, src);
    return 0;
}

IC errno_t strcat_s(char* dest, const char* str)
{
	strcat(dest, str);
    return 0;
}

#endif // ifdef _REDIFINE_SECURE_FUNCS

#ifdef _REDIFINE_SECURE_FUNCS
#undef _REDIFINE_SECURE_FUNCS
#endif

// work-around dumb borland compiler
#ifdef M_BORLAND
	// function redefinition
	#define fabsf(a) fabs(a)
	using std::sinf;
	#define asinf(a) asin(a)
	using std::cosf;
	#define acosf(a) acos(a)
	using std::tanf;
	#define atanf(a) atan(a)
	using std::sqrtf;
	using std::expf;
	#define floorf(a) floor(a)
	using std::atan2f;
	using std::logf;
	using std::fmodf;

	// this function declared in RAD Studio 2007
	// but while linking i got an 'unresolved symbol' error
	namespace std
	{
		IC float __cdecl fmodf(float num, float denom)
		{
			return fmod(num, denom);
		}
	}

	// float redefine
	#define _PC_24 PC_24
	#define _PC_53 PC_53
	#define _PC_64 PC_64
	#define _RC_CHOP RC_CHOP
	#define _RC_NEAR RC_NEAR
    #define _MCW_EM MCW_EM
    #define _MCW_PC MCW_PC
	#define _MCW_RC MCW_RC
#endif

// token type definition
struct XRCORE_API xr_token
{
	LPCSTR	name;
	int 	id;
};

IC LPCSTR get_token_name(xr_token* tokens, int key)
{
    for (int k=0; tokens[k].name; k++)
    	if (key==tokens[k].id) return tokens[k].name;
    return "";
}

IC int get_token_id(xr_token* tokens, LPCSTR key)
{
    for (int k=0; tokens[k].name; k++)
    	if ( stricmp(tokens[k].name,key)==0 ) 
			return tokens[k].id;
    return -1;
}

struct XRCORE_API xr_token2
{
	LPCSTR	name;
	LPCSTR	info;
	int 	id;
};

// generic
template <class T>	IC T		_min	(T a, T b)	{ return a<b?a:b;	}
template <class T>	IC T		_max	(T a, T b)	{ return a>b?a:b;	}
template <class T>	IC T		_sqr	(T a)		{ return a*a;		}

// float
IC float	_abs	(float x)		{ return fabsf(x); }
IC float	_sqrt	(float x)		{ return sqrtf(x); }
IC float	_sin	(float x)		{ return sinf(x); }
IC float	_cos	(float x)		{ return cosf(x); }
IC BOOL		_valid	(const float x)
{
	// check for: Signaling NaN, Quiet NaN, Negative infinity ( ?INF), Positive infinity (+INF), Negative denormalized, Positive denormalized
	int			cls			= _fpclass		(double(x));
	if (cls&(_FPCLASS_SNAN+_FPCLASS_QNAN+_FPCLASS_NINF+_FPCLASS_PINF+_FPCLASS_ND+_FPCLASS_PD))	
		return	false;	

	/*	*****other cases are*****
	_FPCLASS_NN Negative normalized non-zero 
	_FPCLASS_NZ Negative zero ( ? 0) 
	_FPCLASS_PZ Positive 0 (+0) 
	_FPCLASS_PN Positive normalized non-zero 
	*/
	return		true;
}


// double
IC double	_abs	(double x)		{ return fabs(x); }
IC double	_sqrt	(double x)		{ return sqrt(x); }
IC double	_sin	(double x)		{ return sin(x); }
IC double	_cos	(double x)		{ return cos(x); }
IC BOOL		_valid	(const double x)
{
	// check for: Signaling NaN, Quiet NaN, Negative infinity ( ?INF), Positive infinity (+INF), Negative denormalized, Positive denormalized
	int			cls			= _fpclass		(x);
	if (cls&(_FPCLASS_SNAN+_FPCLASS_QNAN+_FPCLASS_NINF+_FPCLASS_PINF+_FPCLASS_ND+_FPCLASS_PD))	
		return false;	

	/*	*****other cases are*****
	_FPCLASS_NN Negative normalized non-zero 
	_FPCLASS_NZ Negative zero ( ? 0) 
	_FPCLASS_PZ Positive 0 (+0) 
	_FPCLASS_PN Positive normalized non-zero 
	*/
	return		true;
}

// int8
IC s8		_abs	(s8  x)			{ return (x>=0)? x : s8(-x); }
IC s8 		_min	(s8  x, s8  y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s8 ) * 8 - 1))); };
IC s8 		_max	(s8  x, s8  y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s8 ) * 8 - 1))); };

// unsigned int8
IC u8		_abs	(u8 x)			{ return x; }

// int16
IC s16		_abs	(s16 x)			{ return (x>=0)? x : s16(-x); }
IC s16		_min	(s16 x, s16 y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1))); };
IC s16		_max	(s16 x, s16 y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1))); };

// unsigned int16
IC u16		_abs	(u16 x)			{ return x; }

// int32
IC s32		_abs	(s32 x)			{ return (x>=0)? x : s32(-x); }
IC s32		_min	(s32 x, s32 y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1))); };
IC s32		_max	(s32 x, s32 y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1))); };

// int64
IC s64		_abs	(s64 x)			{ return (x>=0)? x : s64(-x); }
IC s64		_min	(s64 x, s64 y)	{ return y + ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1))); };
IC s64		_max	(s64 x, s64 y)	{ return x - ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1))); };

IC u32							xr_strlen				( const char* S );

// string management

// return pointer to ".ext"
IC char*						strext					( const char* S )
{
	const char *dot = strrchr(S,'.');
    if(dot && dot > strrchr(S,'\\')) return (char*)dot;
    else return NULL;
}

IC u32							xr_strlen				( const char* S )
{	return (u32)strlen(S);			}

IC char*						xr_strlwr				(char* S)
{	return strlwr(S);				}

#ifdef BREAK_AT_STRCMP
XRCORE_API	int					xr_strcmp				( const char* S1, const char* S2 );
#else
IC int							xr_strcmp				( const char* S1, const char* S2 )
{	return (int)strcmp(S1,S2);  }
#endif

XRCORE_API	char*				timestamp				(string64& dest);

extern XRCORE_API u32			crc32					(const void* P, u32 len);
extern XRCORE_API u32			crc32					(const void* P, u32 len, u32 starting_crc);
extern XRCORE_API u32			path_crc32				(const char* path, u32 len); // ignores '/' and '\'

#endif // _STD_EXT_internal


