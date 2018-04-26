#include "stdafx.h"
#pragma hdrstop

#include "IM_LeftBar.h"
#include "../ECore/ImGui/utf8.h"
#include "../ECore/ImGui/imgui.h"

#include "UI_LevelMain.h"
#include "UI_LevelTools.h"
#include "scene.h"
#include "CustomObject.h"
#include "FrmDBXPacker.h"

void IM_LeftBar::OnAdd()
{
	m_title = wide2utf8(L"�������� ������� X-Ray 1.8");

    fraObject.OnAdd();
    fraLight.OnAdd();
    fraFogVol.OnAdd();
    fraDetail.OnAdd();
    fraSector.OnAdd();
    fraPortal.OnAdd();
    fraShape.OnAdd();
    fraPS.OnAdd();
    fraWayPoint.OnAdd();
    fraSpawn.OnAdd();
    fraGroup.OnAdd();
    fraAIMap.OnAdd();

	IM_Storage storage(false, "level.ini", "IM_LeftBar");

    m_enable_snap_list = storage.GetBool("enable_snap_list");
    m_select_snap_objs_mode = storage.GetBool("select_snap_objs_mode");
    m_detach_tool_frame = storage.GetBool("detach_tool_frame");
}

void IM_LeftBar::OnRemove()
{
    fraObject.OnRemove();
    fraLight.OnRemove();
    fraFogVol.OnRemove();
    fraDetail.OnRemove();
    fraSector.OnRemove();
    fraPortal.OnRemove();
    fraShape.OnRemove();
    fraPS.OnRemove();
    fraWayPoint.OnRemove();
    fraSpawn.OnRemove();
    fraGroup.OnRemove();
    fraAIMap.OnRemove();

	IM_Storage storage(true, "level.ini", "IM_LeftBar");

    storage.PutBool("enable_snap_list", m_enable_snap_list);
    storage.PutBool("select_snap_objs_mode", m_select_snap_objs_mode);
    storage.PutBool("detach_tool_frame", m_detach_tool_frame);
}

void IM_LeftBar::Render()
{
	ImGui::Begin("Level Editor", NULL);

    ImGui::TextUnformatted(&*m_title.begin(), &*m_title.end());

    if(ImGui::CollapsingHeader("Scene",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
		if(ImGui::BeginMenu("File"))
        {
        	if(ImGui::MenuItem("Clear"))
            	ExecCommand(COMMAND_CLEAR);
        	if(ImGui::MenuItem("Open"))
            	ExecCommand(COMMAND_LOAD);
        	if(ImGui::MenuItem("Save"))
            	ExecCommand(COMMAND_SAVE);
        	if(ImGui::MenuItem("Save as"))
            	ExecCommand(COMMAND_SAVE, 0, 1);
            ImGui::Separator();
            if(ImGui::MenuItem("Open selection"))
            	ExecCommand(COMMAND_LOAD_SELECTION);
            if(ImGui::MenuItem("Save selection as"))
            	ExecCommand(COMMAND_SAVE_SELECTION);
            ImGui::Separator();
            if(ImGui::MenuItem("Make pack"))
            	TDB_packer::ActivatePacker();
            ImGui::Separator();
            if(ImGui::BeginMenu("Open recent", !!EPrefs->scene_recent_count))
            {
            	for(AStringIt it = EPrefs->scene_recent_list.begin(); it != EPrefs->scene_recent_list.end(); it++)
                {
                	if(ImGui::MenuItem(it->c_str()))
                    	ExecCommand(COMMAND_LOAD, xr_string(it->c_str()));
                }

            	ImGui::EndMenu();
            }
            ImGui::Separator();
        	if(ImGui::MenuItem("Quit"))
            	ExecCommand(COMMAND_QUIT);

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Scene"))
        {
        	if(ImGui::MenuItem("Options"))
            	ExecCommand(COMMAND_OPTIONS, CCommandVar("Scene"));
            ImGui::Separator();
            if(ImGui::MenuItem("Validate"))
            	ExecCommand(COMMAND_VALIDATE_SCENE);
            ImGui::Separator();
            if(ImGui::MenuItem("Summary Info"))
            {
            	ExecCommand(COMMAND_CLEAR_SCENE_SUMMARY);
                ExecCommand(COMMAND_COLLECT_SCENE_SUMMARY);
                ExecCommand(COMMAND_SHOW_SCENE_SUMMARY);
            }
            if(ImGui::MenuItem("Highlight Texture..."))
            	ExecCommand(COMMAND_SCENE_HIGHLIGHT_TEXTURE);
            ImGui::Separator();
            if(ImGui::MenuItem("Clear Debug Draw"))
            	ExecCommand(COMMAND_CLEAR_DEBUG_DRAW);
            ImGui::Separator();
            if(ImGui::MenuItem("Export entire Scene as Obj"))
            	Scene->ExportObj(false);
            if(ImGui::MenuItem("Expoty selection as Obj"))
            	Scene->ExportObj(true);

        	ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Compile"))
        {
        	if(ImGui::MenuItem("Build"))
            	ExecCommand(COMMAND_BUILD);
            ImGui::Separator();
            if(ImGui::MenuItem("Make game"))
            	ExecCommand(COMMAND_MAKE_GAME);
            if(ImGui::MenuItem("Make details"))
            	ExecCommand(COMMAND_MAKE_DETAILS);
            if(ImGui::MenuItem("Make HOM"))
            	ExecCommand(COMMAND_MAKE_HOM);
            if(ImGui::MenuItem("Make Sound Occluder"))
            	ExecCommand(COMMAND_MAKE_SOM);
            if(ImGui::MenuItem("Make AI-map"))
            	ExecCommand(COMMAND_MAKE_AIMAP);
            ImGui::Separator();
            if(ImGui::MenuItem("Import error list"))
            	ExecCommand(COMMAND_IMPORT_COMPILER_ERROR);
            if(ImGui::MenuItem("Export error list"))
            	ExecCommand(COMMAND_EXPORT_COMPILER_ERROR);
            if(ImGui::MenuItem("Clear error list"))
            	ExecCommand(COMMAND_CLEAR_DEBUG_DRAW);

        	ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Objects"))
    	{
        	if(ImGui::MenuItem("Library editor"))
            	ExecCommand(COMMAND_LIBRARY_EDITOR);
            ImGui::Separator();
            if(ImGui::MenuItem("Reload objects"))
            	ExecCommand(COMMAND_RELOAD_OBJECTS);
            if(ImGui::MenuItem("Clean library"))
            	ExecCommand(COMMAND_CLEAN_LIBRARY);
            if(ImGui::MenuItem("Clip editor"))
            	ExecCommand(COMMAND_SHOW_CLIP_EDITOR);

        	ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Images"))
        {
        	if(ImGui::MenuItem("Image editor"))
            	ExecCommand(COMMAND_IMAGE_EDITOR);
            ImGui::Separator();
            if(ImGui::MenuItem("Reload textures"))
            	ExecCommand(COMMAND_RELOAD_TEXTURES);
            ImGui::Separator();
            if(ImGui::MenuItem("Synchronize textures"))
            	ExecCommand(COMMAND_REFRESH_TEXTURES);
            if(ImGui::MenuItem("Check new textures"))
            	ExecCommand(COMMAND_CHECK_TEXTURES);
            ImGui::Separator();
            if(ImGui::MenuItem("Edit minimap"))
            	ExecCommand(COMMAND_MINIMAP_EDITOR);
            if(ImGui::MenuItem("SyncTHM"))
            	;

        	ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Sounds"))
        {
        	if(ImGui::MenuItem("Sound editor"))
            	ExecCommand(COMMAND_SOUND_EDITOR);
            ImGui::Separator();
        	if(ImGui::MenuItem("Synchronize sounds"))
            	ExecCommand(COMMAND_SYNC_SOUNDS);
            ImGui::Separator();
            if(ImGui::MenuItem("Refresh environment library"))
            	ExecCommand(COMMAND_REFRESH_SOUND_ENVS);
            if(ImGui::MenuItem("Refresh environment geometry"))
            	ExecCommand(COMMAND_REFRESH_SOUND_ENV_GEOMETRY);
            if(ImGui::MenuItem("Load sound occluder"))
            	ExecCommand(COMMAND_LOAD_SOUND_OCCLUDER);
        	ImGui::EndMenu();
        }

        if(ImGui::MenuItem("Light anim editor"))
        	ExecCommand(COMMAND_LANIM_EDITOR);

        if(ImGui::MenuItem("Object list"))
        	ExecCommand(COMMAND_SHOW_OBJECTLIST);

        if(ImGui::MenuItem("Preferences"))
        	ExecCommand(COMMAND_EDITOR_PREF);
    }

    if(ImGui::CollapsingHeader("Tools",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2);

        if(ImGui::BeginMenu("Edit"))
        {
        	if(ImGui::MenuItem("Cut"))
            	ExecCommand(COMMAND_CUT);
            if(ImGui::MenuItem("Copy"))
            	ExecCommand(COMMAND_COPY);
            if(ImGui::MenuItem("Paste"))
            	ExecCommand(COMMAND_PASTE);
            ImGui::Separator();
            if(ImGui::MenuItem("Undo"))
            	ExecCommand(COMMAND_UNDO);
            if(ImGui::MenuItem("Redo"))
            	ExecCommand(COMMAND_REDO);
        	ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Selection"))
        {
        	if(ImGui::MenuItem("Invert"))
            	ExecCommand(COMMAND_INVERT_SELECTION_ALL);
            if(ImGui::MenuItem("Select all"))
            	ExecCommand(COMMAND_SELECT_ALL);
            if(ImGui::MenuItem("Unselect all"))
            	ExecCommand(COMMAND_DESELECT_ALL);
        	ImGui::EndMenu();
        }

        if(ImGui::MenuItem("Properties"))
        	ExecCommand(COMMAND_SHOW_PROPERTIES);

        ImGui::NextColumn();

        if(ImGui::BeginMenu("Visibility"))
        {
        	if(ImGui::MenuItem("Hide selection"))
            	ExecCommand(COMMAND_HIDE_SEL, FALSE);
            if(ImGui::MenuItem("Hide unselected"))
            	ExecCommand(COMMAND_HIDE_UNSEL);
            if(ImGui::MenuItem("Hide all"))
            	ExecCommand(COMMAND_HIDE_ALL, FALSE);
            ImGui::Separator();
        	if(ImGui::MenuItem("Unhide all"))
            	ExecCommand(COMMAND_HIDE_ALL, TRUE);
        	ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Locking"))
        {
        	if(ImGui::MenuItem("Lock selection"))
            	ExecCommand(COMMAND_LOCK_SEL, TRUE);
            if(ImGui::MenuItem("Lock unselected"))
            	ExecCommand(COMMAND_LOCK_UNSEL, TRUE);
            if(ImGui::MenuItem("Lock all"))
            	ExecCommand(COMMAND_LOCK_ALL, TRUE);
            ImGui::Separator();
            if(ImGui::MenuItem("Unlock selection"))
            	ExecCommand(COMMAND_LOCK_SEL, FALSE);
            if(ImGui::MenuItem("Unlock unselected"))
            	ExecCommand(COMMAND_LOCK_UNSEL, FALSE);
            if(ImGui::MenuItem("Unlock all"))
            	ExecCommand(COMMAND_LOCK_ALL, FALSE);
        	ImGui::EndMenu();
        }

        if(ImGui::MenuItem("Multi rename"))
        	ExecCommand(COMMAND_MULTI_RENAME_OBJECTS);

        ImGui::Columns(1);
    }

    if(ImGui::CollapsingHeader("Edit mode",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	ImGui::Columns(2);

		for(DWORD i = OBJCLASS_FIRST_CLASS; i < OBJCLASS_COUNT; i++)
        {
        	ESceneToolBase *tool = Scene->GetTool(i);

            ImGui::PushID(1005 + i);
            if(ImGui::Button(tool->IsVisible() ? "*" : " "))
            	ExecCommand(COMMAND_SHOW_TARGET, i, !tool->IsVisible());
            ImGui::PopID();

            ImGui::SameLine();

			ImGui::RadioButton(tool->ClassDesc(), LTools->CurrentClassID() == i);
            if(ImGui::IsItemClicked())
            	ExecCommand(COMMAND_CHANGE_TARGET, i);

            if(i == OBJCLASS_COUNT/2-1)
            	ImGui::NextColumn();
        }

        ImGui::Columns(1);
    }

    if(ImGui::CollapsingHeader("Snap list",
    ImGuiTreeNodeFlags_Framed|ImGuiTreeNodeFlags_DefaultOpen))
    {
    	if(ImGui::BeginMenu("Commands"))
        {
        	if(ImGui::MenuItem("Make list from selected"))
            	ExecCommand(COMMAND_SET_SNAP_OBJECTS);
            if(ImGui::MenuItem("Select objects from list"))
            	ExecCommand(COMMAND_SELECT_SNAP_OBJECTS);
            ImGui::Separator();
            if(ImGui::MenuItem("Add selected to list"))
            	ExecCommand(COMMAND_ADD_SEL_SNAP_OBJECTS);
            if(ImGui::MenuItem("Remove selected from list"))
            	ExecCommand(COMMAND_DEL_SEL_SNAP_OBJECTS);
            ImGui::Separator();
            if(ImGui::MenuItem("Clear list"))
            {
            	if (ELog.DlgMsg(mtConfirmation,TMsgDlgButtons() << mbYes << mbNo,"Are you sure to clear snap objects?")==mrYes)
					ExecCommand(COMMAND_CLEAR_SNAP_OBJECTS);
            }

        	ImGui::EndMenu();
        }

		ImGui::Selectable("Enable/Show snap list", &m_enable_snap_list);

        ImGui::Columns(3, NULL, false);

		if(ImGui::Selectable("+/- Mode", &m_select_snap_objs_mode))
        	if (m_select_snap_objs_mode&&(etaSelect!=Tools->GetAction())){
    			ELog.Msg(mtError,"Before modify snap list activate select mode!");
        		m_select_snap_objs_mode = false;
    		}

        ImGui::NextColumn();

        if(ImGui::MenuItem("Clear"))
        	ExecCommand(COMMAND_CLEAR_SNAP_OBJECTS);

        ImGui::NextColumn();

        if(ImGui::MenuItem("Edit..."))
        	ExecCommand(COMMAND_EDIT_SNAP_OBJECTS);

        ImGui::Columns(1);

    	ObjectList *ol = Scene->GetSnapList(true);
        int i = 0;

        ImGui::BeginChild("snap list", ImVec2(0,150), true);

        for(ObjectIt it = ol->begin(), end = ol->end(); it != end; it++)
        {
        	ImGui::Text("%u: %s", i, (*it)->FName.c_str());
        	i++;
        }

        ImGui::EndChild();
    }

    if(m_detach_tool_frame)
    {
    	ImGui::Begin("Tool Options", &m_detach_tool_frame);
        RenderToolFrame();
        ImGui::End();
    }
    else
    {
    	bool detach = ImGui::Button(" ", ImVec2(-1, 5));
		RenderToolFrame();
        m_detach_tool_frame = detach;
    }

    ImGui::End();
}

void IM_LeftBar::RenderToolFrame()
{
    switch(LTools->CurrentClassID())
    {
    	case OBJCLASS_SCENEOBJECT: 	fraObject.Render(); break;
        case OBJCLASS_LIGHT:        fraLight.Render(); break;
        case OBJCLASS_FOG_VOL:		fraFogVol.Render(); break;
        case OBJCLASS_DO:			fraDetail.Render(); break;
        case OBJCLASS_SECTOR:		fraSector.Render(); break;
        case OBJCLASS_PORTAL:		fraPortal.Render(); break;
        case OBJCLASS_SHAPE:		fraShape.Render(); break;
        case OBJCLASS_PS:			fraPS.Render(); break;
        case OBJCLASS_WAY:			fraWayPoint.Render(); break;
        case OBJCLASS_SPAWNPOINT:	fraSpawn.Render(); break;
        case OBJCLASS_GROUP:		fraGroup.Render(); break;
        case OBJCLASS_AIMAP:		fraAIMap.Render(); break;
    }
}

IM_LeftBar imLeftBar;


