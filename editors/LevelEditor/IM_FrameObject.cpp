#include "stdafx.h"
#pragma hdrstop

#include "IM_FrameObject.h"
#include "../ECore/ImGui/ImGui.h"
#include "../ECore/ImGui/utf8.h"
#include "../ECore/Editor/Library.h"

void IM_FrameObject::RefreshList()
{
	objects_tree.Clear();

	FS_FileSet objects;
    Lib.GetObjects(objects);

    for(FS_FileSetIt it = objects.begin(), end = objects.end(); it != end; it++)
    {
    	objects_tree.Add(codepage2utf8(it->name).c_str(), it->name.c_str());
    }
}

void IM_FrameObject::Render()
{
    if(ImGui::CollapsingHeader("Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    }

    if(ImGui::CollapsingHeader("Reference select",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    }

    if(ImGui::CollapsingHeader("Current object",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::MenuItem("Select..."))
        {
        	LPCSTR result;
        	if(TfrmChoseItem::SelectItem(smObject, result, 1, objects_tree.GetSelected().c_str()))
            	objects_tree.Select(result, true);
        }

        if(ImGui::MenuItem("Refresh list"))
			RefreshList();

        ImGui::BeginChild("objects", ImVec2(0,0), true);
        objects_tree.Render();
        ImGui::EndChild();
    }
}

