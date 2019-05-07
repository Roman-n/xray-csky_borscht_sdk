#include "stdafx.h"
#pragma hdrstop

#include "IM_ImageEditor.h"
#include "ImageManager.h"
#include "imgui.h"
#include "ETextureParams.h"
#include "ui_main.h"

#pragma package(smart_init)

ECORE_API IM_ImageEditor imImageEditor;

IM_ImageEditor::IM_ImageEditor()
	: m_open(false),
	m_title("Image Editor"),
	m_importmode(false),
	m_needupdate(false),
	m_thm(THUMB_WIDTH, THUMB_HEIGHT)
{
	m_items.OnItemsFocused.bind(this, &IM_ImageEditor::OnItemsFocused);
}

void IM_ImageEditor::Open(bool import)
{
	if(!m_open)
	{
		m_importmode = import;

		if(m_importmode)
		{
			m_title = "Import Textures";
			int new_cnt = ImageLib.GetLocalNewTextures(texture_map);
			if(new_cnt < 1)
			{
				ELog.DlgMsg(mtInformation, "Can't find new textures");
				return;
			}
		}
		else
		{
			m_title = "Image Editor";
			ImageLib.GetTexturesRaw(texture_map);
		}

		ListItemsVec 			items;
		SPBItem* pb				= UI->ProgressStart		(texture_map.size(),"Fill list...");
		// fill
		FS_FileSetIt it         = texture_map.begin();
		FS_FileSetIt _E         = texture_map.end();
		for (; it!=_E; it++)
		{
			pb->Inc				();
			ListItem* I			= LHelper().CreateItem(items,it->name.c_str(),0);
			I->m_Object			= (void*)(FindUsedTHM(it->name.c_str()));
			R_ASSERT2			(I->m_Object, it->name.c_str());
		}
		UI->ProgressEnd			(pb);
		m_items.AssignItems 	(items,false,true);

		UI->AddIMWindow(this);
		m_open = true;
    }
}

void IM_ImageEditor::Close()
{
	texture_map.clear();
	UI->RemoveIMWindow(this);
	m_open = false;
}

void IM_ImageEditor::Render()
{
	if(!m_open)
	{
		Close();
		return;
	}

	if(!ImGui::Begin(m_title.c_str(), &m_open))
	{
		ImGui::End();
		return;
	}

	if(m_needupdate)
	{
		ListItemsVec selected;
		m_items.GetSelected(selected);
		OnItemsFocused(selected);

		m_needupdate = false;
    }

	ImGui::Columns(2);

	ImGui::BeginChild("ItemList", ImVec2(0,0), true);
	m_items.Render();
	ImGui::EndChild();

	ImGui::NextColumn();

	ImGui::BeginChild("THM", ImVec2(m_thm.Width()+16,m_thm.Height()+16), true);
	m_thm.Render();
	ImGui::EndChild();

	ImGui::BeginChild("ItemProps", ImVec2(0,0), true);
	m_props.Render();
	ImGui::EndChild();

	ImGui::Columns(1);

	ImGui::End();
}

ETextureThumbnail* IM_ImageEditor::FindUsedTHM(shared_str name)
{
    THMMapIt it = m_THM_Used.find(name);
	if (it!=m_THM_Used.end())
		return it->second;

    ETextureThumbnail* thm = xr_new<ETextureThumbnail>(name.c_str(), false);
    m_THM_Used[name]			= thm;

	if(m_importmode)
    {
        xr_string fn            = name.c_str();
        ImageLib.UpdateFileName (fn);

        if (!thm->Load(name.c_str(), _import_))
        {
            bool bLoad                      = thm->Load(fn.c_str(),_game_textures_);
            ImageLib.CreateTextureThumbnail (thm, name.c_str(), _import_, !bLoad);
        }
    }else
    {
    	thm->Load();
    }
    return thm;
}

void IM_ImageEditor::SaveUsedTHM()
{
	for(THMMapIt t_it=m_THM_Used.begin(); t_it!=m_THM_Used.end(); ++t_it)
    { 
	//	if (modif_map.find(FS_File(t_it->second->SrcName()))!=modif_map.end())
	//    	t_it->second->Save();
    }
}

void IM_ImageEditor::DestroyUsedTHM()
{
    for (THMMapIt it = m_THM_Used.begin(); it!=m_THM_Used.end(); ++it)
    	xr_delete(it->second);
    m_THM_Used.clear();
}

void __stdcall IM_ImageEditor::OnItemsFocused(ListItemsVec& items)
{
	PropItemVec props;

//	RegisterModifiedTHM	();
	m_THM_Current.clear	();
    
	if (!items.empty())
    {
	    for (ListItemsIt it=items.begin(); it!=items.end(); it++)
		{
            ListItem* prop = *it;
            if (prop){
				ETextureThumbnail* thm=0;

				thm = FindUsedTHM(prop->Key());
				m_THM_Current.push_back	                (thm);
                //prop->tag								= thm->_Format().type;

                // fill prop
				thm->FillProp							(props, PropValue::TOnChange(this,&IM_ImageEditor::OnTypeChange));

				if (thm->_Format().type==STextureParams::ttCubeMap)
                {
					ButtonValue* B		= PHelper().CreateButton (props, "CubeMap\\Edit", "Make Small", 0);
					//B->OnBtnClickEvent.bind(this,&TfrmImageLib::OnCubeMapBtnClick);
                }
            }
        }
    }

	if(m_THM_Current.size() == 1)
	{
		HDC hdc = m_thm.BeginPaint();
		m_THM_Current.back()->Draw(hdc, Irect().set(0,0,m_thm.Width(),m_thm.Height()));
		m_thm.EndPaint();
	}
	else
		m_thm.Clear();

	m_props.AssignItems(props, false, false);
}

void __stdcall IM_ImageEditor::OnTypeChange(PropValue*)
{
	m_needupdate = true;
}

