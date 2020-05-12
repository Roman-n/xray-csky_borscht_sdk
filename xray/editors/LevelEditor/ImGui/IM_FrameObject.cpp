#include "stdafx.h"
#pragma hdrstop

#include "IM_FrameObject.h"
#include "../ECore/ImGui/ImGui.h"
#include "../ECore/ImGui/utf8.h"
#include "../ECore/ImGui/IM_ChooseForm.h"
#include "../ECore/Editor/Library.h"
#include "../Edit/Scene.h"
#include "../Edit/SceneObject.h"
#include "../Edit/ESceneObjectTools.h"
#include "../ECore/Editor/ui_main.h"
#include "../ECore/Editor/EThumbnail.h"
#include <random>

LPCSTR IM_FrameObject::Current()
{
	if(m_objects_tree.GetSelectedCount())
    	return m_objects_tree.GetSelected().c_str();
    else
    	return NULL;
}

#ifndef __BORLANDC__
AnsiString& _Trim( AnsiString& str )
{
	return str=Trim(str);
}

LPCSTR _CopyVal ( LPCSTR src, AnsiString& dst, char separator )
{
	LPCSTR	p;
	u32		n;
	p			= strchr	( src, separator );
	n			= (p>0) ? (p-src) : xr_strlen(src);
	dst			= src;
	dst			= dst.substr(n);
	return		dst.c_str();
}

LPCSTR _GetItem ( LPCSTR src, int index, AnsiString& dst, char separator=',', LPCSTR def="", bool trim=true )
{
	LPCSTR	ptr;
	ptr			= _SetPos	( src, index, separator );
	if( ptr )	_CopyVal	( ptr, dst, separator );
	else	dst = def;
	if (trim)	dst			= Trim(dst);
	return		dst.c_str();
}

void _SequenceToList(AStringVec& lst, LPCSTR in, char separator=',')
{
	lst.clear();
	int t_cnt=_GetItemCount(in,separator);
	AnsiString T;
	for (int i=0; i<t_cnt; i++){
		_GetItem(in,i,T,separator,0);
        _Trim(T);
        if (!T.empty()) lst.push_back(T);
	}
}
#endif

void IM_FrameObject::MultipleAppend(IM_ChooseForm* form)
{
	{
    	Fvector pos={0.f,0.f,0.f};
    	Fvector up={0.f,1.f,0.f};
        Scene->SelectObjects(false,OBJCLASS_SCENEOBJECT);
	    AStringVec lst;
    	_SequenceToList(lst,*form->GetSelected());
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

void IM_FrameObject::SelectObject(IM_ChooseForm* form)
{
    m_objects_tree.Select(*form->GetSelected());
}

void IM_FrameObject::DrawThumbnail(LPCSTR name, HDC hdc, const Irect& r)
{
	EObjectThumbnail* thm	= xr_new<EObjectThumbnail>(name);
    thm->Draw				(hdc,r);
    xr_delete				(thm);
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
        std::shuffle	    (sellist.begin(),sellist.end(), std::random_device());
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

    IM_Storage s(false, "level.ini", "IM_FrameObject");

    m_random_append = s.GetBool("random_append");
    m_select_percent = s.GetInt("select_percent", 0);

	m_objects_tree.Select(s.GetString("selected_object").c_str(), true);

    m_show_commands = s.GetBool("show_commands_panel", true);
    m_show_refselect = s.GetBool("show_refselect_panel", true);
    m_show_currentobject = s.GetBool("show_currentobject_panel", true);
}

void IM_FrameObject::OnRemove()
{
	IM_Storage s(true, "level.ini", "IM_FrameObject");

    s.PutBool("random_append", m_random_append);
    s.PutInt("select_percent", m_select_percent);

    shared_str sel_obj = m_objects_tree.GetSelected();
    s.PutString("selected_object", !sel_obj ? "" : sel_obj.c_str());

    s.PutBool("show_commands_panel", m_show_commands);
    s.PutBool("show_refselect_panel", m_show_refselect);
    s.PutBool("show_currentobject_panel", m_show_currentobject);
}

void IM_FrameObject::Render()
{
    if(ImGui::CollapsingPanel("Commands", &m_show_commands))
    {
        if(ImGui::MenuItem("Multiple Append"))
        {
			IM_ChooseForm* cf = xr_new<IM_ChooseForm>(smObject, 1024);
			cf->OnOK.bind(this, &IM_FrameObject::MultipleAppend);

			UI->AddIMWindow(cf);
        }

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

    if(ImGui::CollapsingPanel("Reference select", &m_show_refselect))
    {
    	ImGui::Columns(2, "ref_select", false);

        ImGui::AlignTextToFramePadding();
    	ImGui::TextUnformatted("Select by Current:\t");
        ImGui::AlignTextToFramePadding();
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

    if(ImGui::CollapsingPanel("Current object", &m_show_currentobject))
    {
		if(ImGui::MenuItem("Select..."))
		{
			IM_ChooseForm* cf = new IM_ChooseForm(smObject, 1);
            cf->OnOK.bind(this, &IM_FrameObject::SelectObject);
			UI->AddIMWindow(cf);
        }

        if(ImGui::MenuItem("Refresh list"))
			RefreshList();

		ImGui::Checkbox("Draw thm", &m_objects_tree.DrawThumbnails);
        ImGui::BeginChild("objects", ImVec2(0,0), true);
        m_objects_tree.Render();
        ImGui::EndChild();
    }
}

