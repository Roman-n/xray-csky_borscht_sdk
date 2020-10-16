#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/ImGui.h"

#include "IM_ContextMenu.h"
#include "../Edit/UI_LevelMain.h"
#include "../Edit/UI_LevelTools.h"

void IM_ContextMenu::Render()
{
	if(m_open)
	{
		ImGui::OpenPopup("im_contextmenu");
		m_open = false;
	}
			
	if(ImGui::BeginPopup("im_contextmenu"))
	{
		bool detach = false;
		
		if(ImGui::MenuItem("------------------------"))
			detach = true;
		
		ShowMenu();
			
		ImGui::EndPopup();
		
		if(detach)
		{
			m_detach = true;
			ImGui::SetNextWindowPos(ImGui::GetIO().MousePos, ImGuiCond_Always);
		}
	}
	
	if(m_detach)
	{
		if(!ImGui::Begin("Context Menu", &m_detach, ImGuiWindowFlags_NoResize))
		{
			ImGui::End();
			return;
		}
		
		ShowMenu();
		
		ImGui::End();
	}
}

void IM_ContextMenu::Open()
{
	m_open = true;
}

void IM_ContextMenu::ShowMenu()
{		
	if(ImGui::MenuItem("Copy (selection)"))
		ExecCommand(COMMAND_COPY);
	if(ImGui::MenuItem("Paste (selection)"))
		ExecCommand(COMMAND_PASTE);
	if(ImGui::MenuItem("Cut (selection)"))
		ExecCommand(COMMAND_CUT);
	if(ImGui::MenuItem("Duplicate (selection)"))
		ExecCommand(COMMAND_DUPLICATE);
		
	ImGui::Separator();
	
	if(ImGui::BeginMenu("Visibility"))
	{
		if(ImGui::MenuItem("Hide Selected"))
			ExecCommand(COMMAND_HIDE_SEL, FALSE);
		if(ImGui::MenuItem("Hide Unselected"))
			ExecCommand(COMMAND_HIDE_UNSEL);
		if(ImGui::MenuItem("Hide All"))
			ExecCommand(COMMAND_HIDE_ALL, FALSE);
			
		ImGui::Separator();
		
		if(ImGui::MenuItem("Unhide All"))
			ExecCommand(COMMAND_HIDE_ALL, TRUE);
			
		ImGui::EndMenu();
	}
	
	if(ImGui::BeginMenu("Locking"))
	{
		if(ImGui::MenuItem("Lock Selected"))
			ExecCommand(COMMAND_LOCK_SEL, TRUE);
		if(ImGui::MenuItem("Lock Unselected"))
			ExecCommand(COMMAND_LOCK_UNSEL, TRUE);
		if(ImGui::MenuItem("Lock All"))
			ExecCommand(COMMAND_LOCK_ALL, TRUE);
			
		ImGui::Separator();
		
		if(ImGui::MenuItem("Unlock Selected"))
			ExecCommand(COMMAND_LOCK_SEL, FALSE);
		if(ImGui::MenuItem("Unlock Unselected"))
			ExecCommand(COMMAND_LOCK_UNSEL, FALSE);
		if(ImGui::MenuItem("Unlock All"))
			ExecCommand(COMMAND_LOCK_ALL, FALSE);
			
		ImGui::EndMenu();
	}
	
	ImGui::Separator();
	
	if(ImGui::MenuItem("Properties..."))
		ExecCommand(COMMAND_SHOW_PROPERTIES);
}

IM_ContextMenu imContextMenu;
