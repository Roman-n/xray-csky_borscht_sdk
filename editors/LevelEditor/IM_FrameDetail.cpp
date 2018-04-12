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

    if(ImGui::CollapsingHeader("DO Commands", ImGuiTreeNodeFlags_Framed))
    {
    	ImGui::TextUnformatted("First Initialize");
        if(ImGui::IsItemClicked())
        {
        	if(parent_tool->Initialize())
            	Scene->UndoSave();
        }
		ImGui::TextUnformatted("Reinitialize All");
        if(ImGui::IsItemClicked())
        {
        	if(parent_tool->Reinitialize())
            	Scene->UndoSave();
        }
        ImGui::TextUnformatted("Reinitialize Objects Only");
        if(ImGui::IsItemClicked())
        {
        	if(parent_tool->UpdateObjects(true, false))
            	Scene->UndoSave();
        }
        ImGui::TextUnformatted("Reinitialize Selected Slot Objects");
        if(ImGui::IsItemClicked())
        {
        	if(parent_tool->UpdateObjects(false, true))
            	Scene->UndoSave();
        }

        ImGui::Separator();

        ImGui::TextUnformatted("Update Renderer");
        if(ImGui::IsItemClicked())
        {
        	parent_tool->InvalidateCache();
            Scene->UndoSave();
        }

        ImGui::Separator();

        ImGui::TextUnformatted("Clear Slots");
        if(ImGui::IsItemClicked())
        {
        	if(ELog.DlgMsg(mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, "Are you sure to reset slots?") == mrYes)
            {
    			parent_tool->ClearSlots();
				Scene->UndoSave();
    		}
    	}
		ImGui::TextUnformatted("Clear Details");
        if(ImGui::IsItemClicked())
        {
        	if(ELog.DlgMsg(mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, "Are you sure to clear details?") == mrYes)
            {
    			ExecCommand(COMMAND_UPDATE_PROPERTIES);
				parent_tool->Clear();
				Scene->UndoSave();
    		}
    	}

        ImGui::Separator();

        ImGui::TextUnformatted("Object List");
        if(ImGui::IsItemClicked())
        {
        	if(TfrmDOShuffle::Run())
            	Scene->UndoSave();
        }
    }
}

#pragma package(smart_init)
 