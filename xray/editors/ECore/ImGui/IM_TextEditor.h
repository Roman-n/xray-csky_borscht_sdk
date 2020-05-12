#ifndef IM_TextEditorH
#define IM_TextEditorH

#include "IM_Window.h"

typedef fastdelegate::FastDelegate<void(class IM_TextEditor*)> IM_TECallback;
struct IM_TEActions;

class ECORE_API IM_TextEditor : public IM_Window
{
	public:
    xr_string	  	m_caption;
    xr_vector<char>	m_text;

    xr_vector<std::pair<xr_string,IM_TECallback> > m_user_buttons;

    // delegates
    IM_TECallback	m_on_ok;
    IM_TECallback	m_on_cancel;
    IM_TECallback	m_on_close;
    // or this
    IM_TEActions* 	m_actions;

    public:
    void SetupUserButtons(LPCSTR user_buttons, va_list v);

	public:
    IM_TextEditor(const xr_string& caption, const xr_string& initial_text = "",
    	IM_TECallback on_ok = NULL, IM_TECallback on_cancel = NULL, IM_TECallback on_close = NULL,
        LPCSTR user_buttons = NULL, ...);
    IM_TextEditor(const xr_string& caption, const xr_string& initial_text = "",
    	IM_TEActions* actions = NULL, LPCSTR user_buttons = NULL, ...);

    ~IM_TextEditor();

    void Close();
    xr_string GetText();
    void SetText(const xr_string& new_text);
    virtual void Render();
};

struct ECORE_API IM_TEActions
{
	virtual ~IM_TEActions();

    virtual void OnOK(IM_TextEditor* editor);
    virtual void OnCancel(IM_TextEditor* editor);
    virtual void OnClose(IM_TextEditor* editor);
};

#endif
