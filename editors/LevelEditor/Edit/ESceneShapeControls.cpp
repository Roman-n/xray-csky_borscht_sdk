#include "stdafx.h"
#pragma hdrstop

#include "ESceneShapeControls.h"
#include "ui_leveltools.h"
#include "FrameShape.h"
#include "EShape.h"
#include "scene.h"
#include "../ECore/Editor/ui_main.h"
#include "IM_LeftBar.h"
//---------------------------------------------------------------------------
__fastcall TUI_ControlShapeAdd::TUI_ControlShapeAdd(int st, int act, ESceneToolBase* parent):TUI_CustomControl(st,act,parent)
{
}

bool __fastcall TUI_ControlShapeAdd::AfterAppendCallback(TShiftState Shift, CCustomObject* obj)
{
	CEditShape* shape 	= dynamic_cast<CEditShape*>(obj); R_ASSERT(shape);
//	TfraShape* F 		= (TfraShape*)parent_tool->pFrame;
	IM_FrameShape& F 	= imLeftBar.fraShape;
//	if (F->ebTypeSphere->Down){
	if (F.m_append_sphere){
    	Fsphere S;	S.identity();
    	shape->add_sphere(S);
        if (!Shift.Contains(ssAlt)) F.m_append_sphere = false;//F->ebTypeSphere->Down = false;
        return true;
//	}else if (F->ebTypeBox->Down){
	}else if (F.m_append_box){
    	Fmatrix M;	M.identity();
    	shape->add_box(M);
		if (!Shift.Contains(ssAlt)) F.m_append_box = false;//F->ebTypeBox->Down = false;
        return true;
    }else{
    	ELog.DlgMsg(mtInformation,"Select shape type at first.");
    }
    return false;
}

bool __fastcall TUI_ControlShapeAdd::Start(TShiftState Shift)
{
//	TfraShape* F 		= (TfraShape*)parent_tool->pFrame;
    IM_FrameShape& F 	= imLeftBar.fraShape;
	if (F.m_attach_shape){
//	if (F->ebAttachShape->Down){
		CEditShape* from = dynamic_cast<CEditShape*>(Scene->RayPickObject(UI->ZFar(),UI->m_CurrentRStart, UI->m_CurrentRNorm, OBJCLASS_SHAPE, 0, 0));
        if (from){
            ObjectList lst;
            int cnt 		= Scene->GetQueryObjects(lst,OBJCLASS_SHAPE,1,1,0);
            if (1!=cnt)		ELog.DlgMsg(mtError,"Select one shape.");
            else{
                CEditShape* base = dynamic_cast<CEditShape*>(lst.back()); R_ASSERT(base);
                if (base!=from){
	                base->Attach(from);
    	            if (!Shift.Contains(ssAlt)){
//        	            F->ebAttachShape->Down 	= false;
						F.m_attach_shape 		= false;
            	        ResetActionToSelect		();
                	}
                }
            }
        }
    }else
	    DefaultAddObject(Shift,0,AfterAppendCallback);
    return false;
}

