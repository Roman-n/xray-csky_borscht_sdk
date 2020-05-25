// LocatorAPI.h: interface for the CLocatorAPI class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ELocatorAPIH
#define ELocatorAPIH
#pragma once

#include "LocatorAPI_defs.h"

class XRCORE_API ELocatorAPI : public ILocatorAPI  
{
	friend class FS_Path;
public:
private:
	DEFINE_MAP_PRED				(LPCSTR,FS_Path*,PathMap,PathPairIt,pred_str);
	PathMap						pathes;
public:
								ELocatorAPI		();
								~ELocatorAPI	();
	void						_initialize		(u32 flags, LPCSTR target_folder=0, LPCSTR fs_fname=0) override;
	void						_destroy		() override;

	CStreamReader*				rs_open			(LPCSTR initial, LPCSTR N) override;
	IReader*					r_open			(LPCSTR initial, LPCSTR N) override;
	IC IReader*					r_open			(LPCSTR N) override {return r_open(0,N);}
	void						r_close			(IReader* &S) override;
	void						r_close			(CStreamReader* &fs) override;

	IWriter*					w_open			(LPCSTR initial, LPCSTR N) override;
	IWriter*					w_open_ex		(LPCSTR initial, LPCSTR N);
	IC IWriter*					w_open			(LPCSTR N) override {return w_open(0,N);}
	IC IWriter*					w_open_ex		(LPCSTR N) override {return w_open_ex(0,N);}
	void						w_close			(IWriter* &S) override;

	bool						exist			(LPCSTR N) override;
	bool						exist			(LPCSTR path, LPCSTR name) override;
	bool						exist			(string_path& fn, LPCSTR path, LPCSTR name) override;
	bool						exist			(string_path& fn, LPCSTR path, LPCSTR name, LPCSTR ext) override;

    BOOL 						can_write_to_folder	(LPCSTR path) override; 
    BOOL 						can_write_to_alias	(LPCSTR path) override; 
    BOOL						can_modify_file	(LPCSTR fname);
    BOOL						can_modify_file	(LPCSTR path, LPCSTR name);

    BOOL 						dir_delete			(LPCSTR initial, LPCSTR N,BOOL remove_files) override;
    BOOL 						dir_delete			(LPCSTR full_path,BOOL remove_files) override {return dir_delete(0,full_path,remove_files);}
    void 						file_delete			(LPCSTR path,LPCSTR nm) override;
    void 						file_delete			(LPCSTR full_path) override {file_delete(0,full_path);}
	void 						file_copy			(LPCSTR src, LPCSTR dest) override;
	void 						file_rename			(LPCSTR src, LPCSTR dest,bool bOwerwrite=true) override;
    int							file_length			(LPCSTR src) override;

    time_t 						get_file_age		(LPCSTR nm) override;
    void 						set_file_age		(LPCSTR nm, time_t age) override;

    bool						path_exist			(LPCSTR path) override;
    FS_Path*					get_path			(LPCSTR path) override;
    FS_Path*					append_path			(LPCSTR path_alias, LPCSTR root, LPCSTR add, BOOL recursive);
    LPCSTR						update_path			(string_path& dest, LPCSTR initial, LPCSTR src) override;

	BOOL						file_find			(LPCSTR full_name, FS_File& f);

	int							file_list			(FS_FileSet& dest, LPCSTR path, u32 flags=FS_ListFiles, LPCSTR mask=0) override;
//.    void						update_path			(xr_string& dest, LPCSTR initial, LPCSTR src);

	void						auth_generate		(xr_vector<xr_string>&	ignore, xr_vector<xr_string>&	important) override;
	u64							auth_get			() override;
	void						auth_runtime		(void*) override;

	xr_vector<LPSTR>*			file_list_open		(LPCSTR initial, LPCSTR folder,	u32 flags=FS_ListFiles) override;
	xr_vector<LPSTR>*			file_list_open		(LPCSTR path,					u32 flags=FS_ListFiles) override;
	void						file_list_close		(xr_vector<LPSTR>* &lst) override;

	virtual bool				load_all_unloaded_archives() override;
    bool						loadArchiveByLevelNameAnvVersion(LPCSTR name, LPCSTR version) override;
	CInifile*					getArchiveHeader	(LPCSTR name, LPCSTR version) override;
	void						enumUnloadedMaps	(LPCSTR tmp_entrypoint, MapCallback callback) override;

	void						rescan_path			(LPCSTR full_path, BOOL bRecurse) override;
	void						rescan_pathes		() override;
};

#endif // ELocatorAPIH

