#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/ImGui.h"

#include "IM_FrameFogVol.h"
#include "Scene.h"
#include "ESceneFogVolumeTools.h"

#pragma package(smart_init)

void IM_FrameFogVol::Render()
{
	if(!parent_tool)
	{
    	parent_tool = dynamic_cast<ESceneFogVolumeTool*>(Scene->GetOTool(OBJCLASS_FOG_VOL));
        VERIFY(parent_tool);
    }

    if(ImGui::CollapsingHeader("Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2, NULL, false);

    	if(ImGui::MenuItem("Group Selected"))
    		parent_tool->GroupSelected();

    	ImGui::NextColumn();

    	if(ImGui::MenuItem("UnGroup Selected"))
    		parent_tool->UnGroupCurrent();

    	ImGui::Columns(1);
    }
}
