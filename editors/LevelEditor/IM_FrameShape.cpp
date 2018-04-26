#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/imgui.h"

#include "IM_FrameShape.h"
#include "Scene.h"
#include "EShape.h"
#include "ESceneShapeTools.h"
#include "../ECore/Editor/ui_main.h"
#include "ui_leveltools.h"

#pragma package(smart_init)

void IM_FrameShape::Render()
{
	if(!m_parent_tool)
    {
    	m_parent_tool = dynamic_cast<ESceneShapeTool*>(Scene->GetTool(OBJCLASS_SHAPE));
        VERIFY(m_parent_tool);
    }

	if(ImGui::CollapsingHeader("Append",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::Selectable("Box", &m_append_box))
        	m_append_sphere = !m_append_box;
        if(ImGui::Selectable("Sphere", &m_append_sphere))
        	m_append_box = !m_append_sphere;
    }

    if(ImGui::CollapsingHeader("Edit",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::Selectable("Attach Shape...", &m_attach_shape))
        {
        	if(m_attach_shape)
            	ExecCommand(COMMAND_CHANGE_ACTION, etaAdd);
        }
        if(ImGui::MenuItem("Detach All"))
        {
            ObjectList lst;
    		if(Scene->GetQueryObjects(lst,OBJCLASS_SHAPE,1,1,0))
            {
				Scene->SelectObjects(false,OBJCLASS_SHAPE);
    			for(ObjectIt it=lst.begin(); it!=lst.end(); it++)
        			((CEditShape*)*it)->Detach();
    		}
    	}
    }

    if(ImGui::CollapsingHeader("Level bounds",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::Selectable("Edit level bounds", &m_edit_level_bound))
        	m_parent_tool->OnEditLevelBounds(false);

        if(ImGui::MenuItem("Recalc", NULL, false, m_edit_level_bound))
        	m_parent_tool->OnEditLevelBounds(true);
    }
}
