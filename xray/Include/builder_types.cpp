#include "stdafx.h"
#include "builder_types.h"

std::unique_ptr<TApplication> Application;

void TApplication::ProcessMessages()
{
	MSG msg;
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

AnsiString ExtractFileExt(const AnsiString& fileName)
{
	string_path ext;
	_splitpath	(fileName.c_str(),0,0,0,ext);
    return ext;
}

AnsiString Trim(const AnsiString& s)
{
    auto b = std::find_if(s.begin(), s.end(), [](char c) { return !isspace(c); });
    auto e = std::find_if(s.rbegin(), s.rend(), [](char c) { return !isspace(c); }).base();
    return AnsiString(b,e);
}

AnsiString ChangeFileExt(const AnsiString& fileName, const AnsiString& newExt)
{
    return EFS.ChangeFileExt(fileName.c_str(), newExt.c_str()).c_str();
}

AnsiString LowerCase(const AnsiString& s)
{
    AnsiString result(s);
    std::for_each(result.begin(), result.end(), [](char c) { return tolower(c); });
    return result;
}

int MessageDlg(const AnsiString& Msg, TMsgDlgType DlgType, TMsgDlgButtons Buttons, int HelpCtx)
{
    UINT dlgTypes[] = {MB_ICONWARNING, MB_ICONERROR, MB_ICONINFORMATION, MB_ICONQUESTION, 0};
    UINT buttonType = 0;
    if (Buttons.Contains(mbAbort) && Buttons.Contains(mbRetry) && Buttons.Contains(mbIgnore))
        buttonType = MB_ABORTRETRYIGNORE;
    else if (Buttons.Contains(mbOK) && Buttons.Contains(mbCancel))
        buttonType = MB_OKCANCEL;
    else if (Buttons.Contains(mbOK))
        buttonType = MB_OK;
    else if (Buttons.Contains(mbRetry) && Buttons.Contains(mbCancel))
        buttonType = MB_RETRYCANCEL;
    else if (Buttons.Contains(mbYes) && Buttons.Contains(mbNo))
        buttonType = MB_YESNO;
    else if (Buttons.Contains(mbYes) && Buttons.Contains(mbNo) && Buttons.Contains(mbCancel))
        buttonType = MB_YESNOCANCEL;
    else
        R_ASSERT(!"Unknown MessageDlg button type!");
    if (Buttons.Contains(mbHelp))
        buttonType |= MB_HELP;
    int result = MessageBox(0, Msg.c_str(), "", dlgTypes[DlgType] | buttonType);
    switch (result) {
    case IDABORT:
        return mrAbort;//3
    case IDCANCEL:
        return mrCancel;// 2
    //case IDCONTINUE:
    //    return mrContinue;// 11
    case IDIGNORE:
        return mrIgnore;// 5
    case IDNO:
        return mrNo;// 7
    case IDOK:
        return mrOK;// 1
    case IDRETRY:
        return mrRetry;// 4
    //case IDTRYAGAIN:
    //    return mrTryAgain;// 10
    case IDYES:
        return mrYes;// 6
    }
    R_ASSERT(false);
    return mrNone;
}

bool FileExists(const AnsiString& fileName)
{
    DWORD dwAttrib = GetFileAttributes(fileName.c_str());
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

AnsiString ExtractFileName(const AnsiString& fileName)
{
    R_ASSERT(false);
    return 0;
}

POINT TWinControl::ScreenToClient(POINT pt)
{
    R_ASSERT(Handle);
    ::ScreenToClient(Handle, &pt);
    return pt;
}