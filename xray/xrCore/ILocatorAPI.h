#pragma once

#include "LocatorAPI_defs.h"

class XRCORE_API CStreamReader;

struct ILocatorAPI
{
	virtual ~ILocatorAPI() = 0 {}

	enum{
		flNeedRescan			= (1<<0),
		flBuildCopy				= (1<<1),
		flReady					= (1<<2),
		flEBuildCopy			= (1<<3),
		flEventNotificator      = (1<<4),
		flTargetFolderOnly		= (1<<5),
		flCacheFiles			= (1<<6),
		flScanAppRoot			= (1<<7),
		flNeedCheck				= (1<<8),
		flDumpFileActivity		= (1<<9),
	};    
	Flags32						m_Flags			;
	u32							dwAllocGranularity;
	u32							dwOpenCounter;

	virtual void						_initialize			(u32 flags, LPCSTR target_folder=0, LPCSTR fs_name=0) = 0;
	virtual void						_destroy			() = 0;

	virtual bool						exist				(LPCSTR N) = 0;
	virtual bool						exist				(LPCSTR path, LPCSTR name) = 0;
	virtual bool						exist				(string_path& fn, LPCSTR path, LPCSTR name) = 0;
	virtual bool						exist				(string_path& fn, LPCSTR path, LPCSTR name, LPCSTR ext) = 0;

	virtual bool						path_exist			(LPCSTR path) = 0;
    virtual FS_Path*					get_path			(LPCSTR path) = 0;
    virtual LPCSTR						update_path			(string_path& dest, LPCSTR initial, LPCSTR src) = 0;

	virtual CStreamReader*				rs_open				(LPCSTR initial, LPCSTR N) = 0;
	virtual IReader*					r_open				(LPCSTR initial, LPCSTR N) = 0;
	virtual IReader*					r_open				(LPCSTR N) = 0;
	virtual void						r_close				(IReader* &S) = 0;
	virtual void						r_close				(CStreamReader* &fs) = 0;

	virtual IWriter*					w_open				(LPCSTR initial, LPCSTR N) = 0;
	virtual IWriter*					w_open				(LPCSTR N) = 0;
	virtual IWriter*					w_open_ex			(LPCSTR N) = 0;
	virtual void						w_close				(IWriter* &S) = 0;

	virtual void						auth_generate		(xr_vector<xr_string>&	ignore, xr_vector<xr_string>&	important) = 0;
	virtual u64							auth_get			() = 0;
	virtual void						auth_runtime		(void*) = 0;

    virtual BOOL 						dir_delete			(LPCSTR initial, LPCSTR N,BOOL remove_files) = 0;
    virtual BOOL 						dir_delete			(LPCSTR full_path,BOOL remove_files) = 0;
    virtual void 						file_delete			(LPCSTR path,LPCSTR nm) = 0;
    virtual void 						file_delete			(LPCSTR full_path) = 0;
	virtual void 						file_copy			(LPCSTR src, LPCSTR dest) = 0;
	virtual void 						file_rename			(LPCSTR src, LPCSTR dest,bool bOwerwrite=true) = 0;
	virtual int							file_length			(LPCSTR src) = 0;

    virtual time_t 						get_file_age		(LPCSTR nm) = 0;
    virtual void 						set_file_age		(LPCSTR nm, time_t age) = 0;

	virtual int							file_list			(FS_FileSet& dest, LPCSTR path, u32 flags=FS_ListFiles, LPCSTR mask=0) = 0;

	virtual xr_vector<LPSTR>*			file_list_open		(LPCSTR initial, LPCSTR folder,	u32 flags=FS_ListFiles) = 0;
	virtual xr_vector<LPSTR>*			file_list_open		(LPCSTR path,					u32 flags=FS_ListFiles) = 0;
	virtual void						file_list_close		(xr_vector<LPSTR>* &lst) = 0;

    virtual BOOL 						can_write_to_folder	(LPCSTR path) = 0; 
    virtual BOOL 						can_write_to_alias	(LPCSTR path) = 0;

	virtual bool						load_all_unloaded_archives() = 0;
    virtual bool						loadArchiveByLevelNameAnvVersion(LPCSTR name, LPCSTR version) = 0;
	virtual CInifile*					getArchiveHeader	(LPCSTR name, LPCSTR version) = 0;
	using MapCallback					= fastdelegate::FastDelegate<void(LPCSTR, const xr_string&, LPCSTR)>;
	virtual void						enumUnloadedMaps	(LPCSTR tmp_entrypoint, MapCallback callback) = 0;

	virtual void						rescan_path			(LPCSTR full_path, BOOL bRecurse) = 0;
	virtual void						rescan_pathes		() = 0;
};

extern XRCORE_API	ILocatorAPI*					xr_FS;
#define FS (*xr_FS)

inline bool ignore_name(const char* _name)
{
	// ignore processing ".svn" folders
	return ( _name[0]=='.' && _name[1]=='s' && _name[2]=='v' && _name[3]=='n' && _name[4]==0);
}
