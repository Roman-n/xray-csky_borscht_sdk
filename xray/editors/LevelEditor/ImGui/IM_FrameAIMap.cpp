#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/imgui.h"
#include "../ECore/ImGui/utf8.h"

#include "IM_FrameAIMap.h"
#include "../Edit/Scene.h"
#include "../Edit/ESceneAIMapTools.h"
#include <xrEngine/GameMtlLib.h>
#include "../ECore/Editor/ui_main.h"

#pragma package(smart_init)

void IM_FrameAIMap::LoadCompilerErrors()
{
	xr_string filename;
	if(false == EFS.GetOpenName("$logs$", filename))
    	return;

    IReader *R = FS.r_open(filename.c_str());
    if(!R)
    	return;

    m_parent_tool->LoadCompilerErrors(*R);
    FS.r_close(R);
}

static const int idx[5][4]={
	{0,1,2,3},
	{1,2,3,0},
	{2,3,0,1},
	{3,0,1,2},
	{4,4,4,4},
};

static int ConvertV2L(int side)
{
	if (side<4){
        const Fvector& HPB = Device.m_Camera.GetHPB();
        float h = angle_normalize(HPB.x)/PI; R_ASSERT((h>=0.f)&&(h<=2.f));
        if (h>0.25f&&h<=0.75f)		return idx[3][side];
        else if (h>0.75f&&h<=1.25f)	return idx[2][side];
        else if (h>1.25f&&h<=1.75f)	return idx[1][side];
        else return idx[0][side];
    }else return side;
}
                        
static const u8 fl[5]	=	{SAINode::flN1,SAINode::flN2,SAINode::flN3,SAINode::flN4,
    					 	 SAINode::flN1|SAINode::flN2|SAINode::flN3|SAINode::flN4,
//    					 	 SAINode::flN1|SAINode::flN2,SAINode::flN2|SAINode::flN3,
//    					 	 SAINode::flN3|SAINode::flN4,SAINode::flN4|SAINode::flN1
                             };

void IM_FrameAIMap::MakeLink(int side)
{
	ESceneAIMapTool::EMode mode;
    if (m_link_add) 		mode = ESceneAIMapTool::mdAppend;
    else if (m_link_del)	mode = ESceneAIMapTool::mdRemove;
    else if (m_link_invert)	mode = ESceneAIMapTool::mdInvert;
	m_parent_tool->MakeLinks(fl[ConvertV2L(side)], mode, m_ignore_constraints);
    Scene->UndoSave();
    UI->RedrawScene();
}

void IM_FrameAIMap::OnAdd()
{
	m_parent_tool = dynamic_cast<ESceneAIMapTool*>(Scene->GetTool(OBJCLASS_AIMAP));
	VERIFY(m_parent_tool);

    IM_Storage storage(false, "level.ini", "IM_FrameAIMap");

    m_ignore_constraints = storage.GetBool("ignore_constraints", false);
    m_auto_link = storage.GetBool("auto_link", true);

    xr_string link_mode = storage.GetString("link_mode", "add");
    if(link_mode == "add")
    {
    	m_link_add = true;
        m_link_del = m_link_invert = false;
    }
    else if(link_mode == "del")
    {
    	m_link_del = true;
        m_link_add = m_link_invert = false;
    }
    else
    {
    	m_link_invert = true;
        m_link_add = m_link_del = false;
    }
}

void IM_FrameAIMap::OnRemove()
{
	IM_Storage storage(true, "level.ini", "IM_FrameAIMap");
    storage.PutBool("ignore_constraints", m_ignore_constraints);
    storage.PutBool("auto_link", m_auto_link);
	storage.PutString("link_mode",
    m_link_add ? "add" : m_link_del ? "del" : "invert");
}

void IM_FrameAIMap::Render()
{
    if(ImGui::CollapsingHeader("AI Map Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2, "aimap_commands", false);

        if(ImGui::MenuItem("Generate Full"))
        	m_parent_tool->GenerateMap(false);
        if(ImGui::MenuItem("Generate Selected"))
        	m_parent_tool->GenerateMap(true);
        if(ImGui::MenuItem("Reset Selected"))
        	m_parent_tool->ResetNodes();

        ImGui::NextColumn();

        if(ImGui::MenuItem("Smooth Selected"))
        	m_parent_tool->SmoothNodes();
        if(ImGui::MenuItem("Clear AI-Map"))
        {
        	if (ELog.DlgMsg(mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,"Are you sure to clear AI Map?")==mrYes){
				m_parent_tool->Clear();
				Scene->UndoSave();
    		}
    	}

        ImGui::Columns(1);
    }

    if(ImGui::CollapsingHeader("AI Map Errors",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2, "aimap_errors", false);

        if(ImGui::MenuItem("Load Error List"))
        	LoadCompilerErrors();
        if(ImGui::MenuItem("Clear Error List"))
        	m_parent_tool->m_ErrorNodes.clear();

        ImGui::NextColumn();

        if(ImGui::MenuItem("Select Error Nodes"))
        	m_parent_tool->SelectErrorNodes();

        ImGui::Columns(1);
    }

    if(ImGui::CollapsingHeader("AI Map Nodes",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2, "aimap_nodes", false);
        if(ImGui::Selectable("Ignore Contraints", &m_ignore_constraints))
        	;
        ImGui::NextColumn();
        if(ImGui::Selectable("Auto Link", &m_auto_link))
        	;
        ImGui::Columns(1);

        ImGui::TextUnformatted("Link commands:");

        ImGui::Columns(3);

        if(ImGui::Selectable("Add", &m_link_add) && m_link_add)
        	m_link_del = m_link_invert = false;
        if(ImGui::Selectable("Delete", &m_link_del) && m_link_del)
        	m_link_add = m_link_invert = false;
        if(ImGui::Selectable("Invert", &m_link_invert) && m_link_invert)
        	m_link_add = m_link_del = false;

        ImGui::NextColumn();

        ImGui::SmallButton(" ");
        ImGui::SameLine();
        if(ImGui::SmallButton("^"))
        	MakeLink(1);
        ImGui::SameLine();
        ImGui::SmallButton(" ");

        if(ImGui::SmallButton("<"))
        	MakeLink(0);
        ImGui::SameLine();
        if(ImGui::SmallButton("+"))
        	MakeLink(4);
        ImGui::SameLine();
        if(ImGui::SmallButton(">"))
        	MakeLink(2);

        ImGui::SmallButton(" ");
        ImGui::SameLine();
        if(ImGui::SmallButton("v"))
        	MakeLink(3);
        ImGui::SameLine();
        ImGui::SmallButton(" ");

        ImGui::NextColumn();

        if(ImGui::MenuItem("Select 0-Link"))
        	m_parent_tool->SelectNodesByLink(0);
        if(ImGui::MenuItem("Select 1-Link"))
        	m_parent_tool->SelectNodesByLink(1);
        if(ImGui::MenuItem("Select 2-Link"))
        	m_parent_tool->SelectNodesByLink(2);

        ImGui::Columns(1);
    }

    if(ImGui::CollapsingHeader("Ignore Materials",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2, "aimap_ignoremat", false);
    	if(ImGui::MenuItem("Add"))
        {
            LPCSTR new_val = 0;
#ifndef NO_VCL
    		if ( TfrmChoseItem::SelectItem(smGameMaterial,new_val,1) )
    		{
        		m_ignored_materials.push_back(new_val);
        		SGameMtl* mtl		= GMLib.GetMaterial(new_val);
        		m_parent_tool->m_ignored_materials.push_back(mtl->GetID());
    		}
#endif
        }
        ImGui::NextColumn();
        if(ImGui::MenuItem("Clear"))
        {
        	m_ignored_materials.clear();
        	m_parent_tool->m_ignored_materials.clear();
        }
        ImGui::Columns(1);

        ImGui::BeginChild("ignorematerials", ImVec2(0,250), true);
        for(SStringVecIt it = m_ignored_materials.begin(), end = m_ignored_materials.end(); it != end; it++)
        {
        	xr_string mat_name = codepage2utf8(*it);
        	ImGui::TextUnformatted(&*mat_name.begin(), &*mat_name.end());
        }
        ImGui::EndChild();
    }
}
