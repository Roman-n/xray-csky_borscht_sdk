#include "stdafx.h"
#pragma hdrstop

#include "IM_SoundEditor.h"
#include "imgui.h"
#include "..\Editor\ui_main.h"
#include "..\Editor\SoundManager.h"
#include "..\..\..\xrSound\soundrender_source.h"

#pragma package(smart_init)

ECORE_API IM_SoundEditor imSoundEditor;

void IM_SoundEditor::Open()
{
	if(!m_open)
	{
		UI->AddIMWindow(this);

		m_open = true;
		InitItemsList();

		modif_map.clear	();
		m_Flags.zero	();
		if (!FS.can_write_to_alias(_sounds_)){
			Log				("#!You don't have permisions to modify sounds.");
			m_Flags.set		(flReadOnly,TRUE);
			bAutoPlay		= TRUE;
		}
	}
}

void IM_SoundEditor::Close()
{
	UI->RemoveIMWindow(this);
	m_open = false;
}

void IM_SoundEditor::OnRemove()
{
	modif_map.clear();
	DestroyUsedTHM();
	m_items.Clear();
	m_props.Clear();
	m_Snd.destroy();
}

void IM_SoundEditor::Render()
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

	ImGui::Columns(2, NULL, true);

	ImGui::BeginChild("ItemList", ImVec2(0, 0), true);
	m_items.Render();
	ImGui::EndChild();

	ImGui::NextColumn();

	ImGui::BeginChild("ItemProps", ImVec2(0, -25), true);
	m_props.Render();
	ImGui::EndChild();

	if(!m_Flags.is(flReadOnly))
	{
		if(ImGui::Button("OK", ImVec2(80, 0)))
		{
			UpdateLib();
			m_open = false;
		}

		ImGui::SameLine();
		if(ImGui::Button("Cancel", ImVec2(80, 0)))
		{
			m_open = false;
		}
	}

	ImGui::Columns(1);

	ImGui::End();
}

void IM_SoundEditor::InitItemsList()
{
    FS_FileSet		sound_map;
    SndLib->GetSounds(sound_map,TRUE);

	ListItemsVec items;

    // fill items
	FS_FileSetIt it = sound_map.begin();
	FS_FileSetIt _E = sound_map.end();
    for (; it!=_E; it++)
		LHelper().CreateItem(items,it->name.c_str(),0);

	m_items.AssignItems(items, false, false);
}

ESoundThumbnail* IM_SoundEditor::FindUsedTHM(LPCSTR name)
{
	for (THMIt it=m_THM_Used.begin(); it!=m_THM_Used.end(); it++)
    	if (0==strcmp((*it)->SrcName(),name)) return *it;
    return 0;
}

void IM_SoundEditor::SaveUsedTHM()
{
	int m_age 		= time(NULL);
	for (THMIt t_it=m_THM_Used.begin(); t_it!=m_THM_Used.end(); t_it++)
		(*t_it)->Save(m_age,0);
}

void IM_SoundEditor::DestroyUsedTHM()
{
    for (THMIt it=m_THM_Used.begin(); it!=m_THM_Used.end(); it++)
    	xr_delete(*it);
    m_THM_Used.clear();
}

void IM_SoundEditor::AppendModif(LPCSTR nm)
{
    FS_File 		dest;
	string_path		fname;
	FS.update_path	(fname,_sounds_,ChangeFileExt(nm,".wav").c_str());
	BOOL bFind		= FS.file_find(fname,dest); R_ASSERT(bFind);
	modif_map.insert(dest);
}

void IM_SoundEditor::RegisterModifiedTHM()
{
	if (m_props.IsModified()){
		for (THMIt t_it=m_THM_Current.begin(); t_it!=m_THM_Current.end(); t_it++){
//.            (*t_it)->Save	(0,0);
			AppendModif		((*t_it)->SrcName());
		}
	}
}

void IM_SoundEditor::UpdateLib()
{
    RegisterModifiedTHM		();
    SaveUsedTHM				();
    // save game sounds
    if (modif_map.size()){
		//LockForm			();
        SndLib->SynchronizeSounds	(true,true,true,&modif_map,0);
//		SndLib->ChangeFileAgeTo		(&modif_map,time(NULL));
		//UnlockForm			();
        SndLib->RefreshSounds(false);
		modif_map.clear		();
    }
}

void __stdcall IM_SoundEditor::OnItemsFocused(ListItemsVec& items)
{
	PropItemVec props;

    RegisterModifiedTHM	();
    m_Snd.destroy		();
    m_THM_Current.clear	();
                                          
	if (!items.empty()){
	    for (ListItemsIt it=items.begin(); it!=items.end(); it++){
            ListItem* prop = *it;
            if (prop){
            	ESoundThumbnail* thm=FindUsedTHM(prop->Key());
                if (!thm) m_THM_Used.push_back(thm=xr_new<ESoundThumbnail>(prop->Key()));
                m_THM_Current.push_back(thm);
                thm->FillProp		(props);
            }
        }
    }

	ButtonValue* B=0;
    if (m_THM_Current.size()==1)
    {
        ESoundThumbnail* thm=m_THM_Current.back();
        u32 size=0;
		float time=0;
        PlaySound(thm->SrcName(), size, time);

		CanvasValue* C=0;
		C=PHelper().CreateCanvas	(props,"Attenuation",	"", 64);
		C->tag						= (int)this;
		C->OnDrawCanvasEvent.bind	(this,&IM_SoundEditor::OnAttenuationDraw);
//		C->OnTestEqual.bind			(this,&TfrmSoundLib::OnPointDataTestEqual);
		B=PHelper().CreateButton	(props,"Auto Att",		"By Min,By Max",ButtonValue::flFirstOnly);
		B->OnBtnClickEvent.bind		(this,&IM_SoundEditor::OnAttClick);
        
        PHelper().CreateCaption		(props,"File Length",	shared_str().sprintf("%.2f Kb",float(size)/1024.f));
        PHelper().CreateCaption		(props,"Total Time", 	shared_str().sprintf("%.2f sec",time));
		if (!m_Flags.is(flReadOnly)){
	        B=PHelper().CreateButton(props,"Control",		"Play,Stop",ButtonValue::flFirstOnly);
			B->OnBtnClickEvent.bind	(this,&IM_SoundEditor::OnControlClick);
        }
    }
    if (!m_Flags.is(flReadOnly))
    {
	    B=PHelper().CreateButton	(props,"Auto Play",		bAutoPlay?"on":"off",ButtonValue::flFirstOnly);
		B->OnBtnClickEvent.bind		(this,&IM_SoundEditor::OnControl2Click);
    }

    if (!m_Flags.is(flReadOnly) && m_THM_Current.size())
    {
        B=PHelper().CreateButton(props,"MANAGE", "SyncCurrent", ButtonValue::flFirstOnly);
		B->OnBtnClickEvent.bind	(this,&IM_SoundEditor::OnSyncCurrentClick);
    }

	m_props.AssignItems(props, false, false);
}

void __stdcall IM_SoundEditor::OnControlClick(ButtonValue* V, bool& bModif, bool& bSafe)
{
	switch (V->btn_num){
	case 0: m_Snd.play(0,sm_2D); 	break;
	case 1: m_Snd.stop();			break;
	case 2:{
		bAutoPlay=!bAutoPlay;
		V->value[V->btn_num] = shared_str().sprintf("Auto (%s)",bAutoPlay?"on":"off");
	}break;
	}
	bModif = false;
}

void __stdcall IM_SoundEditor::OnControl2Click(ButtonValue* V, bool& bModif, bool& bSafe)
{
	switch (V->btn_num){
	case 0:{
		bAutoPlay=!bAutoPlay;
		V->value[V->btn_num] = bAutoPlay?"on":"off";
	}break;
	}
	bModif = false;
}

void __stdcall IM_SoundEditor::OnSyncCurrentClick(ButtonValue* V, bool& bModif, bool& bSafe)
{
//.
	THMIt it 	= m_THM_Current.begin();
	THMIt it_e 	= m_THM_Current.end();

    for(;it!=it_e; ++it)
    {
    	ESoundThumbnail* pTHM 		= *it;

        string_path             src_name, game_name;
        FS.update_path			(src_name,_sounds_,pTHM->SrcName());
        strconcat				(sizeof(src_name),src_name,src_name,".wav");

        FS.update_path			(game_name,_game_sounds_,pTHM->SrcName());
        strconcat				(sizeof(game_name),game_name,game_name,".ogg");

        Msg						("synchronizing [%s]", game_name);
		SndLib->MakeGameSound	(pTHM, src_name, game_name);
    }
    Msg	("Done.");
}

void __stdcall IM_SoundEditor::OnAttClick(ButtonValue* V, bool& bModif, bool& bSafe)
{
	bModif = true;
	ESoundThumbnail* thm	= m_THM_Current.back();
	switch (V->btn_num){
	case 0:{
		float dist			= thm->MinDist()/(0.01f*psSoundRolloff);
		thm->SetMaxDist		(dist+0.1f*dist);
	}break;
	case 1:{
		float dist			= psSoundRolloff*(thm->MaxDist()-(0.1f/1.1f)*thm->MaxDist())*0.01f;
		thm->SetMinDist		(dist);
	}break;
	}
}

#define X_GRID 10
#define Y_GRID 5
void __stdcall IM_SoundEditor::OnAttenuationDraw(CanvasValue* sender, void* _canvas, const Irect& _rect)
{
	TCanvas* canvas 	= (TCanvas*)_canvas;
    const TRect& rect	= *((TRect*)&_rect);
//	canvas
    int w = rect.Width();
    int h = rect.Height();
    int x0= rect.left;
    int y0= rect.top;

    canvas->Brush->Color = clBlack;
    canvas->FillRect(rect);
    canvas->Pen->Color = TColor(0x00006600);
    canvas->MoveTo(x0,y0);
    for (int i=0; i<X_GRID+1; i++){
        canvas->LineTo(x0+i*w/X_GRID,y0+h);
        canvas->MoveTo(x0+(i+1)*w/X_GRID,y0+0);
    }
    canvas->MoveTo(x0+0,y0+0);
    for (int j=0; j<Y_GRID+1; j++){
        canvas->LineTo(x0+w,y0+j*h/Y_GRID);
        canvas->MoveTo(x0+0,y0+(j+1)*h/Y_GRID);
    }
    canvas->Pen->Color = clYellow;
    canvas->MoveTo(x0+0,y0+iFloor(float(h)-float(h)*0.01f)); // snd cull = 0.01f
    canvas->LineTo(x0+w,y0+iFloor(float(h)-float(h)*0.01f));

	ESoundThumbnail* thm	= m_THM_Current.back();
	float d_cost 			= thm->MaxDist()/w;
	AnsiString temp;
//    float v = m_D3D.range;
//    temp.sprintf("Range = %.2f",v); lbRange->Caption = temp;
	canvas->Pen->Color = clLime;
	for (int d=1; d<w; d++){
		float R = d*d_cost;
		float b = thm->MinDist()/(psSoundRolloff*R);
//		float b = m_Brightness/(m_Attenuation0+m_Attenuation1*R+m_Attenuation2*R*R);
		float bb = h-(h*b);
		int y = iFloor(y0+bb); clamp(y,int(rect.Top),int(rect.Bottom));
		if (1==d)	canvas->MoveTo(x0+d,y);
		else		canvas->LineTo(x0+d,y);
	}
}

void __stdcall IM_SoundEditor::RemoveSound(LPCSTR fname, EItemType type, bool& res)
{
	// delete it from modif map
	FS_FileSetIt it=modif_map.find(FS_File(fname));
	if (it!=modif_map.end()) modif_map.erase(it);
	// remove sound source
	res = SndLib->RemoveSound(fname,type);
}

void __stdcall IM_SoundEditor::RenameSound(LPCSTR p0, LPCSTR p1, EItemType type)
{
	// rename sound source
	SndLib->RenameSound(p0,p1,type);
	// delete old from map
	FS_FileSetIt old_it=modif_map.find(FS_File(p0));
	if (old_it!=modif_map.end()){
		modif_map.erase	(old_it);
		AppendModif		(p1);
	}
}

void IM_SoundEditor::PlaySound(LPCSTR name, u32& size, float& time)
{
	string_path fname;
    FS.update_path			(fname,_game_sounds_,ChangeFileExt(name,".ogg").c_str());
    FS_File F;
    if (FS.file_find(fname,F))
    {
		m_Snd.create		(name,st_Effect,sg_Undefined);
		m_Snd.play			(0,sm_2D);
		CSoundRender_Source* src= (CSoundRender_Source*)m_Snd._handle(); VERIFY(src);
		size				= F.size;
		time				= src->length_sec();
		if (!bAutoPlay)		m_Snd.stop();
	}
}
