#include "stdafx.h"
#pragma hdrstop

#include "IM_FrameObject.h"
#include "../ECore/ImGui/ImGui.h"
#include "../ECore/ImGui/utf8.h"
#include "../ECore/Editor/Library.h"
#include "Scene.h"
#include "SceneObject.h"
#include "ESceneObjectTools.h"
#include "../ECore/Editor/ui_main.h"

LPCSTR IM_FrameObject::Current()
{
	if(m_objects_tree.GetSelectedCount())
    	return m_objects_tree.GetSelected().c_str();
    else
    	return NULL;
}

void IM_FrameObject::MultipleAppend()
{
	LPCSTR N;
    if (TfrmChoseItem::SelectItem(smObject,N,32,0)){
    	Fvector pos={0.f,0.f,0.f};
    	Fvector up={0.f,1.f,0.f};
        Scene->SelectObjects(false,OBJCLASS_SCENEOBJECT);
	    AStringVec lst;
    	_SequenceToList(lst,N);
        SPBItem* pb = UI->ProgressStart(lst.size(),"Append object: ");
        for (AStringIt it=lst.begin(); it!=lst.end(); it++){
            string256 namebuffer;
            Scene->GenObjectName(OBJCLASS_SCENEOBJECT, namebuffer, it->c_str());
            CSceneObject *obj = xr_new<CSceneObject>((LPVOID)0,namebuffer);
            CEditableObject* ref = obj->SetReference(it->c_str());
            if (!ref){
                ELog.DlgMsg(mtError,"TfraObject:: Can't load reference object.");
                xr_delete(obj);
                return;
            }
/*            if (ref->IsDynamic()){
                ELog.DlgMsg(mtError,"TfraObject:: Can't assign dynamic object.");
                xr_delete(obj);
                return;
            }
*/
            obj->MoveTo(pos,up);
            Scene->AppendObject( obj );
        }         
        UI->ProgressEnd(pb);
    }
}

void IM_FrameObject::MultiSelByRefObject(bool clear_prev)
{
    ObjectList 	objlist;
    LPU32Vec 	sellist;
    if (Scene->GetQueryObjects(objlist,OBJCLASS_SCENEOBJECT,1,1,-1)){
    	for (ObjectIt it=objlist.begin(); it!=objlist.end(); it++){
	        LPCSTR N = ((CSceneObject*)*it)->RefName();
            ObjectIt _F = Scene->FirstObj(OBJCLASS_SCENEOBJECT);
            ObjectIt _E = Scene->LastObj(OBJCLASS_SCENEOBJECT);
            for(;_F!=_E;_F++){
	            CSceneObject *_O = (CSceneObject *)(*_F);
                if((*_F)->Visible()&&_O->RefCompare(N)){
                	if (clear_prev){
                    	_O->Select( false );
	                    sellist.push_back((u32*)_O);
                    }else{
                    	if (!_O->Selected())
                        	sellist.push_back((u32*)_O);
                    }
                }
            }
        }
        std::sort			(sellist.begin(),sellist.end());
        sellist.erase		(std::unique(sellist.begin(),sellist.end()),sellist.end());
        std::random_shuffle	(sellist.begin(),sellist.end());
        int max_k		= iFloor(float(sellist.size())/100.f*float(m_select_percent)+0.5f);
        int k			= 0;
        for (LPU32It o_it=sellist.begin(); k<max_k; o_it++,k++){
            CSceneObject *_O = (CSceneObject *)(*o_it);
            _O->Select( true );
        }
    }
}

void IM_FrameObject::SelByRefObject(bool flag)
{
    ObjectList objlist;
//    LPCSTR sel_name=0;
//    if (Scene->GetQueryObjects(objlist,OBJCLASS_SCENEOBJECT,1,1,-1))
//        sel_name = ((CSceneObject*)objlist.front())->GetRefName();
	LPCSTR N=Current();
//    if (!TfrmChoseItem::SelectItem(TfrmChoseItem::smObject,N,1,sel_name)) return;
	if (N){
        ObjectIt _F = Scene->FirstObj(OBJCLASS_SCENEOBJECT);
        ObjectIt _E = Scene->LastObj(OBJCLASS_SCENEOBJECT);
        for(;_F!=_E;_F++){
            if((*_F)->Visible() ){
                CSceneObject *_O = (CSceneObject *)(*_F);
                if(_O->RefCompare(N)) _O->Select( flag );
            }
        }
    }
}

void IM_FrameObject::RefreshList()
{
	m_objects_tree.Clear();

	FS_FileSet objects;
    Lib.GetObjects(objects);

    for(FS_FileSetIt it = objects.begin(), end = objects.end(); it != end; it++)
    {
    	m_objects_tree.Add(codepage2utf8(it->name).c_str(), it->name.c_str());
    }
}

void IM_FrameObject::OnAdd()
{
	m_parent_tool = dynamic_cast<ESceneObjectTool*>(Scene->GetTool(OBJCLASS_SCENEOBJECT));
	VERIFY(m_parent_tool);
	RefreshList();

    IM_Storage storage(false, "level.ini", "IM_FrameObject");

    m_random_append = storage.GetBool("random_append");
    m_select_percent = storage.GetInt("select_percent", 0);

	m_objects_tree.Select(storage.GetString("selected_object").c_str(), true);
}

void IM_FrameObject::OnRemove()
{
	IM_Storage storage(true, "level.ini", "IM_FrameObject");

    storage.PutBool("random_append", m_random_append);
    storage.PutInt("select_percent", m_select_percent);

    shared_str sel_obj = m_objects_tree.GetSelected();
    storage.PutString("selected_object", !sel_obj ? "" : sel_obj.c_str());
}

void IM_FrameObject::Render()
{
    if(ImGui::CollapsingHeader("Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
        if(ImGui::MenuItem("Multiple Append"))
        	MultipleAppend();

        ImGui::Separator();

        ImGui::Columns(2, "obj_commands", false);

        if(ImGui::MenuItem("Random Append", NULL, m_random_append))
        {
        	m_random_append = !m_random_append;
            m_parent_tool->ActivateAppendRandom(m_random_append);
        }

        ImGui::NextColumn();

        if(ImGui::MenuItem("Random Props..."))
        	m_parent_tool->FillAppendRandomProperties();

        ImGui::Columns(1);
    }

    if(ImGui::CollapsingHeader("Reference select",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2, "ref_select", false);

    	ImGui::TextUnformatted("Select by Current:\t");
        ImGui::TextUnformatted("Select by Selected:\t");

        ImGui::NextColumn();

        if(ImGui::Button("+", ImVec2(40,0)))
        	SelByRefObject(true);
        ImGui::SameLine();
        if(ImGui::Button("-", ImVec2(40,0)))
        	SelByRefObject(false);

        if(ImGui::Button("=%", ImVec2(40,0)))
        	MultiSelByRefObject(true);
        ImGui::SameLine();
        if(ImGui::Button("+%", ImVec2(40,0)))
        	MultiSelByRefObject(false);

        ImGui::Columns(1);

        ImGui::SliderInt("%", &m_select_percent, 0, 100);
    }

    if(ImGui::CollapsingHeader("Current object",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::MenuItem("Select..."))
        {
        	LPCSTR result;
        	if(TfrmChoseItem::SelectItem(smObject, result, 1, m_objects_tree.GetSelected().c_str()))
            	m_objects_tree.Select(result, true);
        }

        if(ImGui::MenuItem("Refresh list"))
			RefreshList();

        ImGui::BeginChild("objects", ImVec2(0,0), true);
        m_objects_tree.Render();
        ImGui::EndChild();
    }
}

