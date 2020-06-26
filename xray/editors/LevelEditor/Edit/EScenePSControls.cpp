#include "stdafx.h"
#pragma hdrstop

#include "EScenePSControls.h"
#include "ui_leveltools.h"
#include "..\..\Layers\xrRender\PSLibrary.h"
#include "EParticlesObject.h"
#include "scene.h"
#ifndef NO_VCL
#include "FramePS.h"
#endif
#include "../ECore/Editor/ui_main.h"

#include "ImGui\IM_LeftBar.h"

using namespace std::placeholders;

//----------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TUI_ControlPSAdd::TUI_ControlPSAdd(int st, int act, ESceneToolBase* parent):TUI_CustomControl(st,act,parent){
}

bool TUI_ControlPSAdd::AfterAppendCallback(TShiftState Shift, CCustomObject* obj)
{
	EParticlesObject* pg= dynamic_cast<EParticlesObject*>(obj); R_ASSERT(pg);
#ifndef NO_VCL
    LPCSTR ref_name		= ((TfraPS*)parent_tool->pFrame)->Current();
#else
    LPCSTR ref_name = imLeftBar.fraPS.Current();
#endif

    if (!ref_name){
    	ELog.DlgMsg(mtInformation,"Nothing selected.");
    	return false;
    }
	if (!pg->Compile(ref_name)){
    	ELog.DlgMsg(mtInformation,"Can't compile particle system '%s'.",ref_name);
        return false;
    }

    return true;
}

bool TUI_ControlPSAdd::Start(TShiftState Shift)
{
    DefaultAddObject(Shift,0,std::bind(&TUI_ControlPSAdd::AfterAppendCallback,this,_1,_2));
    return false;
}

void TUI_ControlPSAdd::Move(TShiftState _Shift)
{
}
bool TUI_ControlPSAdd::End(TShiftState _Shift)
{
    return true;
}


