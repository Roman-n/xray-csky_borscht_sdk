#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/imgui.h"
#include "../ECore/ImGui/utf8.h"

#include "IM_FrameSpawn.h"
#include "SpawnPoint.h"
#include "Scene.h"
#include "../ECore/Editor/ui_main.h"
#include "ui_leveltools.h"

#pragma package(smart_init)

void IM_FrameSpawn::RefreshList()
{
	m_spawns.Clear();

    CInifile::Root& data = pSettings->sections();
    for(CInifile::RootIt it=data.begin(); it!=data.end(); it++)
    {
    	LPCSTR val;
    	if ((*it)->line_exist("$spawn",&val))
        {
        	shared_str caption	= pSettings->r_string_wb((*it)->Name,"$spawn");
        	shared_str sect		= (*it)->Name;

            if (caption.size())
				m_spawns.Add(codepage2utf8(*caption).c_str(), sect.c_str());
        }
    }

    m_spawns.Add(RPOINT_CHOOSE_NAME, RPOINT_CHOOSE_NAME);
    m_spawns.Add(ENVMOD_CHOOSE_NAME, ENVMOD_CHOOSE_NAME);
}

LPCSTR IM_FrameSpawn::Current()
{
	if(m_spawns.GetSelectedCount())
    	return m_spawns.GetSelected().c_str();
    else
    	return NULL;
}

void IM_FrameSpawn::MultiSelByRefObject(bool clear_prev)
{
    ObjectList 	objlist;
    LPU32Vec 	sellist;
    if (Scene->GetQueryObjects(objlist,OBJCLASS_SPAWNPOINT,1,1,-1)){
    	for (ObjectIt it=objlist.begin(); it!=objlist.end(); it++){
	        LPCSTR N = ((CSpawnPoint*)*it)->RefName();
            ObjectIt _F = Scene->FirstObj(OBJCLASS_SPAWNPOINT);
            ObjectIt _E = Scene->LastObj(OBJCLASS_SPAWNPOINT);
            for(;_F!=_E;_F++){
	            CSpawnPoint *_O = (CSpawnPoint *)(*_F);
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
            CSpawnPoint *_O = (CSpawnPoint *)(*o_it);
            _O->Select( true );
        }
    }
}

void IM_FrameSpawn::SelByRefObject(bool flag)
{
    ObjectList objlist;
	LPCSTR N=Current();
	if (N){
        ObjectIt _F = Scene->FirstObj(OBJCLASS_SPAWNPOINT);
        ObjectIt _E = Scene->LastObj(OBJCLASS_SPAWNPOINT);
        for(;_F!=_E;_F++){
            if((*_F)->Visible() ){
                CSpawnPoint *_O = (CSpawnPoint*)(*_F);
                if(_O->RefCompare(N)) _O->Select( flag );
            }
        }
    }
}

void IM_FrameSpawn::OnAdd()
{
	RefreshList();

    IM_Storage storage(false, "level.ini", "IM_FrameSpawn");
    m_select_percent = storage.GetInt("select_percent", 0);
    m_spawns.Select(storage.GetString("current").c_str(), true);
}

void IM_FrameSpawn::OnRemove()
{
	IM_Storage storage(true, "level.ini", "IM_FrameSpawn");
    storage.PutInt("select_percent", m_select_percent);
    storage.PutString("current", Current()?Current():"");
}

void IM_FrameSpawn::Render()
{
	if(ImGui::CollapsingHeader("Reference Select",
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

	if(ImGui::CollapsingHeader("Commands",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::Selectable("Attach Object...", &m_attach_object))
        {
        	if(m_attach_object)
            	ExecCommand(COMMAND_CHANGE_ACTION, etaAdd);
        }

        if(ImGui::MenuItem("Detach Object"))
		{
            ObjectList lst;
    		if (Scene->GetQueryObjects(lst,OBJCLASS_SPAWNPOINT,1,1,0)){
    			for (ObjectIt it=lst.begin(); it!=lst.end(); it++){
	        		CSpawnPoint* O = dynamic_cast<CSpawnPoint*>(*it); R_ASSERT(O);
        			O->DetachObject();
        		}
    		}
    	}
    }

    if(ImGui::CollapsingHeader("Current Spawn",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::BeginChild("spawns", ImVec2(0,0), true);
        m_spawns.Render();
        ImGui::EndChild();
    }
}
