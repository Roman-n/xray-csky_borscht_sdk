#include "stdafx.h"
#include "builder_types.h"

std::unique_ptr<TApplication> Application;

void TApplication::ProcessMessages() { }

AnsiString ExtractFileExt(const AnsiString& fileName)
{
    R_ASSERT(false);
    return {};
}

AnsiString Trim(const AnsiString& s)
{
    R_ASSERT(false);
    return {};
}

AnsiString ChangeFileExt(const AnsiString& fileName, const AnsiString& newExt)
{
    R_ASSERT(false);
    return {};
}

AnsiString LowerCase(const AnsiString& s)
{
    R_ASSERT(false);
    return {};
}

int MessageDlg(const AnsiString& Msg, TMsgDlgType DlgType, TMsgDlgButtons Buttons, int HelpCtx)
{
    R_ASSERT(false);
    return 0;
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