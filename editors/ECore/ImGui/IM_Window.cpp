#include "stdafx.h"
#pragma hdrstop

#include "IM_Window.h"

IM_Storage::IM_Storage(bool for_write, const xr_string& fn, const xr_string& sn)
	: m_file_name(fn),
	  m_sect_name(sn)
{
	// CInifile automatically converts section names to lowercase while writing
    // but while reading it uses case sensitive comarison :-\
    // so convert section name to lowercase anyway
    for(size_t i = 0; i < m_sect_name.size(); i++)
    	m_sect_name[i] = tolower(m_sect_name[i]);

	ini = CInifile::Create(m_file_name.c_str(), !for_write);
    ini->set_override_names(for_write);
}

IM_Storage::IM_Storage(bool for_write, const xr_string& sn)
{
	IM_Storage(for_write, "imgui.ini", sn);
}

IM_Storage::~IM_Storage()
{
	CInifile::Destroy(ini);
}

int IM_Storage::GetInt(LPCSTR name, int def)
{
	if(ini->line_exist(m_sect_name.c_str(), name))
    	return ini->r_s32(m_sect_name.c_str(), name);
    else
    	return def;
}

void IM_Storage::PutInt(LPCSTR name, int value)
{
	ini->remove_line(m_sect_name.c_str(), name);
    ini->w_s32(m_sect_name.c_str(), name, value);
}

bool IM_Storage::GetBool(LPCSTR name, bool def)
{
	if(ini->line_exist(m_sect_name.c_str(), name))
    	return ini->r_bool(m_sect_name.c_str(), name);
    else
    	return def;
}

void IM_Storage::PutBool(LPCSTR name, bool value)
{
	ini->remove_line(m_sect_name.c_str(), name);
    ini->w_bool(m_sect_name.c_str(), name, value);
}

xr_string IM_Storage::GetString(LPCSTR name, const xr_string& def)
{
	if(ini->line_exist(m_sect_name.c_str(), name))
    	return ini->r_string_wb(m_sect_name.c_str(), name).c_str();
    else
    	return def;
}

void IM_Storage::PutString(LPCSTR name, const xr_string& value)
{
	xr_string s = xr_string("\"") + value + "\"";
	ini->remove_line(m_sect_name.c_str(), name);
    ini->w_string(m_sect_name.c_str(), name, s.c_str());
}
 