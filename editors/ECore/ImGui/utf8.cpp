#include "stdafx.h"
#pragma hdrstop

#include "utf8.h"

#pragma package(smart_init)

ECORE_API xr_string codepage2utf8(const xr_string &str)
{
	size_t sz = MultiByteToWideChar(CP_ACP, 0, &*str.begin(), str.length(), NULL, 0);
    xr_vector<WCHAR> wstr;
    wstr.resize(sz);
    MultiByteToWideChar(CP_ACP, 0, &*str.begin(), str.length(), &*wstr.begin(), wstr.size());
    sz = WideCharToMultiByte(CP_UTF8, 0, &*wstr.begin(), wstr.size(), NULL, 0, NULL, NULL);
    xr_string result;
    result.resize(sz);
    WideCharToMultiByte(CP_UTF8, 0, &*wstr.begin(), wstr.size(), &*result.begin(), result.size(), NULL, NULL);
    return result;
}

ECORE_API xr_string wide2utf8(const std::wstring &wstr)
{
    size_t sz = WideCharToMultiByte(CP_UTF8, 0, &*wstr.begin(), wstr.size(), NULL, 0, NULL, NULL);
    xr_string result;
    result.resize(sz);
    WideCharToMultiByte(CP_UTF8, 0, &*wstr.begin(), wstr.size(), &*result.begin(), result.size(), NULL, NULL);
    return result;
}
