#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/ImGui.h"

#include "IM_FrameFogVol.h"
#include "Scene.h"
#include "ESceneFogVolumeTools.h"

#pragma package(smart_init)

void IM_FrameFogVol::OnAdd()
{
    m_parent_tool = dynamic_cast<ESceneFogVolumeTool*>(Scene->GetOTool(OBJCLASS_FOG_VOL));
    VERIFY(m_parent_tool);

    IM_Storage s(false, "level.ini", "IM_FrameFogVol");
    m_show_commands = s.GetBool("show_commands_panel", true);
}

void IM_FrameFogVol::OnRemove()
{
    IM_Storage s(true, "level.ini", "IM_FrameFogVol");
    s.PutBool("show_commands_panel", m_show_commands);
}

void IM_FrameFogVol::Render()
{
    if(ImGui::CollapsingPanel("Commands", &m_show_commands))
    {
    	ImGui::Columns(2, NULL, false);

    	if(ImGui::MenuItem("Group Selected"))
    		m_parent_tool->GroupSelected();

    	ImGui::NextColumn();

    	if(ImGui::MenuItem("UnGroup Selected"))
    		m_parent_tool->UnGroupCurrent();

    	ImGui::Columns(1);
    }
}
