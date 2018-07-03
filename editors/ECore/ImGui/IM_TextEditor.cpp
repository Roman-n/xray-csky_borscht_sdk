#include "stdafx.h"
#pragma hdrstop

#include "imgui.h"
#include "IM_TextEditor.h"
#include "../Editor/UI_Main.h"

#pragma package(smart_init)

static const u32 text_reserve = 4096; // 4kb

void IM_TextEditor::SetupUserButtons(LPCSTR user_buttons, va_list v)
{
    u32 cnt = _GetItemCount(user_buttons, ',');
    for(u32 i = 0; i < cnt; i++)
    {
		char str[256];
        _GetItem(user_buttons, i, str);

		m_user_buttons.push_back(
        	std::make_pair(xr_string(str), va_arg(v, IM_TECallback))
        );
    }
}

IM_TextEditor::IM_TextEditor(const xr_string& caption, const xr_string& initial_text, IM_TECallback on_ok, IM_TECallback on_cancel, IM_TECallback on_close, LPCSTR user_buttons, ...)
	: m_caption(caption),
	  m_on_ok(on_ok),
      m_on_cancel(on_cancel),
      m_on_close(on_close),
      m_actions(NULL)
{
    SetText(initial_text);

    if(user_buttons)
    {
    	va_list v;
    	va_start(v, user_buttons);
		SetupUserButtons(user_buttons, v);
    	va_end(v);
    }
}

IM_TextEditor::IM_TextEditor(const xr_string& caption, const xr_string& initial_text, IM_TEActions* actions, LPCSTR user_buttons, ...)
	: m_caption(caption),
      m_on_ok(NULL),
      m_on_cancel(NULL),
      m_on_close(NULL),
      m_actions(actions)
{
	SetText(initial_text);

    if(user_buttons)
    {
    	va_list v;
    	va_start(v, user_buttons);
		SetupUserButtons(user_buttons, v);
    	va_end(v);
    }
}

IM_TextEditor::~IM_TextEditor()
{
}

void IM_TextEditor::Close()
{
	if(m_on_close)
    	m_on_close(this);
	if(m_actions)
    	m_actions->OnClose(this);

	UI->RemoveIMWindow(this);
    xr_delete(m_actions);
    xr_delete(const_cast<IM_TextEditor*>(this));
}

xr_string IM_TextEditor::GetText()
{
	return xr_string(&*m_text.begin());
}

void IM_TextEditor::SetText(const xr_string& new_text)
{
	if(m_text.size() < new_text.length()+1+text_reserve)
    	m_text.resize(new_text.length()+1+text_reserve*2);

    memcpy(&*m_text.begin(), new_text.c_str(), new_text.length()+1);
}

void IM_TextEditor::Render()
{
	bool open = true;

    ImGui::SetNextWindowSize(ImVec2(500,350), ImGuiCond_FirstUseEver);

    ImGui::OpenPopup(m_caption.c_str()); // this is fine, i hope
	if(!ImGui::BeginPopupModal(m_caption.c_str(), &open))
    {
    	Close();
        return;
    }

    ImGui::Columns(3, NULL, false);

    if(ImGui::Button("OK"))
    {
    	if(m_on_ok)
        	m_on_ok(this);
        if(m_actions)
        	m_actions->OnOK(this);

		open = false;
	}
    ImGui::SameLine();
    if(ImGui::Button("Cancel"))
    {
    	if(m_on_cancel)
        	m_on_cancel(this);
        if(m_actions)
        	m_actions->OnCancel(this);

        open = false;
    }

    ImGui::NextColumn();

    for(u32 i = 0; i < m_user_buttons.size(); i++)
    {
    	ImGui::PushID(4444 + i);
    	if(ImGui::Button(m_user_buttons[i].first.c_str()))
        	m_user_buttons[i].second(this);
        ImGui::PopID();

        ImGui::SameLine();
    }

    ImGui::NextColumn();

    if(ImGui::Button("Load"))
    	;
    ImGui::SameLine();
    if(ImGui::Button("Save"))
    	;
    ImGui::SameLine();
    if(ImGui::Button("Clear"))
    	m_text[0] = '\0';

    ImGui::Columns(1);

    ImGui::Separator();
    if(ImGui::InputTextMultiline("##textarea", &*m_text.begin(), m_text.size(),
       ImVec2(-1,-1), ImGuiInputTextFlags_AllowTabInput))
    {
    	if(m_text.size() < strlen(&*m_text.begin())+1+text_reserve)
        	m_text.resize(m_text.size()+text_reserve*2);
    }

    ImGui::EndPopup();

    if(!open)
    	Close();
}

//
IM_TEActions::~IM_TEActions()
{
}

void IM_TEActions::OnOK(IM_TextEditor* editor)
{
}

void IM_TEActions::OnCancel(IM_TextEditor* editor)
{
}

void IM_TEActions::OnClose(IM_TextEditor* editor)
{
}