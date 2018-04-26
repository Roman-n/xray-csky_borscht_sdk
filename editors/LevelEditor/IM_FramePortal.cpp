#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/imgui.h"

#include "IM_FramePortal.h"
#include "scene.h"
#include "sector.h"
#include "portal.h"
#include "portalutils.h"
#include "EScenePortalTools.h"

#pragma package(smart_init)

void IM_FramePortal::Render()
{
	if(!ImGui::CollapsingHeader("Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    	return;

    if(ImGui::MenuItem("Invert Orientation"))
    {
    	ObjectList lst;
    	if(Scene->GetQueryObjects(lst,OBJCLASS_PORTAL,1,1,0))
        {
    		for (ObjectIt it=lst.begin(); it!=lst.end(); it++)
            {
				CPortal* _O = (CPortal*)*it;
		    	_O->InvertOrientation(true);
        	}
    	}
    }
    if(ImGui::MenuItem("Compute All Portals"))
    {
    	if(mrYes == ELog.DlgMsg(mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, "Are you sure want to destroy all existing portals and compute them again?"))
    	{
			int cnt = PortalUtils.CalculateAllPortals();
			if(cnt)
            	ELog.DlgMsg(mtInformation, "Calculated '%d' portal(s).", cnt);
    	}
    }
    if(ImGui::MenuItem("Compute Sel. Portals"))
    {
    	if(mrYes == ELog.DlgMsg(mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, "Are you sure want to destroy all existing portals and compute them again?"))
    	{
			int cnt = PortalUtils.CalculateSelectedPortals();
			if(cnt)
            	ELog.DlgMsg(mtInformation, "Calculated '%d' portal(s).", cnt);
    	}
    }
    if(ImGui::MenuItem("Remove Similar"))
    {
    	EScenePortalTool* tool = dynamic_cast<EScenePortalTool*>(Scene->GetTool(OBJCLASS_PORTAL));
        VERIFY(tool);
        tool->RemoveSimilar();
    }
}
