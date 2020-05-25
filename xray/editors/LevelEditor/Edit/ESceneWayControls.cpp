#include "stdafx.h"
#pragma hdrstop

#include "ESceneWayTools.h"
#include "ESceneWayControls.h"
#include "ui_leveltools.h"
#ifndef NO_VCL
#include "FrameWayPoint.h"
#endif
#include "WayPoint.h"
#include "scene.h"
#include "ui_levelmain.h"

void ESceneWayTool::OnActivate()
{
	inherited::OnActivate	();
#ifndef NO_VCL
	TfraWayPoint* frame		=(TfraWayPoint*)pFrame;
    if (sub_target==estWayModePoint)	frame->ebModePoint->Down 	= true;
    else								frame->ebModeWay->Down 		= true;
#endif
}
//----------------------------------------------------

void ESceneWayTool::CreateControls()
{
	inherited::CreateDefaultControls(estWayModeWay);
	inherited::CreateDefaultControls(estWayModePoint);
    AddControl		(xr_new<TUI_ControlWayPointAdd>	(estWayModePoint,	etaAdd,		this));
#ifndef NO_VCL
	// frame
    pFrame 			= xr_new<TfraWayPoint>((TComponent*)0);
#endif
}
//----------------------------------------------------

void ESceneWayTool::RemoveControls()
{
	inherited::RemoveControls();
}
//----------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TUI_ControlWayPointAdd::TUI_ControlWayPointAdd(int st, int act, ESceneToolBase* parent):TUI_CustomControl(st,act,parent){
}

bool TUI_ControlWayPointAdd::Start(TShiftState Shift)
{
	ObjectList lst; Scene->GetQueryObjects(lst,OBJCLASS_WAY,1,1,-1);
#ifndef NO_VCL
	TfraWayPoint* frame=(TfraWayPoint*)parent_tool->pFrame;
    if (1!=lst.size()){
        ELog.DlgMsg(mtInformation,"Select one WayObject.");
        return false;
    }
    Fvector p;
    if (LUI->PickGround(p,UI->m_CurrentRStart,UI->m_CurrentRNorm,1)){
        CWayObject* obj = (CWayObject*)lst.front(); R_ASSERT(obj);
        CWayPoint* last_wp=obj->GetFirstSelected();
        CWayPoint* wp=obj->AppendWayPoint();
        wp->MoveTo(p);
        if (frame->ebAutoLink->Down){
            if (last_wp) last_wp->AddSingleLink(wp);
        }
        Scene->UndoSave();
    }
#endif
    if (!Shift.Contains(ssAlt)) ResetActionToSelect();
    return false;
}

void TUI_ControlWayPointAdd::OnEnter(){
}

