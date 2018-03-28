//---------------------------------------------------------------------------

#ifndef IM_TextEditorH
#define IM_TextEditorH

#include "IM_Window.h"
//---------------------------------------------------------------------------

class IM_TextEditor : public IM_Window
{
	public:
    enum EditorStatus
    {
    	esOK,
        esCancel,
        esActive,
        esInactive
    };

	xr_vector<char> buffer;
    EditorStatus status;

    public:
    IM_TextEditor(size_t bufsize = 512*1024);

    void SetText(const char* text);
    const char* GetText();
    EditorStatus Status() { return status; }
    virtual void Render();
}

#endif
