#pragma once

#include <memory>
#include <string>

// Типы из Builder С++

enum TMsgDlgType { mtWarning, mtError, mtInformation, mtConfirmation, mtCustom };

enum TMsgDlgBtn {
    mbYes,
    mbNo,
    mbOK,
    mbCancel,
    mbAbort,
    mbRetry,
    mbIgnore,
    mbAll,
    mbNoToAll,
    mbYesToAll,
    mbHelp,
    mbClose
};

template <class T> struct VclFlags {
    VclFlags<T>& operator<<(T flag)
    {
        value |= (1 << flag);
        return *this;
    }
    VclFlags<T>& operator>>(T flag)
    {
        value &= ~(1 << flag);
        return *this;
    }
    bool operator==(VclFlags<T> other) const { return value == other.value; }
    void Clear() { value = 0; }
    bool Contains(T flag) { return value & flag; }

    unsigned int value = 0;
};

using TMsgDlgButtons = VclFlags<TMsgDlgBtn>;

enum _TShiftState { ssShift, ssAlt, ssCtrl, ssLeft, ssRight, ssMiddle, ssDouble };
using TShiftState = VclFlags<_TShiftState>;

const int mrNone = 0;
const int mrYes = IDOK;
const int mrCancel = IDCANCEL;
const int mrNo = IDNO;

using AnsiString = std::string;

using TColor = unsigned int;

int MessageDlg(const AnsiString& Msg, TMsgDlgType DlgType, TMsgDlgButtons Buttons, int HelpCtx);

class TObject
{
};

class TPersistent : public TObject
{
};

class TComponent : public TPersistent
{
};

class TControl : public TComponent
{
};

class TWinControl : public TControl
{
public:
    HWND Handle = 0;

    POINT ScreenToClient(POINT pt);
};

class TCustomControl : public TWinControl
{
};

class TPanel
{
};

class THintWindow
{
};

class TForm
{
};

class TApplication
{
public:
    void ProcessMessages();
};
extern std::unique_ptr<TApplication> Application;

class TCanvas : public TPersistent
{
public:
    HDC Handle = 0;
};

class TMxPanel
{
public:
    int Width = 0;
    int Height = 0;
    TCanvas* Canvas = 0;
};

AnsiString ExtractFileExt(const AnsiString& fileName);
AnsiString Trim(const AnsiString& s);
AnsiString ChangeFileExt(const AnsiString& fileName, const AnsiString& newExt);
AnsiString LowerCase(const AnsiString& s);
bool FileExists(const AnsiString& fileName);
AnsiString ExtractFileName(const AnsiString& fileName);
