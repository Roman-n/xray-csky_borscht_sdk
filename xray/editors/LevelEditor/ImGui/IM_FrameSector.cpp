#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/imgui.h"

#include "IM_FrameSector.h"
#include "../Edit/scene.h"
#include "../Edit/sector.h"
#include "../Edit/portal.h"
#include "../Edit/portalutils.h"

#pragma package(smart_init)

void IM_FrameSector::Render()
{
	if(!ImGui::CollapsingHeader("Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    	return;

    if(ImGui::MenuItem("Validate Sectors"))
    {
    	PortalUtils.Validate(true);
    }
    if(ImGui::MenuItem("Capture Volume"))
    {
    	CSector* S = PortalUtils.GetSelectedSector();
		if(S)
        {
    		S->CaptureInsideVolume();
        	Scene->UndoSave();
    	}
    }
    if(ImGui::MenuItem("Distribute Objects"))
    {
    	CSector* S = PortalUtils.GetSelectedSector();
		if(S)
        {
    		S->DistributeInsideObjects	();
        	Scene->UndoSave				();
    	}
    }

    ImGui::Separator();

    if(ImGui::MenuItem("Create Default"))
    {
        CCustomObject* O = Scene->FindObjectByName(DEFAULT_SECTOR_NAME, OBJCLASS_SECTOR);
		if(O)
        	ELog.DlgMsg(mtInformation,"Default sector already present. Remove this and try again.");
    	else
        {
			if(!PortalUtils.CreateDefaultSector())
            	ELog.DlgMsg(mtInformation,"Default can't created.");
    	}
    }
    if(ImGui::MenuItem("Remove Default"))
    {
    	if(!PortalUtils.RemoveDefaultSector())
        	ELog.DlgMsg(mtInformation,"Default sector not found.");
    }
}
