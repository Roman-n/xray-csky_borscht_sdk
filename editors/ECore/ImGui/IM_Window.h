#ifndef IM_WINDOW_H
#define IM_WINDOW_H

ECORE_API class IM_Storage
{
	xr_string m_file_name;
	xr_string m_sect_name;

    CInifile* ini;

    public:
    IM_Storage(bool for_write, const xr_string& fn, const xr_string& sn);
    IM_Storage(bool for_write, const xr_string& sn);

    ~IM_Storage();

    public:
    int			GetInt(LPCSTR name, int def = 0);
    bool		GetBool(LPCSTR name, bool def = false);
    xr_string   GetString(LPCSTR name, const xr_string& def = xr_string(""));

    void		PutInt(LPCSTR name, int value);
    void		PutBool(LPCSTR name, bool value);
    void		PutString(LPCSTR name, const xr_string& value);
};

class IM_Window
{
	public:
    virtual void OnAdd() {}
    virtual void OnRemove() {}

    virtual void Render() = 0;
};

#endif
 