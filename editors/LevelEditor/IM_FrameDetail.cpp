#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/ImGui.h"

#include "IM_FrameDetail.h"
#include "Scene.h"
#include "ESceneDOTools.h"
#include "DOShuffle.h"
#include "../ECore/Editor/ui_main.h"

void IM_FrameDetail::Render()
{
	if(!parent_tool)
    {
    	parent_tool = dynamic_cast<EDetailManager*>(Scene->GetTool(OBJCLASS_DO));
        VERIFY(parent_tool);
    }

    if(ImGui::CollapsingHeader("DO Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::MenuItem("First Initialize"))
        {
        	if(parent_tool->Initialize())
            	Scene->UndoSave();
        }
		if(ImGui::MenuItem("Reinitialize All"))
        {
        	if(parent_tool->Reinitialize())
            	Scene->UndoSave();
        }
        if(ImGui::MenuItem("Reinitialize Objects Only"))
        {
        	if(parent_tool->UpdateObjects(true, false))
            	Scene->UndoSave();
        }
        if(ImGui::MenuItem("Reinitialize Selected Slot Objects"))
        {
        	if(parent_tool->UpdateObjects(false, true))
            	Scene->UndoSave();
        }

        ImGui::Separator();

        if(ImGui::MenuItem("Update Renderer"))
        {
        	parent_tool->InvalidateCache();
            Scene->UndoSave();
        }

        ImGui::Separator();

        if(ImGui::MenuItem("Clear Slots"))
        {
        	if(ELog.DlgMsg(mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, "Are you sure to reset slots?") == mrYes)
            {
    			parent_tool->ClearSlots();
				Scene->UndoSave();
    		}
    	}
		if(ImGui::MenuItem("Clear Details"))
        {
        	if(ELog.DlgMsg(mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, "Are you sure to clear details?") == mrYes)
            {
    			ExecCommand(COMMAND_UPDATE_PROPERTIES);
				parent_tool->Clear();
				Scene->UndoSave();
    		}
    	}

        ImGui::Separator();

        if(ImGui::MenuItem("Object List"))
        {
        	if(TfrmDOShuffle::Run())
            	Scene->UndoSave();
        }
    }
}

#pragma package(smart_init)
 