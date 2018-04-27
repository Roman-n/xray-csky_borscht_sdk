#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/imgui.h"

#include "IM_FrameWayPoint.h"
#include "../ECore/Editor/ui_main.h"
#include "ui_leveltools.h"
#include "WayPoint.h"
#include "ESceneWayControls.h"
#include "Scene.h"

#pragma package(smart_init)

void IM_FrameWayPoint::Add1Links()
{
	if (!m_point_mode){
    	ELog.DlgMsg(mtInformation,"Before editing enter Point Mode.");
    	return;
    }
    bool bRes = false;
	ObjectList lst;
    Scene->GetQueryObjects(lst, OBJCLASS_WAY, 1, 1, 0);
	// remove links
    for (ObjectIt it=lst.begin(); it!=lst.end(); it++){
    	((CWayObject*)(*it))->RemoveLink();
    	bRes|=((CWayObject*)(*it))->Add1Link();
    }
	if (bRes) Scene->UndoSave();
    ExecCommand(COMMAND_UPDATE_PROPERTIES);
}

void IM_FrameWayPoint::Add2Links()
{
	if (!m_point_mode){
    	ELog.DlgMsg(mtInformation,"Before editing enter Point Mode.");
    	return;
    }
    bool bRes = false;
	ObjectList lst;
    Scene->GetQueryObjects(lst, OBJCLASS_WAY, 1, 1, 0);
    for (ObjectIt it=lst.begin(); it!=lst.end(); it++)
    	bRes|=((CWayObject*)(*it))->Add2Link();
	if (bRes) Scene->UndoSave();
    ExecCommand(COMMAND_UPDATE_PROPERTIES);
}

void IM_FrameWayPoint::InvertLinks()
{
	if (!m_point_mode){
    	ELog.DlgMsg(mtInformation,"Before editing enter Point Mode.");
    	return;
    }
	ObjectList lst;
    int cnt = Scene->GetQueryObjects(lst, OBJCLASS_WAY, 1, 1, 0);
    for (ObjectIt it=lst.begin(); it!=lst.end(); it++)
    	((CWayObject*)(*it))->InvertLink();
	if (cnt) Scene->UndoSave();
    ExecCommand(COMMAND_UPDATE_PROPERTIES);
}

void IM_FrameWayPoint::ConvertTo1Links()
{
	ObjectList lst;
    int cnt = Scene->GetQueryObjects(lst, OBJCLASS_WAY, 1, 1, 0);
    for (ObjectIt it=lst.begin(); it!=lst.end(); it++)
    	((CWayObject*)(*it))->Convert1Link();
	if (cnt) Scene->UndoSave();
    ExecCommand(COMMAND_UPDATE_PROPERTIES);
}

void IM_FrameWayPoint::ConvertTo2Links()
{
	ObjectList lst;
    int cnt = Scene->GetQueryObjects(lst, OBJCLASS_WAY, 1, 1, 0);
    for (ObjectIt it=lst.begin(); it!=lst.end(); it++)
    	((CWayObject*)(*it))->Convert2Link();
	if (cnt) Scene->UndoSave();
    ExecCommand(COMMAND_UPDATE_PROPERTIES);
}

void IM_FrameWayPoint::RemoveLinks()
{
	if (!m_point_mode){
    	ELog.DlgMsg(mtInformation,"Before editing enter Point Mode.");
    	return;
    }
	ObjectList lst;
    int cnt = Scene->GetQueryObjects(lst, OBJCLASS_WAY, 1, 1, 0);
    for (ObjectIt it=lst.begin(); it!=lst.end(); it++)
    	((CWayObject*)(*it))->RemoveLink();
	if (cnt) Scene->UndoSave();
    ExecCommand(COMMAND_UPDATE_PROPERTIES);
}

void IM_FrameWayPoint::OnAdd()
{
	IM_Storage storage(false, "level.ini", "IM_FrameWayPoint");
    m_auto_link = storage.GetBool("auto_link", true);
}

void IM_FrameWayPoint::OnRemove()
{
	IM_Storage storage(true, "level.ini", "IM_FrameWayPoint");
    storage.PutBool("auto_link", m_auto_link);
}

void IM_FrameWayPoint::Render()
{
	if(ImGui::CollapsingHeader("Way Mode",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::MenuItem("Way Mode", NULL, m_way_mode))
        {
        	m_way_mode = true;
            m_point_mode = false;
            LTools->SetTarget(OBJCLASS_WAY, estWayModeWay);
        }
        if(ImGui::MenuItem("Point Mode", NULL, m_point_mode))
        {
        	m_point_mode = true;
            m_way_mode = false;
            LTools->SetTarget(OBJCLASS_WAY, estWayModePoint);
        }
    }

    if(ImGui::CollapsingHeader("Link Command",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::MenuItem("Auto Link", NULL, m_auto_link))
        	m_auto_link = !m_auto_link;

        ImGui::Separator();

        ImGui::Columns(2);

        if(ImGui::MenuItem("Create 1-Link"))
			Add1Links();
        if(ImGui::MenuItem("Create 2-Link"))
        	Add2Links();
        if(ImGui::MenuItem("Invert Link"))
        	InvertLinks();

        ImGui::NextColumn();

        if(ImGui::MenuItem("Convert to 1-Link"))
        	ConvertTo1Links();
        if(ImGui::MenuItem("Convert to 2-Link"))
        	ConvertTo2Links();
        if(ImGui::MenuItem("Remove Link"))
        	RemoveLinks();

        ImGui::Columns(1);
    }
}
