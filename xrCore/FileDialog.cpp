#include "stdafx.h"
#pragma hdrstop

#include <commdlg.h>
#include <objbase.h>
#include <wchar.h>
#include <cderr.h>
#include "FileDialog.h"

typedef HRESULT (*LPFNSHCREATEITEMFROMPARSINGNAMEPROC)(PCWSTR path, void *, REFIID riid, void **ppv);
static LPFNSHCREATEITEMFROMPARSINGNAMEPROC pSHCreateItemFromParsingName;

#if _WIN32_WINNT < 0x0600

enum _FDAP
{
	FDAP_BOTTOM = 0,
    FDAP_TOP    = 1
};
typedef DWORD FDAP;

enum _FILEOPENDIALOGOPTIONS {
    FOS_OVERWRITEPROMPT 	= 0x00000002,
    FOS_STRICTFILETYPES 	= 0x00000004,
    FOS_NOCHANGEDIR 		= 0x00000008,
    FOS_PICKFOLDERS 		= 0x00000020,
    FOS_FORCEFILESYSTEM 	= 0x00000040,
    FOS_ALLNONSTORAGEITEMS 	= 0x00000080,
    FOS_NOVALIDATE 			= 0x00000100,
    FOS_ALLOWMULTISELECT 	= 0x00000200,
    FOS_PATHMUSTEXIST 		= 0x00000800,
    FOS_FILEMUSTEXIST 		= 0x00001000,
    FOS_CREATEPROMPT 		= 0x00002000,
    FOS_SHAREAWARE 			= 0x00004000,
    FOS_NOREADONLYRETURN 	= 0x00008000,
    FOS_NOTESTFILECREATE 	= 0x00010000,
    FOS_HIDEMRUPLACES 		= 0x00020000,
    FOS_HIDEPINNEDPLACES 	= 0x00040000,
    FOS_NODEREFERENCELINKS 	= 0x00100000,
    FOS_DONTADDTORECENT 	= 0x02000000,
    FOS_FORCESHOWHIDDEN 	= 0x10000000,
    FOS_DEFAULTNOMINIMODE 	= 0x20000000,
    FOS_FORCEPREVIEWPANEON 	= 0x40000000
};
typedef DWORD FILEOPENDIALOGOPTIONS;

enum _SIGDN {
    SIGDN_NORMALDISPLAY 				= 0x0,
    SIGDN_PARENTRELATIVEPARSING 		= 0x80018001,
    SIGDN_DESKTOPABSOLUTEPARSING 		= 0x80028000,
    SIGDN_PARENTRELATIVEEDITING 		= 0x80031001,
    SIGDN_DESKTOPABSOLUTEEDITING 		= 0x8004c000,
    SIGDN_FILESYSPATH 					= 0x80058000,
    SIGDN_URL 							= 0x80068000,
    SIGDN_PARENTRELATIVEFORADDRESSBAR 	= 0x8007c001,
    SIGDN_PARENTRELATIVE 				= 0x80080001,
    SIGDN_PARENTRELATIVEFORUI 			= 0x80094001
};
typedef DWORD SIGDN;

enum _SICHINTF {
    SICHINT_DISPLAY 						= 0x0,
    SICHINT_ALLFIELDS 						= 0x80000000,
    SICHINT_CANONICAL 						= 0x10000000,
    SICHINT_TEST_FILESYSPATH_IF_NOT_EQUAL 	= 0x20000000
};
typedef DWORD SICHINTF;

enum _SHCONTF {
    SHCONTF_CHECKING_FOR_CHILDREN 	= 0x00010,
    SHCONTF_FOLDERS 				= 0x00020,
    SHCONTF_NONFOLDERS 				= 0x00040,
    SHCONTF_INCLUDEHIDDEN 			= 0x00080,
    SHCONTF_INIT_ON_FIRST_NEXT 		= 0x00100,
    SHCONTF_NETPRINTERSRCH 			= 0x00200,
    SHCONTF_SHAREABLE 				= 0x00400,
    SHCONTF_STORAGE 				= 0x00800,
    SHCONTF_NAVIGATION_ENUM 		= 0x01000,
    SHCONTF_FASTITEMS 				= 0x02000,
    SHCONTF_FLATLIST 				= 0x04000,
    SHCONTF_ENABLE_ASYNC 			= 0x08000,
    SHCONTF_INCLUDESUPERHIDDEN 		= 0x10000
};
typedef DWORD SHCONTF;

typedef ULONG SFGAOF, GETPROPERTYSTOREFLAGS, SIATTRIBFLAGS;
typedef PVOID REFPROPERTYKEY;

struct COMDLG_FILTERSPEC
{
	LPCWSTR name, spec;
};

typedef void IFileDialogEvents, IPropertyStore, IPropertyDescriptionList, IFileOperationProgressSink, IBindCtz, IEnumShellItems; // not used

static GUID IID_IShellItem = { 0x43826d1e, 0xe718, 0x42ee, {0xbc,0x55,0xa1,0xe2,0x61,0xc3,0x7b,0xfe} };
class IShellItem: public IUnknown
{
	public:
    virtual HRESULT __stdcall BindToHandler(IBindCtx *pbc, REFGUID bhid, REFIID riid, void **ppv) = 0;
    virtual HRESULT __stdcall GetParent(IShellItem **ppsi) = 0;
    virtual HRESULT __stdcall GetDisplayName(SIGDN sigdnName, LPWSTR *ppszName) = 0;
    virtual HRESULT __stdcall GetAttributes(SFGAOF sfgaoMask, SFGAOF *psfgaoAttribs) = 0;
    virtual HRESULT __stdcall Compare(IShellItem *psi, SICHINTF hint, int *piOrder) = 0;
};

static GUID IID_IShellItemFilter = { 0x2659b475, 0xeeb8, 0x48b7, {0x8f,0x07,0xb3,0x78,0x81,0x0f,0x48,0xcf} };
class IShellItemFilter: public IUnknown
{
	public:
    virtual HRESULT __stdcall IncludeItem(IShellItem *psi) = 0;
    virtual HRESULT __stdcall GetEnumFlagsForItem(IShellItem *psi, SHCONTF *pgrfFlags) = 0;
};

static GUID IID_IShellItemArray = { 0xb63ea76d, 0x1f85, 0x456f, {0xa1,0x9c,0x48,0x15,0x9e,0xfa,0x85,0x8b} };
class IShellItemArray: public IUnknown
{
	public:
    virtual HRESULT __stdcall BindToHandler(IBindCtx *pbc, REFGUID bhid, REFIID riid, void **ppvOut) = 0;
    virtual HRESULT __stdcall GetPropertyStore(GETPROPERTYSTOREFLAGS flags, REFIID riid, void **ppv) = 0;
    virtual HRESULT __stdcall GetPropertyDescriptionList(REFPROPERTYKEY keyType, REFIID riid, void **ppv) = 0;
    virtual HRESULT __stdcall GetAttributes(SIATTRIBFLAGS AttribFlags, SFGAOF sfgaoMask, SFGAOF *psfgaoAttribs) = 0;
    virtual HRESULT __stdcall GetCount(DWORD *pdwNumItems) = 0;
    virtual HRESULT __stdcall GetItemAt(DWORD dwIndex, IShellItem **ppsi) = 0;
    virtual HRESULT __stdcall EnumItems(IEnumShellItems **ppenumShellItems) = 0;
};

static GUID IID_IModalWindow = { 0xb4db1657, 0x70d7, 0x485e, {0x8e,0x3e,0x6f,0xcb,0x5a,0x5c,0x18,0x02} };
class IModalWindow: public IUnknown
{
	public:
	virtual HRESULT __stdcall Show(HWND owner) = 0;
};

static GUID IID_IFileDialog = { 0x42f85136, 0xdb7e, 0x439c, {0x85,0xf1,0xe4,0x07,0x5d,0x13,0x5f,0xc8} };
class IFileDialog: public IModalWindow
{
	public:
    virtual HRESULT __stdcall SetFileTypes(UINT cFileTypes, const COMDLG_FILTERSPEC *rgFilterSpec) = 0;
    virtual HRESULT __stdcall SetFileTypeIndex(UINT iFileType) = 0;
    virtual HRESULT __stdcall GetFileTypeIndex(UINT *piFileType) = 0;
    virtual HRESULT __stdcall Advise(IFileDialogEvents *pfde, DWORD *pdwCookie) = 0;
    virtual HRESULT __stdcall Unadvise(DWORD dwCookie) = 0;
    virtual HRESULT __stdcall SetOptions(FILEOPENDIALOGOPTIONS fos) = 0;
    virtual HRESULT __stdcall GetOptions(FILEOPENDIALOGOPTIONS *pfos) = 0;
    virtual HRESULT __stdcall SetDefaultFolder(IShellItem *psi) = 0;
    virtual HRESULT __stdcall SetFolder(IShellItem *psi) = 0;
    virtual HRESULT __stdcall GetFolder(IShellItem **ppsi) = 0;
    virtual HRESULT __stdcall GetCurrentSelection(IShellItem **ppsi) = 0;
    virtual HRESULT __stdcall SetFileName(LPCWSTR pszName) = 0;
    virtual HRESULT __stdcall GetFileName(LPWSTR *pszName) = 0;
    virtual HRESULT __stdcall SetTitle(LPCWSTR pszTitle) = 0;
    virtual HRESULT __stdcall SetOkButtonLabel(LPCWSTR pszText) = 0;
    virtual HRESULT __stdcall SetFileNameLabel(LPCWSTR pszLabel) = 0;
    virtual HRESULT __stdcall GetResult(IShellItem **ppsi) = 0;
    virtual HRESULT __stdcall AddPlace(IShellItem *psi, FDAP fdap) = 0;
    virtual HRESULT __stdcall SetDefaultExtension(LPCWSTR pszDefaultExtension) = 0;
    virtual HRESULT __stdcall Close(HRESULT hr) = 0;
    virtual HRESULT __stdcall SetClientGuid(REFGUID guid) = 0;
    virtual HRESULT __stdcall ClearClientData() = 0;
    virtual HRESULT __stdcall SetFilter(IShellItemFilter *pFilter) = 0;
};

static GUID IID_IFileOpenDialog = { 0xd57c7288, 0xd4ad, 0x4768, {0xbe,0x02,0x9d,0x96,0x95,0x32,0xd9,0x60} };
class IFileOpenDialog: public IFileDialog
{
	public:
    virtual HRESULT __stdcall GetResults(IShellItemArray **ppenum) = 0;
    virtual HRESULT __stdcall GetSelectedItems(IShellItemArray **ppsai) = 0;
};

static GUID IID_IFileSaveDialog = { 0x84bccd23, 0x5fde, 0x4cdb, {0xae,0xa4,0xaf,0x64,0xb8,0x3d,0x78,0xab} };
class IFileSaveDialog: public IFileDialog
{
	public:
    virtual HRESULT __stdcall SetSaveAsItem(IShellItem *psi) = 0;
    virtual HRESULT __stdcall SetProperties(IPropertyStore *pStore) = 0;
    virtual HRESULT __stdcall SetCollectedProperties(IPropertyDescriptionList *pList, BOOL fAppendDefault) = 0;
    virtual HRESULT __stdcall GetProperties(IPropertyStore **ppStore) = 0;
    virtual HRESULT __stdcall ApplyProperties(IShellItem *psi, IPropertyStore *pStore, HWND hwnd, IFileOperationProgressSink *pSink) = 0;
};

// CLSIDs
static GUID CLSID_ShellItem = { 0x9ac9fbe1, 0xe0a2, 0x4ad6, {0xb4,0xee,0xe2,0x12,0x01,0x3e,0xa9,0x17} };
static GUID CLSID_FileOpenDialog = { 0xdc1c5a9c, 0xe88a, 0x4dde, {0xa5,0xa1,0x60,0xf8,0x2a,0x20,0xae,0xf7} };
static GUID CLSID_FileSaveDialog = { 0xc0b4e2f3, 0xba21, 0x4773, {0x8d,0xba,0x33,0x5e,0xc9,0x46,0xeb,0x8b} };

#endif

CFileDialog::CFileDialog(int dialog_type)
{
	Multiselect 	= false;
    ShowReadOnly 	= false;
    FileMustExist 	= false;
    PathMustExist 	= false;
    OverwritePrompt = false;
    NoChangeDir 	= false;
    NoPlacesBar 	= false;

    if(dialog_type == fdOpen)
    	Caption = "Open";
    if(dialog_type == fdSave)
    	Caption = "Save";

    DefaultExt = "";
    DefaultDir = "";
    CurrentFile = "";
    CurrentDir	= "";

	Type 			= dialog_type;
	DefaultFilter	= 0;
    CurrentFilter	= -1;
}

void CFileDialog::SetFilters(const char *filters)
{
	Filters.clear();
    
	const char *p = filters;
    while(p[0])
    {
    	const char *desc = p;
        p = strchr(desc, 0) + 1;
        const char *mask = p;
        p = strchr(mask, 0) + 1;

        AddFilter(mask, desc);
    }
}

bool CFileDialog::ShowModal(HWND owner)
{
	Results.clear();

    if(DefaultExt.length())
    {
    	if(DefaultExt.length() >= 2 && DefaultExt[0] == '*' && DefaultExt[1] == '.')
        	DefaultExt.erase(0, 2);
        else if(DefaultExt.length() >= 1 && DefaultExt[0] == '.')
        	DefaultExt.erase(0, 1);
    }

	int ret = -1;
	if((GetVersion() & 0xFF) >= 6) // if NT6 or greater
	{
    	ret = ShowVista(owner);
		if(ret < 0)
        {
        	Log("Vista dialog failed :-(");
            ret = ShowOld(owner);
        }
    }
    else
    	ret = ShowOld(owner);

    return ret > 0;
}

int CFileDialog::ShowOld(HWND owner)
{
	char result[512*256];
    strcpy(result, CurrentFile.c_str());
	OPENFILENAME ofn = {0};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = owner;
	ofn.lpstrFile = result;
	ofn.nMaxFile = sizeof(result);
	ofn.lpstrInitialDir = DefaultDir.size() ? DefaultDir.c_str() : NULL;
	ofn.lpstrTitle = Caption.size() ? Caption.c_str() : NULL;

	DWORD flags = 0;

	if(Multiselect)
		flags |= OFN_EXPLORER|OFN_ALLOWMULTISELECT;
	if(!ShowReadOnly)
		flags |= OFN_HIDEREADONLY;
    if(PathMustExist)
        flags |= OFN_PATHMUSTEXIST;
    if(FileMustExist)
        flags |= OFN_FILEMUSTEXIST;
    if(OverwritePrompt)
        flags |= OFN_OVERWRITEPROMPT;
    if(NoChangeDir)
        flags |= OFN_NOCHANGEDIR;

    ofn.Flags = flags;
    ofn.lpstrDefExt = DefaultExt.size() ? DefaultExt.c_str() : NULL;

    if(NoPlacesBar)
    	ofn.FlagsEx = OFN_EX_NOPLACESBAR;

    char flt[1024] = "";
    if(Filters.size())
    {
    	char *p = flt;
    	for(size_t i = 0; i < Filters.size(); i++)
    	{
        	SFilter &f = Filters[i];
			size_t len;

            len = f.desc.length();
            memcpy(p, f.desc.c_str(), len+1);
            p += len + 1;
			len = f.mask.length();
            memcpy(p, f.mask.c_str(), len+1);
            p += len + 1;
		}
		*p = '\0';
		ofn.lpstrFilter = flt;
	}

    if(CurrentFilter != -1)
    	ofn.nFilterIndex = CurrentFilter + 1;
    else
    	ofn.nFilterIndex = DefaultFilter + 1;

    if(Type == fdOpen)
    {
		if(GetOpenFileName(&ofn) == FALSE)
		{
			if(CommDlgExtendedError() == FNERR_BUFFERTOOSMALL)
				SetLastError(DWORD(ERROR_INSUFFICIENT_BUFFER));
			return 0;
		}
	}
	else
	{
		if(GetSaveFileName(&ofn) == FALSE)
		{
			if(CommDlgExtendedError() == FNERR_BUFFERTOOSMALL)
				SetLastError(DWORD(ERROR_INSUFFICIENT_BUFFER));
            return 0;
        }
    }
    // if multiselect and selected more than one file
    if(Type == fdOpen && Multiselect && result[strlen(result)+1] != '\0')
    {
    	char *p = result;

        char dir[512];
        strcpy(dir, p);

        p = strchr(p, 0) + 1;
        while(p[0])
        {
        	Results.push_back(xr_string(dir) + "\\" + p);
            p = strchr(p, 0) + 1;
        }
    }
    else
    	Results.push_back(result);

    CurrentFilter = ofn.nFilterIndex - 1;
    CurrentFile = Results[0];
    char drive[_MAX_DRIVE], dir[_MAX_DIR];
    _splitpath(Results[0].c_str(), drive, dir, NULL, NULL);
    CurrentDir = xr_string(drive) + dir;

    return 1;
}

int CFileDialog::ShowVista(HWND owner)
{
    // convert to full path
	if(DefaultDir.length() && (DefaultDir.length() < 2 || DefaultDir.at(1) != ':'))
    {
    	char cd[512];
        GetCurrentDirectory(sizeof(cd), cd);
        DefaultDir = xr_string(cd) + DefaultDir;
    }
    if(CurrentDir.length() && (CurrentDir.length() < 2 || CurrentDir.at(1) != ':'))
    {
    	char cd[512];
        GetCurrentDirectory(sizeof(cd), cd);
        CurrentDir = xr_string(cd) + CurrentDir;
    }
    
    if(pSHCreateItemFromParsingName == NULL)
    {
		HMODULE hShell32 = GetModuleHandle("SHELL32.DLL");
        R_ASSERT(hShell32);
        pSHCreateItemFromParsingName = (LPFNSHCREATEITEMFROMPARSINGNAMEPROC)GetProcAddress(hShell32, "SHCreateItemFromParsingName");
        R_ASSERT(pSHCreateItemFromParsingName);
    }

    IFileDialog *dlg = NULL;
    IFileOpenDialog *odlg = NULL;
    IFileSaveDialog *sdlg = NULL;

    int ret = -1;

    do
    {
		HRESULT hr;

		if(Type == fdOpen)
        {
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileOpenDialog, (void**)&odlg);
            if(FAILED(hr)) break;

            dlg = odlg; // it's okay??
        }
        else
        {
            hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_IFileSaveDialog, (void**)&sdlg);
            if(FAILED(hr)) break;

			dlg = sdlg;
        }

        DWORD flags = 0;

        if(Multiselect)
            flags |= FOS_ALLOWMULTISELECT;
        if(PathMustExist)
            flags |= FOS_PATHMUSTEXIST;
        if(FileMustExist)
            flags |= FOS_FILEMUSTEXIST;
        if(NoChangeDir)
            flags |= FOS_NOCHANGEDIR;
        if(OverwritePrompt)
            flags |= FOS_OVERWRITEPROMPT;

        hr = dlg->SetOptions(flags);
        if(FAILED(hr)) break;

        WCHAR wcaption[512];
        MultiByteToWideChar(CP_ACP, 0, Caption.c_str(), -1, wcaption, 512);
        hr = dlg->SetTitle(wcaption);
        if(FAILED(hr)) break;

        WCHAR wdefaultdir[512];
        MultiByteToWideChar(CP_ACP, 0, DefaultDir.c_str(), -1, wdefaultdir, 512);

        IShellItem *si_defdir;
        hr = pSHCreateItemFromParsingName(wdefaultdir, NULL, IID_IShellItem, (void**)&si_defdir);
        if(!FAILED(hr))
        {
        	hr = dlg->SetDefaultFolder(si_defdir);
        	si_defdir->Release();
        	if(FAILED(hr)) break;
		}

        if(CurrentDir.size())
        {
        	WCHAR wcurrentdir[512];
            MultiByteToWideChar(CP_ACP, 0, CurrentDir.c_str(), -1, wcurrentdir, 512);
            IShellItem *si_cd;
            hr = pSHCreateItemFromParsingName(wcurrentdir, NULL, IID_IShellItem, (void**)&si_cd);
            if(!FAILED(hr))
            {
            	hr = dlg->SetFolder(si_cd);
                si_cd->Release();
                if(FAILED(hr)) break;
            }
        }

        WCHAR wdefext[512];
        MultiByteToWideChar(CP_ACP, 0, DefaultExt.c_str(), -1, wdefext, 512);
        hr = dlg->SetDefaultExtension(wdefext);
        if(FAILED(hr)) break;

        if(Filters.size())
        {
        	size_t filter_cnt = Filters.size();
            COMDLG_FILTERSPEC *specs = xr_alloc<COMDLG_FILTERSPEC>(filter_cnt);

            for(size_t i = 0; i < filter_cnt; i++)
            {
                size_t len;
                WCHAR *name, *spec;

                len = Filters[i].desc.length();
                name = xr_alloc<WCHAR>(len+1);
                MultiByteToWideChar(CP_ACP, 0, Filters[i].desc.c_str(), -1, name, len+1);

                len = Filters[i].mask.length();
                spec = xr_alloc<WCHAR>(len+1);
                MultiByteToWideChar(CP_ACP, 0, Filters[i].mask.c_str(), -1, spec, len+1);

                specs[i].name = name;
                specs[i].spec = spec;
            }

            hr = dlg->SetFileTypes(filter_cnt, specs);

            for(i = 0; i < filter_cnt; i++)
            {
				xr_free(specs[i].name);
                xr_free(specs[i].spec);
			}

            xr_free(specs);
            if(FAILED(hr)) break;
        }

        if(CurrentFilter != -1)
        	/*hr =*/ dlg->SetFileTypeIndex(CurrentFilter + 1);
        else
        	/*hr =*/ dlg->SetFileTypeIndex(DefaultFilter + 1);

        WCHAR wcurfile[512];
        MultiByteToWideChar(CP_ACP, 0, CurrentFile.c_str(), -1, wcurfile, 512);

        /*hr =*/ dlg->SetFileName(wcurfile);

        if(dlg->Show(owner) != S_OK)
        {
        	ret = 0;
            break;
        }

        if(Type == fdOpen && Multiselect)
        {
            IShellItemArray *arr;
            hr = odlg->GetResults(&arr);
            if(FAILED(hr)) break;

            ULONG count;
            hr = arr->GetCount(&count);
            if(FAILED(hr)) { arr->Release(); break; }

            for(ULONG i = 0; i < count; i++)
            {
                IShellItem *si;
                hr = arr->GetItemAt(i, &si);
                if(FAILED(hr)) { arr->Release(); goto fail; }

                WCHAR *pfn;
                hr = si->GetDisplayName(SIGDN_FILESYSPATH, &pfn);
                if(FAILED(hr)) { arr->Release(); si->Release(); goto fail; }

                xr_string fp;
                fp.resize(wcslen(pfn));
                WideCharToMultiByte(CP_ACP, 0, pfn, -1, &*fp.begin(), fp.size(), NULL, NULL);
                Results.push_back(fp);
                CoTaskMemFree(pfn);

                si->Release();
            }

            arr->Release();
        }
        else
        {
            IShellItem *si_result;
            hr = dlg->GetResult(&si_result);
            if(FAILED(hr)) break;

            WCHAR *pfn;
            hr = si_result->GetDisplayName(SIGDN_FILESYSPATH, &pfn);
            si_result->Release();
            if(FAILED(hr)) break;

            xr_string fp;
            fp.resize(wcslen(pfn));
            WideCharToMultiByte(CP_ACP, 0, pfn, -1, &*fp.begin(), fp.size(), NULL, NULL);
            Results.push_back(fp);
            CoTaskMemFree(pfn);
        }

        hr = dlg->GetFileTypeIndex((UINT*)&CurrentFilter);
        if(FAILED(hr)) CurrentFilter = -1;

        WCHAR *wcfn;
        hr = dlg->GetFileName(&wcfn);
        if(!FAILED(hr))
        {
        	char cfn[512];
            WideCharToMultiByte(CP_ACP, 0, wcfn, -1, cfn, sizeof(cfn), NULL, NULL);
            CurrentFile = cfn;
        }

        IShellItem *si_cd;
        hr = dlg->GetFolder(&si_cd);
        if(!FAILED(hr))
        {
        	WCHAR *wcd;
        	char cd[512];
            hr = si_cd->GetDisplayName(SIGDN_FILESYSPATH, &wcd);
            if(!FAILED(hr))
            {
            	WideCharToMultiByte(CP_ACP, 0, wcd, -1, cd, 512, NULL, NULL);
                CurrentDir = cd;
            }
            si_cd->Release();
        }

        ret = 1;
    }
    while(0);
    fail:

    if(odlg) odlg->Release();
    if(sdlg) sdlg->Release();

    return ret;
}
