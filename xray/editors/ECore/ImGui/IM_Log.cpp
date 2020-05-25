//---------------------------------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include "imgui.h"
#include "IM_Log.h"
//---------------------------------------------------------------------------

void IM_Log::Clear()
{
	msgs.clear();
}

void IM_Log::ClearSelected()
{
	xr_list<Message>::iterator it, end;
    for(it = msgs.begin(), end = msgs.end(); it != end;)
    {
    	if(it->selected)
        {
        	msgs.erase(it++);
            continue;
        }

        it++;
    }
}

void IM_Log::AddMessage(MessageType mt, const char* text)
{
	msgs.push_back(Message(mt, text));
    has_new_messages = true;
}

void IM_Log::Render()
{
	if(!show_log)
    	return;

	ImGui::SetNextWindowSize(ImVec2(500,150), ImGuiCond_FirstUseEver);
	if(!ImGui::Begin("Log", &show_log))
    {
    	ImGui::End();
        return;
    }

    ImGui::BeginChild("log", ImVec2(0, -(ImGui::GetItemsLineHeightWithSpacing() + 5)));

    xr_list<Message>::iterator it, end;
    for(it = msgs.begin(), end = msgs.end(); it != end; it++)
    {
    	const char* text = it->text.c_str();
    	u32 color;

    	switch(it->type)
    	{
    		case mtInfo:			color = EPrefs->log_info_color;			break;
    		case mtError:			color = EPrefs->log_error_color;        break;
    		case mtConfirmation:	color = EPrefs->log_confirmation_color;	break;
    		default:				color = EPrefs->log_default_color;
    	}

    	color = subst_alpha(bgr2rgb(color), 0xFF);
    	ImGui::PushStyleColor(ImGuiCol_Text, color);

    	ImGui::Selectable(text, &it->selected);

    	ImGui::PopStyleColor(1);
    }

    if(has_new_messages)
    {
    	ImGui::SetScrollY(ImGui::GetItemsLineHeightWithSpacing() * msgs.size());
    	has_new_messages = false;
    }

    ImGui::EndChild();

    ImGui::Separator();

    if(ImGui::Button("Close"))
    	Close();

    ImGui::SameLine();

    if(ImGui::Button("Flush"))
    	FlushLog();

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.f);

    if(ImGui::Button("Clear"))
    	Clear();

    ImGui::SameLine();

    if(ImGui::Button("Clear selected"))
    	ClearSelected();

    ImGui::End();
}

ECORE_API IM_Log imLog;

#pragma package(smart_init)
