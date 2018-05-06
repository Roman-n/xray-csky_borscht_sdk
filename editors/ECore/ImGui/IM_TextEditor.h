#ifndef IM_TextEditorH
#define IM_TextEditorH

#include "IM_Window.h"

typedef fastdelegate::FastDelegate1<class IM_TextEditor*> IM_TECallback;

ECORE_API class IM_TextEditor : public IM_Window
{
	public:
    xr_string	  	m_caption;
    xr_vector<char>	m_text;
	IM_TECallback	m_on_ok;
    IM_TECallback	m_on_cancel;

    xr_vector<std::pair<xr_string,IM_TECallback> > m_user_buttons;

	public:
    IM_TextEditor(const xr_string& caption, const xr_string& initial_text = "", u32 desired_text_len = 0, IM_TECallback on_ok = NULL, IM_TECallback on_cancel = NULL, LPCSTR user_buttons = NULL, ...);
    ~IM_TextEditor();

    void Close();
    xr_string GetText();
    void SetText(const xr_string& new_text);
    virtual void Render();
};

#endif
