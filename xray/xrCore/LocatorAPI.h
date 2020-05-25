// LocatorAPI.h: interface for the CLocatorAPI class.
//
//////////////////////////////////////////////////////////////////////

#ifndef LocatorAPIH
#define LocatorAPIH
#pragma once

#pragma warning(push)
#pragma warning(disable:4995)
#include <io.h>
#pragma warning(pop)

#include "LocatorAPI_defs.h"

class XRCORE_API CStreamReader;

class XRCORE_API CLocatorAPI : public ILocatorAPI
{
	friend class FS_Path;
public:
	struct	file
	{
		LPCSTR					name;			// low-case name
		u32						vfs;			// 0xffffffff - standart file
		u32						crc;			// contents CRC
		u32						ptr;			// pointer inside vfs
		u32						size_real;		// 
		u32						size_compressed;// if (size_real==size_compressed) - uncompressed
        u32						modif;			// for editor
	};
	struct	archive
	{
		shared_str				path;
		void					*hSrcFile, *hSrcMap;
		u32						size;
		CInifile*				header;
		u32						vfs_idx;
		archive():hSrcFile(NULL),hSrcMap(NULL),header(NULL),size(0),vfs_idx(u32(-1)){}
		void					open();
		void					close();
	};
    DEFINE_VECTOR				(archive,archives_vec,archives_it);
    archives_vec				m_archives;
	void						LoadArchive		(archive& A, LPCSTR entrypoint=NULL);

private:
	struct	file_pred
	{	
		IC bool operator()	(const file& x, const file& y) const
		{	return xr_strcmp(x.name,y.name)<0;	}
	};
	DEFINE_MAP_PRED				(LPCSTR,FS_Path*,PathMap,PathPairIt,pred_str);
	PathMap						pathes;

	DEFINE_SET_PRED				(file,files_set,files_it,file_pred);

    int							m_iLockRescan	; 
    void						check_pathes	();

	files_set					m_files			;
	BOOL						bNoRecurse		;

	xrCriticalSection			m_auth_lock		;
	u64							m_auth_code		;

	void						Register		(LPCSTR name, u32 vfs, u32 crc, u32 ptr, u32 size_real, u32 size_compressed, u32 modif);
	void						ProcessArchive	(LPCSTR path);
	void						ProcessOne		(LPCSTR path, const _finddata_t& F);
	bool						Recurse			(LPCSTR path);	

	files_it					file_find_it	(LPCSTR n);

private:
			void				check_cached_files	(LPSTR fname, const u32 &fname_size, const file &desc, LPCSTR &source_name);

			void				file_from_cache_impl(IReader *&R, LPSTR fname, const file &desc);
			void				file_from_cache_impl(CStreamReader *&R, LPSTR fname, const file &desc);
	template <typename T>
			void				file_from_cache		(T *&R, LPSTR fname, const u32 &fname_size, const file &desc, LPCSTR &source_name);
			
			void				file_from_archive	(IReader *&R, LPCSTR fname, const file &desc);
			void				file_from_archive	(CStreamReader *&R, LPCSTR fname, const file &desc);

			void				copy_file_to_build	(IWriter *W, IReader *r);
			void				copy_file_to_build	(IWriter *W, CStreamReader *r);
	template <typename T>
			void				copy_file_to_build	(T *&R, LPCSTR source_name);

			bool				check_for_file		(LPCSTR path, LPCSTR _fname, string_path& fname, const file *&desc);
	
	template <typename T>
	IC		T					*r_open_impl		(LPCSTR path, LPCSTR _fname);

private:
			void				setup_fs_path		(LPCSTR fs_name, string_path &fs_path);
			void				setup_fs_path		(LPCSTR fs_name);
			IReader				*setup_fs_ltx		(LPCSTR fs_name);

public:
								CLocatorAPI			();
								~CLocatorAPI		();
	void						_initialize			(u32 flags, LPCSTR target_folder=0, LPCSTR fs_name=0) override;
	void						_destroy			() override;

	CStreamReader*				rs_open				(LPCSTR initial, LPCSTR N) override;
	IReader*					r_open				(LPCSTR initial, LPCSTR N) override;
	IC IReader*					r_open				(LPCSTR N) override {return r_open(0,N);}
	void						r_close				(IReader* &S) override;
	void						r_close				(CStreamReader* &fs) override;

	IWriter*					w_open				(LPCSTR initial, LPCSTR N) override;
	IC IWriter*					w_open				(LPCSTR N) override {return w_open(0,N);}
	IWriter*					w_open_ex			(LPCSTR initial, LPCSTR N);
	IC IWriter*					w_open_ex			(LPCSTR N) override {return w_open_ex(0,N);}
	void						w_close				(IWriter* &S) override;

	bool						exist				(LPCSTR N) override;
	bool						exist				(LPCSTR path, LPCSTR name) override;
	bool						exist				(string_path& fn, LPCSTR path, LPCSTR name) override;
	bool						exist				(string_path& fn, LPCSTR path, LPCSTR name, LPCSTR ext) override;

    BOOL 						can_write_to_folder	(LPCSTR path) override; 
    BOOL 						can_write_to_alias	(LPCSTR path) override; 
    BOOL						can_modify_file		(LPCSTR fname);
    BOOL						can_modify_file		(LPCSTR path, LPCSTR name);

    BOOL 						dir_delete			(LPCSTR path,LPCSTR nm,BOOL remove_files) override;
    BOOL 						dir_delete			(LPCSTR full_path,BOOL remove_files) override {return dir_delete(0,full_path,remove_files);}
    void 						file_delete			(LPCSTR path,LPCSTR nm) override;
    void 						file_delete			(LPCSTR full_path) override {file_delete(0,full_path);}
	void 						file_copy			(LPCSTR src, LPCSTR dest) override;
	void 						file_rename			(LPCSTR src, LPCSTR dest,bool bOwerwrite=true) override;
    int							file_length			(LPCSTR src) override;

    time_t 						get_file_age		(LPCSTR nm) override;
    void 						set_file_age		(LPCSTR nm, time_t age) override;

	xr_vector<LPSTR>*			file_list_open		(LPCSTR initial, LPCSTR folder,	u32 flags=FS_ListFiles) override;
	xr_vector<LPSTR>*			file_list_open		(LPCSTR path,					u32 flags=FS_ListFiles) override;
	void						file_list_close		(xr_vector<LPSTR>* &lst) override;
                                                     
    bool						path_exist			(LPCSTR path) override;
    FS_Path*					get_path			(LPCSTR path) override;
    FS_Path*					append_path			(LPCSTR path_alias, LPCSTR root, LPCSTR add, BOOL recursive);
    LPCSTR						update_path			(string_path& dest, LPCSTR initial, LPCSTR src) override;

	int							file_list			(FS_FileSet& dest, LPCSTR path, u32 flags=FS_ListFiles, LPCSTR mask=0) override;

	bool						load_all_unloaded_archives() override;
	void						unload_archive		(archive& A);
    bool						loadArchiveByLevelNameAnvVersion(LPCSTR name, LPCSTR version) override;
	CInifile*					getArchiveHeader	(LPCSTR name, LPCSTR version) override;
	void						enumUnloadedMaps	(LPCSTR tmp_entrypoint, MapCallback callback) override;

	void						auth_generate		(xr_vector<xr_string>&	ignore, xr_vector<xr_string>&	important) override;
	u64							auth_get			() override;
	void						auth_runtime		(void*) override;

	void						rescan_path			(LPCSTR full_path, BOOL bRecurse) override;
	// editor functions
	void						rescan_pathes		() override;
	void						lock_rescan			();
	void						unlock_rescan		();
};

#endif // LocatorAPIH

