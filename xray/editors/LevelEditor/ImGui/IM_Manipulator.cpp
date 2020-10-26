#include "stdafx.h"
#pragma hdrstop

#include "IM_Manipulator.h"
#include "../../ECore/ImGui/imgui.h"
#include "../../ECore/ImGui/ImGuizmo.h"

#include "../Edit/scene.h"
#include "../Edit/UI_LevelTools.h"
#include "../Edit/CustomObject.h"
IM_Manipulator imManipulator;

void IM_Manipulator::Render()
{
	//ELog.Msg(mtInformation, "%d", LTools->CurrentClassID());
	ESceneCustomOTool *tool = Scene->GetOTool(LTools->CurrentClassID());
	if(!tool)
		return;
		
	ObjectList lst;
	tool->GetQueryObjects(lst, TRUE, TRUE, FALSE);
	if(lst.size() < 1)
		return;
		
	bool bWorld = Tools->GetSettings(etfCSParent);
		
	ImGuizmo::OPERATION op;
	ImGuizmo::MODE mode;
	float *snap = NULL;
	
	ImGuizmo::SetRect(0, 0, Device.m_RealWidth, Device.m_RealHeight);
	
	switch(LTools->GetAction())
	{
		case etaMove: {
			op = ImGuizmo::TRANSLATE; 
			mode = bWorld ? ImGuizmo::WORLD : ImGuizmo::LOCAL;
			snap = LTools->GetSettings(etfMSnap) ? &Tools->m_MoveSnap : NULL;
			
			Fmatrix mat = lst.front()->FTransformRP, delta = Fidentity;
			
			bool m = ImGuizmo::Manipulate(
				(float*)&Device.mView, 
				(float*)&Device.mProjection, 
				op, 
				mode, 
				(float*)&mat, 
				(float*)&delta,
				snap
			);
			
			if(m) {
				if(bWorld) {
					for(ObjectIt it = lst.begin(); it != lst.end(); it++)
						(*it)->Move(delta.c);
				} else {
					Fmatrix rot_inv = Fmatrix().invert(lst.front()->FTransformR);
					Fmatrix local_offset = Fmatrix().mul(rot_inv, delta);
			
					for(ObjectIt it = lst.begin(); it != lst.end(); it++) {		
						Fmatrix offset;
						offset.mul((*it)->FTransformR, local_offset);
						
						(*it)->Move(offset.c);
					}
				}
			}
			
		} break;
		
		case etaRotate: {
			op = ImGuizmo::ROTATE;
			mode = bWorld ? ImGuizmo::WORLD : ImGuizmo::LOCAL;
			
			float ang = rad2deg(Tools->m_RotateSnapAngle);
			snap = LTools->GetSettings(etfASnap) ? &ang : NULL;
			
			//if(lst.size() > 1) {
			//	return;
			//}
			
			Fmatrix mat = lst.front()->FTransformRP, diff = Fidentity;
			
			Fvector original_rot;
			mat.getXYZ(original_rot);
			
			bool m = ImGuizmo::Manipulate(
				(float*)&Device.mView, 
				(float*)&Device.mProjection, 
				op, 
				mode, 
				(float*)&mat,
				(float*)&diff,
				snap
			);
			
			if(m) {
				if(bWorld) {
					for(ObjectIt it = lst.begin(); it != lst.end(); it++) {
						Fmatrix t;
						t.mul(diff, (*it)->FTransformR);
						
						Fvector rot;
						t.getXYZ(rot);
						
						(*it)->SetRotation(rot);
					}
				} else {
				
					Fvector rot;
					mat.getXYZ(rot);
					
					Fvector rot_diff;
					rot_diff.set(rot).sub(original_rot);
					
					//ELog.Msg(mtInformation, "%f %f %f", rot_diff.x, rot_diff.y, rot_diff.z);
					
					for(ObjectIt it = lst.begin(); it != lst.end(); it++) {
						(*it)->RotateParent(Fvector().set(0,0,1), rot_diff.z);
						(*it)->RotateParent(Fvector().set(1,0,0), rot_diff.x);
						(*it)->RotateParent(Fvector().set(0,1,0), rot_diff.y);
					}
				}
			}
			
		} break;
		
		case etaScale: {
			op = ImGuizmo::SCALE;
			mode = ImGuizmo::LOCAL;
				
			//if(lst.size() > 1) {
			//	return;
			//}
			
			Fmatrix mat = lst.front()->FTransform;
			
			Fvector original_scale;
			original_scale.x = mat.i.magnitude();
			original_scale.y = mat.j.magnitude();
			original_scale.z = mat.k.magnitude();
			
			bool m = ImGuizmo::Manipulate(
				(float*)&Device.mView, 
				(float*)&Device.mProjection, 
				op, 
				mode, 
				(float*)&mat
			);
			
			if(m) {
				Fvector scale;
				scale.x = mat.i.magnitude() - original_scale.x;
				scale.y = mat.j.magnitude() - original_scale.y;
				scale.z = mat.k.magnitude() - original_scale.z;
				
				for(ObjectIt it = lst.begin(); it != lst.end(); it++)
					(*it)->Scale(scale);
			}
			
		} break;
	}
	
	if(ImGuizmo::IsUsing() && !m_active) {
		// activate
		m_active = true;
	}
	
	if(!ImGuizmo::IsUsing() && m_active) {
		// deactivate
		Scene->UndoSave();
		m_active =  false;
	}
}
