#ifndef utf8H
#define utf8H

ECORE_API xr_string codepage2utf8(const xr_string &str);
ECORE_API xr_string wide2utf8(const std::wstring &wstr);

#endif
