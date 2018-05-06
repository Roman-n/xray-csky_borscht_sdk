#include "stdafx.h"
#pragma hdrstop

#include "imgui.h"
#include "IM_TextEditor.h"
#include "../Editor/UI_Main.h"

#pragma package(smart_init)

IM_TextEditor::IM_TextEditor(const xr_string& caption, const xr_string& initial_text, u32 desired_text_len, IM_TECallback on_ok, IM_TECallback on_cancel, LPCSTR user_buttons, ...)
	: m_caption(caption),
	  m_on_ok(on_ok),
      m_on_cancel(on_cancel)
{
	if(desired_text_len == 0)
    	desired_text_len = 512*1024;

	m_text.resize(desired_text_len);
    SetText(initial_text);

    va_list v;
    va_start(v, user_buttons);

    u32 cnt = _GetItemCount(user_buttons, ',');
    for(u32 i = 0; i < cnt; i++)
    {
		char str[256];
        _GetItem(user_buttons, i, str);

		m_user_buttons.push_back(
        	std::make_pair(xr_string(str), va_arg(v, IM_TECallback))
        );
    }

    va_end(v);
}

IM_TextEditor::~IM_TextEditor()
{
}

void IM_TextEditor::Close()
{
	UI->RemoveIMWindow(this);
    xr_delete(const_cast<IM_TextEditor*>(this));
}

xr_string IM_TextEditor::GetText()
{
	return xr_string(&*m_text.begin());
}

void IM_TextEditor::SetText(const xr_string& new_text)
{
	strncpy(&*m_text.begin(), new_text.c_str(), m_text.size()-1);
    m_text.back() = '\0';
}

void IM_TextEditor::Render()
{
	bool open = true;

	if(!ImGui::Begin(m_caption.c_str(), &open))
    {
    	Close();
        return;
    }

    ImGui::Columns(3, NULL, false);

    if(ImGui::Button("OK"))
    {
    	if(m_on_ok)
        	m_on_ok(this);

		open = false;
	}
    ImGui::SameLine();
    if(ImGui::Button("Cancel"))
    {
    	if(m_on_cancel)
        	m_on_cancel(this);

        open = false;
    }

    ImGui::NextColumn();

    for(u32 i = 0; i < m_user_buttons.size(); i++)
    {
    	ImGui::PushID(4444 + i);
        
    	if(ImGui::Button(m_user_buttons[i].first.c_str()))
        	m_user_buttons[i].second(this);

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

    ImGui::InputTextMultiline("##textarea", &*m_text.begin(), m_text.size(), ImVec2(-1,-1), ImGuiInputTextFlags_AllowTabInput);

    ImGui::End();

    if(!open)
    	Close();
}