#include "stdafx.h"
#pragma hdrstop

#include "ESceneWayTools.h"
#include "WayPoint.h"
#include "ui_levelmain.h"

CCustomObject* ESceneWayTool::CreateObject(LPVOID data, LPCSTR name)
{
	CCustomObject* O	= xr_new<CWayObject>(data,name);
    O->ParentTool		= this;
    return O;
}
//----------------------------------------------------

int ESceneWayTool::RaySelectPoint(int flag, float& distance, const Fvector& start, const Fvector& direction, BOOL bDistanceOnly)
{
    CCustomObject* nearest_object=0;
    if (RayPick(nearest_object,distance,start,direction,0)&&!bDistanceOnly) 
		((CWayObject*)nearest_object)->RaySelectPoint(flag,start,direction,false);

    UI->RedrawScene();
    return !!nearest_object;
}
//----------------------------------------------------

int ESceneWayTool::FrustumSelectPoint(int flag, const CFrustum& frustum)
{
    for(ObjectIt _F = m_Objects.begin();_F!=m_Objects.end();_F++)
		if((*_F)->Visible()){
			((CWayObject*)(*_F))->FrustumSelectPoint( flag, frustum );
		}
	UI->RedrawScene		();
    
	return 0;
}
//----------------------------------------------------

void ESceneWayTool::SelectPoints(bool flag)
{
    for(ObjectIt _F = m_Objects.begin();_F!=m_Objects.end();_F++)
        if((*_F)->Visible()){
			((CWayObject*)(*_F))->SelectPoint( flag );
        }
	UI->RedrawScene		();
}
//----------------------------------------------------

