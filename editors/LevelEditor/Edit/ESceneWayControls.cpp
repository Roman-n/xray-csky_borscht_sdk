#include "stdafx.h"
#pragma hdrstop

#include "ESceneWayTools.h"
#include "ESceneWayControls.h"
#include "ui_leveltools.h"
#include "FrameWayPoint.h"
#include "WayPoint.h"
#include "scene.h"
#include "ui_levelmain.h"

#include "IM_LeftBar.h"

void ESceneWayTool::OnActivate()
{
	inherited::OnActivate	();
//	TfraWayPoint* frame		=(TfraWayPoint*)pFrame;
//    if (sub_target==estWayModePoint)	frame->ebModePoint->Down 	= true;
//    else								frame->ebModeWay->Down 		= true;
	if(sub_target == estWayModePoint)
    {
    	imLeftBar.fraWayPoint.m_point_mode = true;
        imLeftBar.fraWayPoint.m_way_mode = false;
    }
    else
    {
    	imLeftBar.fraWayPoint.m_point_mode = false;
        imLeftBar.fraWayPoint.m_way_mode = true;
    }
}
//----------------------------------------------------

void ESceneWayTool::CreateControls()
{
	inherited::CreateDefaultControls(estWayModeWay);
	inherited::CreateDefaultControls(estWayModePoint);
	AddControl		(xr_new<TUI_ControlWayPointAdd>		(estWayModePoint,	etaAdd,		this));
	AddControl		(xr_new<TUI_ControlWayPointSelect>	(estWayModePoint,	etaSelect,	this));
	// frame
    pFrame 			= xr_new<TfraWayPoint>((TComponent*)0);
}
//----------------------------------------------------

void ESceneWayTool::RemoveControls()
{
	inherited::RemoveControls();
}
//----------------------------------------------------

//----------------------------------------------------
TUI_ControlWayPointAdd::TUI_ControlWayPointAdd(int st, int act, ESceneToolBase* parent):TUI_CustomControl(st,act,parent){
}

bool TUI_ControlWayPointAdd::Start(TShiftState Shift)
{
	ObjectList lst; Scene->GetQueryObjects(lst,OBJCLASS_WAY,1,1,-1);
//	TfraWayPoint* frame=(TfraWayPoint*)parent_tool->pFrame;
	IM_FrameWayPoint &frame = imLeftBar.fraWayPoint;
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
//        if (frame->ebAutoLink->Down){
		if (frame.m_auto_link){
            if (last_wp) last_wp->AddSingleLink(wp);
        }
        Scene->UndoSave();
    }
    if (!Shift.Contains(ssAlt)) ResetActionToSelect();
    return false;
}

void TUI_ControlWayPointAdd::OnEnter(){
}

//----------------------------------------------------
TUI_ControlWayPointSelect::TUI_ControlWayPointSelect(int st, int act, ESceneToolBase* parent)
	: TUI_CustomControl(st,act,parent)
{
}

bool TUI_ControlWayPointSelect::Start(TShiftState Shift)
{
	ESceneWayTool* tool = dynamic_cast<ESceneWayTool*>(parent_tool); VERIFY(tool);
	bool bWayMode = Shift.Contains(ssDouble);

	if (CheckSnapList(Shift)) return false;
	if (Shift==ssRBOnly){ ExecCommand(COMMAND_SHOWCONTEXTMENU,parent_tool->ClassID); return false;}

	if (!(Shift.Contains(ssCtrl)||Shift.Contains(ssAlt))){
		if (bWayMode)
			tool->SelectObjects(false);
		else
			tool->SelectPoints(false);
	}

	int cnt;
	float dist = UI->ZFar();

	if(bWayMode){
		cnt = tool->RaySelect(Shift.Contains(ssCtrl)?-1:Shift.Contains(ssAlt)?0:1,dist,UI->m_CurrentRStart,UI->m_CurrentRNorm,FALSE);
	}else{
		cnt = tool->RaySelectPoint(Shift.Contains(ssCtrl)?-1:Shift.Contains(ssAlt)?0:1,dist,UI->m_CurrentRStart,UI->m_CurrentRNorm,FALSE);

		bBoxSelection    = ((0!=cnt) && (Shift.Contains(ssCtrl)||Shift.Contains(ssAlt))) || (0==cnt);
		if( bBoxSelection ){
			UI->EnableSelectionRect( true );
			UI->UpdateSelectionRect(UI->m_StartCp,UI->m_CurrentCp);
			return true;
		}
	}
	return false;
}

void TUI_ControlWayPointSelect::Move(TShiftState Shift)
{
	if (bBoxSelection) UI->UpdateSelectionRect(UI->m_StartCp,UI->m_CurrentCp);
}

bool TUI_ControlWayPointSelect::End(TShiftState Shift)
{
	ESceneWayTool* tool = dynamic_cast<ESceneWayTool*>(parent_tool); VERIFY(tool);
	CFrustum frustum;

	if (LUI->SelectionFrustum(frustum)) {
		if (bBoxSelection){
			UI->EnableSelectionRect( false );
			bBoxSelection = false;
			tool->FrustumSelectPoint(Shift.Contains(ssAlt)?0:1,frustum);
		}
	}

    return true;
}


