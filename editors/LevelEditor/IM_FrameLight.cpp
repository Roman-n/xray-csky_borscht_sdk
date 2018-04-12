#include "stdafx.h"
#pragma hdrstop

#include "IM_FrameLight.h"
#include "..\ECore\ImGui\ImGui.h"

#include "Scene.h"
#include "ELight.h"

#pragma package(smart_init)

void IM_FrameLight::UseInD3D(bool bAll, bool bFlag)
{
	ObjectIt _F = Scene->FirstObj(OBJCLASS_LIGHT);
    ObjectIt _E = Scene->LastObj(OBJCLASS_LIGHT);
	for(;_F!=_E;_F++){
		CLight* L=(CLight*)*_F;
    	if(bAll){
            L->AffectD3D(bFlag);
        }else{
			if(L->Selected() && L->Visible()) L->AffectD3D(bFlag);
        }
    }
//    UI->RedrawScene();
}

void IM_FrameLight::Render()
{
	if(ImGui::CollapsingHeader("Affect in D3D", ImGuiTreeNodeFlags_Framed))
    {
    	ImGui::Columns(2, NULL, false);

        if(ImGui::Button("Enable Sel"))
        	UseInD3D(false, true);
        if(ImGui::Button("Disable Sel"))
        	UseInD3D(false, false);

        ImGui::NextColumn();

        if(ImGui::Button("Enable All"))
        	UseInD3D(true, true);
        if(ImGui::Button("Disable All"))
        	UseInD3D(true, false);

        ImGui::Columns(1);
    }
}


 