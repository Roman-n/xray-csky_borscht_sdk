//---------------------------------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include "main.h"

TfrmMain *frmMain;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RenderWindow"
#pragma resource "*.dfm"

#include "topbar.h"
#include "leftbar.h"
#include "bottombar.h"

//------------------------------------------------------------------------------
#include "shader.h"
#include "shader_xrlc.h"
#include "../ECore/Engine/texture.h"
#include "../ECore/Editor/Library.h"
#include "../ECore/Editor/EditObject.h"
#include "../ECore/Editor/EThumbnail.h"
#include "../xrEProps/FolderLib.h"
#include "LightAnimLibrary.h"
#include "../ECore/Editor/ImageManager.h"
#include "../ECore/Editor/SoundManager.h"
#include "../ECore/Editor/ui_main.h"
#include "..\..\Layers\xrRender\PSLibrary.h"
#include "GameMtlLib.h"
#include "../../xrSound/soundrender_source.h"
#include "ResourceManager.h"
#include "../xrEProps/EditorChooseEvents.h"
#include "UI_LevelTools.h"
#include "UI_LevelMain.h"
#include "FrmDBXpacker.h"
#include "scene.h"
#include "FormAbout.h"


__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
// forms
    fraBottomBar	= xr_new<TfraBottomBar>	((TComponent*)0);
    fraTopBar   	= xr_new<TfraTopBar>	((TComponent*)0);
    fraLeftBar  	= xr_new<TfraLeftBar>	((TComponent*)0);
//-

	fraBottomBar->Parent    = paBottomBar;
	fraTopBar->Parent       = paTopBar;
	fraLeftBar->Parent      = paLeftBar;
	if (paLeftBar->Tag > 0) paLeftBar->Parent = paTopBar;
	else paLeftBar->Parent 	= frmMain;

	Device.SetHandle		(Handle,D3DWindow->Handle);
    EnableReceiveCommands	();
    if (!ExecCommand(COMMAND_INITIALIZE,(u32)D3DWindow,(u32)paRender)){ 
    	FlushLog			();
    	TerminateProcess(GetCurrentProcess(),-1);
    }

    // add tools to edit mode menu
    struct
    {
    	LPCSTR caption;
        DWORD class_id;
    } tools_desc[] = {
    	{"Object",			OBJCLASS_SCENEOBJECT},
        {"Light",			OBJCLASS_LIGHT},
        {"Sound Source",	OBJCLASS_SOUND_SRC},
        {"Sound Env",		OBJCLASS_SOUND_ENV},
        {"Glow",			OBJCLASS_GLOW},
        {"Shape",			OBJCLASS_SHAPE},
        {"Spawn Element",	OBJCLASS_SPAWNPOINT},
        {"Way Points",		OBJCLASS_WAY},
        {"Sector",			OBJCLASS_SECTOR},
        {"Portal",			OBJCLASS_PORTAL},
        {"Group",			OBJCLASS_GROUP},
        {"Static Particles",OBJCLASS_PS},
        {"Detail Objects",	OBJCLASS_DO},
        {"AI-Map",			OBJCLASS_AIMAP},
        {"Wallmarks",		OBJCLASS_WM},
        {"Fog Volumes",		OBJCLASS_FOG_VOL}
    };

    for(int i = 0; i < sizeof(tools_desc)/sizeof(tools_desc[0]); i++)
    {
    	TMenuItem *item 	= xr_new<TMenuItem>(this);
    	item->Caption 		= tools_desc[i].caption;
    	item->Tag			= tools_desc[i].class_id;
        item->RadioItem		= true;
        item->OnClick		= miChangeTargetClick;

        miEditMode->Add		(item);
    }

    for(i = 0; i < sizeof(tools_desc)/sizeof(tools_desc[0]); i++)
    {
    	TMenuItem *item		= xr_new<TMenuItem>(this);
        item->Caption		= "";
        item->Tag			= tools_desc[i].class_id;
        item->OnClick		= miShowTargetClick;

        if(i == 0)
        	item->Break		= mbBreak;

        miEditMode->Add		(item);
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormShow(TObject *Sender)
{
    tmRefresh->Enabled 		= true; tmRefreshTimer(Sender);
    ExecCommand				(COMMAND_UPDATE_GRID);
    ExecCommand				(COMMAND_RENDER_FOCUS);
    FillChooseEvents		();

    // special case :(
	frmMain->WindowState 	= (TWindowState)fsStorage->ReadInteger("window_state",frmMain->WindowState);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    Application->OnIdle     = 0;

    ClearChooseEvents		();

    ExecCommand				(COMMAND_DESTROY);

	fraTopBar->Parent       = 0;
	fraLeftBar->Parent      = 0;
	fraBottomBar->Parent    = 0;

    xr_delete(fraTopBar);
    xr_delete(fraBottomBar);
	xr_delete(fraLeftBar);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    tmRefresh->Enabled = false;
    CanClose = ExecCommand(COMMAND_EXIT);
    if (!CanClose) tmRefresh->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	DEFINE_INI(fsStorage);
    Application->OnIdle = IdleHandler;
}

//---------------------------------------------------------------------------

#include "RightForm.h"
#define MIN_PANEL_HEIGHT 17
void __fastcall TfrmMain::sbToolsMinClick(TObject *Sender)
{
    if (paLeftBar->Tag > 0)
    {
    	frmRight->Hide     ();

    	paLeftBar->Tag     = 0;
        paLeftBar->Align   = alRight;
        paLeftBar->Parent  = frmMain;

        spLeftBar->Show();
    }else{
    	frmRight->Show	  ();
    	frmRight->Width	  = paLeftBar->Width;
        frmRight->Height  = 1024;

        paLeftBar->Tag    = 1;
        paLeftBar->Parent = frmRight; //paTopBar;
        paLeftBar->Align  = alClient;

        spLeftBar->Hide   ();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::TopClick(TObject *Sender)
{
    if (paLeftBar->Tag > 0){
        paLeftBar->Align  = alRight;
        paLeftBar->Parent = frmMain;
        paLeftBar->Height = paLeftBar->Tag;
        paLeftBar->Tag    = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::IdleHandler(TObject *Sender, bool &Done)
{
    Done = false;
    UI->Idle();
}
void __fastcall TfrmMain::D3DWindowResize(TObject *Sender)
{
    UI->Resize();
}                     
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    ShiftKey = Shift;
    if (!UI->KeyDown(Key, Shift)){UI->ApplyShortCut(Key, Shift);}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (!UI->KeyUp(Key, Shift)){;}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowKeyPress(TObject *Sender, char &Key)
{
    if (!UI->KeyPress(Key, ShiftKey)){;}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (!D3DWindow->Focused()) UI->ApplyGlobalShortCut(Key, Shift);
	if (Key==VK_MENU) Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::UpdateCaption()
{
    AnsiString name;
    name.sprintf("%s - [%s%s]",UI->EditorDesc(),UI->GetCaption(),UI->IsModified()?"*":"");
    Caption = name;
}
//---------------------------------------------------------------------------

void TfrmMain::RefreshBars()
{
    fraTopBar->RefreshBar		();
    fraLeftBar->RefreshBar		();
    fraBottomBar->RefreshBar	();
/*
    miOpenRecent->Clear();
    for(size_t i = 0; i < EPrefs->scene_recent_list.size(); i++)
    {
    	TMenuItem *item = xr_new<TMenuItem>(this);
        item->Caption = EPrefs->scene_recent_list[i];
        item->Tag = i;
        item->OnClick = miOpenRecentClick;

        miOpenRecent->Add(item);
    }
*/
	// clear recent file list
    xr_vector<TMenuItem*> recent;

	for(size_t i = 0; i < miFile->Count; i++)
    	if(miFile->Items[i]->Tag >= 9555)
			recent.push_back(miFile->Items[i]);

    for(i = 0; i < recent.size(); i++)
    	miFile->Remove(recent[i]);

    // recreate recent file list
    size_t cnt = EPrefs->scene_recent_list.size();
    for(i = 0; i < cnt; i++)
    {
    	TMenuItem *item = xr_new<TMenuItem>(this);
        item->Caption = EPrefs->scene_recent_list[i];
        item->Tag = 9555 + i;
        item->OnClick = miOpenRecentClick;

        miFile->Insert(10+i, item);
    }

    TMenuItem *separator = xr_new<TMenuItem>(this);
    separator->Caption = "-";
    miFile->Insert(10+i, separator);


    for(i = 0; i < miEditMode->Count/2; i++)
    {
    	if(LTools->CurrentClassID() == miEditMode->Items[i]->Tag)
        	miEditMode->Items[i]->Checked = true;
    }

    for(i = miEditMode->Count/2; i < miEditMode->Count; i++)
    {
    	ESceneToolBase *tool = Scene->GetTool(miEditMode->Items[i]->Tag);
        VERIFY(tool);

        miEditMode->Items[i]->ImageIndex = tool->IsVisible() ? 0 : 1;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::tmRefreshTimer(TObject *Sender)
{
    for (int i=0; i<frmMain->ComponentCount; i++){
        TComponent* temp = frmMain->Components[i];
        if (dynamic_cast<TExtBtn *>(temp) != NULL)
            ((TExtBtn*)temp)->UpdateMouseInControl();
    }

	fraLeftBar->OnTimer();
	fraTopBar->OnTimer();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowPaint(TObject *Sender)
{
	if (!UI||!UI->m_bReady) return;
    UI->RedrawScene();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowChangeFocus(TObject *Sender)
{
	if (!UI||!UI->m_bReady) return;
	if (D3DWindow->Focused()){
        UI->IR_Capture();
		UI->OnAppActivate();
    }else{
		UI->OnAppDeactivate();
        UI->IR_Release();
//        paRender->Color=paRender->Color; // чтобы не было  internal code gen error
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    UI->MousePress(Shift,X,Y);
    UI->RedrawScene();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    UI->MouseRelease(Shift,X,Y);
    UI->RedrawScene();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::D3DWindowMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    UI->MouseMove(Shift,X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ebAllMinClick(TObject *Sender)
{
	fraLeftBar->MinimizeAllFrames();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ebAllMaxClick(TObject *Sender)
{
	fraLeftBar->MaximizeAllFrames();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormResize(TObject *Sender)
{
	if (fraLeftBar) fraLeftBar->UpdateBar();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::paRenderResize(TObject *Sender)
{
	ExecCommand(COMMAND_RENDER_RESIZE);
}
//---------------------------------------------------------------------------
 
void __fastcall TfrmMain::fsStorageSavePlacement(TObject *Sender)
{
    fsStorage->WriteInteger("window_state",frmMain->WindowState);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miClearClick(TObject *Sender)
{
	ExecCommand(COMMAND_CLEAR);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miOpenClick(TObject *Sender)
{
	ExecCommand(COMMAND_LOAD);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSaveClick(TObject *Sender)
{
	ExecCommand(COMMAND_SAVE, xr_string(LTools->m_LastFileName.c_str()));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSaveAsClick(TObject *Sender)
{
	ExecCommand(COMMAND_SAVE, 0, 1);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miQuitClick(TObject *Sender)
{
	ExecCommand(COMMAND_QUIT);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miOpenRecentClick(TObject *Sender)
{
	TMenuItem *item = (TMenuItem*)Sender;
    ExecCommand(COMMAND_LOAD, xr_string(EPrefs->scene_recent_list[item->Tag-9555].c_str()));
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miOpenSelectionClick(TObject *Sender)
{
	ExecCommand(COMMAND_LOAD_SELECTION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSaveSelectionClick(TObject *Sender)
{
	ExecCommand(COMMAND_SAVE_SELECTION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMakePackClick(TObject *Sender)
{
	DB_packer->ActivatePacker();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miUndoClick(TObject *Sender)
{
	ExecCommand(COMMAND_UNDO);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miRedoClick(TObject *Sender)
{
	ExecCommand(COMMAND_REDO);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miCutClick(TObject *Sender)
{
	ExecCommand(COMMAND_CUT);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miCopyClick(TObject *Sender)
{
	ExecCommand(COMMAND_COPY);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miPasteClick(TObject *Sender)
{
	ExecCommand(COMMAND_PASTE);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miDeleteClick(TObject *Sender)
{
	ExecCommand(COMMAND_DELETE_SELECTION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miSelectAllClick(TObject *Sender)
{
	ExecCommand(COMMAND_SELECT_ALL);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miDeselectAllClick(TObject *Sender)
{
	ExecCommand(COMMAND_DESELECT_ALL);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miInvertSelectionClick(TObject *Sender)
{
	ExecCommand(COMMAND_INVERT_SELECTION_ALL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miChangeTargetClick(TObject *Sender)
{
	TMenuItem *item = (TMenuItem*)Sender;
    ExecCommand(COMMAND_CHANGE_TARGET, item->Tag);
    item->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miShowTargetClick(TObject *Sender)
{
	TMenuItem *item = (TMenuItem*)Sender;
    ESceneToolBase *tool = Scene->GetTool(item->Tag);
    VERIFY(tool);

    ExecCommand(COMMAND_SHOW_TARGET, item->Tag, !tool->IsVisible());
    item->ImageIndex = tool->IsVisible() ? 0 : 1;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miBuildClick(TObject *Sender)
{
	ExecCommand(COMMAND_BUILD);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMakeGameClick(TObject *Sender)
{
	ExecCommand(COMMAND_MAKE_GAME);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMakeDetailsClick(TObject *Sender)
{
	ExecCommand(COMMAND_MAKE_DETAILS);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMakeHOMClick(TObject *Sender)
{
	ExecCommand(COMMAND_MAKE_HOM);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMakeSoundOccluderClick(TObject *Sender)
{
	ExecCommand(COMMAND_MAKE_SOM);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miMakeAIMapClick(TObject *Sender)
{
	ExecCommand(COMMAND_MAKE_AIMAP);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Options1Click(TObject *Sender)
{
	ExecCommand(COMMAND_OPTIONS, CCommandVar("Scene"));	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Validate1Click(TObject *Sender)
{
	ExecCommand(COMMAND_VALIDATE_SCENE);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SummaryInfo1Click(TObject *Sender)
{
	ExecCommand( COMMAND_CLEAR_SCENE_SUMMARY );
	ExecCommand( COMMAND_COLLECT_SCENE_SUMMARY );
	ExecCommand( COMMAND_SHOW_SCENE_SUMMARY );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::HighlightTexture1Click(TObject *Sender)
{
	ExecCommand( COMMAND_SCENE_HIGHLIGHT_TEXTURE );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClearDebugDraw1Click(TObject *Sender)
{
	ExecCommand(COMMAND_CLEAR_DEBUG_DRAW);	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ExportentireSceneasObj1Click(TObject *Sender)
{
	Scene->ExportObj(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Exportselection1Click(TObject *Sender)
{
	Scene->ExportObj(true);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ImportErrorList1Click(TObject *Sender)
{
	ExecCommand(COMMAND_IMPORT_COMPILER_ERROR);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ExportErrorList1Click(TObject *Sender)
{
	ExecCommand(COMMAND_EXPORT_COMPILER_ERROR);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClearErrorList1Click(TObject *Sender)
{
	ExecCommand(COMMAND_CLEAR_DEBUG_DRAW);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LibraryEditor1Click(TObject *Sender)
{
	ExecCommand( COMMAND_LIBRARY_EDITOR );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ReloadObjects1Click(TObject *Sender)
{
	ExecCommand( COMMAND_RELOAD_OBJECTS );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CleanLibrary1Click(TObject *Sender)
{
	ExecCommand( COMMAND_CLEAN_LIBRARY );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ClipEditor1Click(TObject *Sender)
{
	ExecCommand( COMMAND_SHOW_CLIP_EDITOR) ;	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ImageEditor1Click(TObject *Sender)
{
	ExecCommand( COMMAND_IMAGE_EDITOR );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ReloadTextures1Click(TObject *Sender)
{
	ExecCommand( COMMAND_RELOAD_TEXTURES );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SychronizeTextures1Click(TObject *Sender)
{
	ExecCommand( COMMAND_REFRESH_TEXTURES );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::CheckNewTextures1Click(TObject *Sender)
{
	ExecCommand( COMMAND_CHECK_TEXTURES );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::EditMinimap1Click(TObject *Sender)
{
	ExecCommand( COMMAND_MINIMAP_EDITOR );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SynchronizeTHM1Click(TObject *Sender)
{
	FS_FileSet      files;
	FS.file_list    (files,_textures_,FS_ListFiles,"*.thm");
	FS_FileSet::iterator I = files.begin();
	FS_FileSet::iterator E = files.end();

	for(; I!=E; ++I)
	{
		ETextureThumbnail* TH = xr_new<ETextureThumbnail>( (*I).name.c_str(), false);
		TH->Load((*I).name.c_str(),_textures_);
		TH->Save();
		xr_delete(TH);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SoundEditor1Click(TObject *Sender)
{
	ExecCommand( COMMAND_SOUND_EDITOR );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::SynchronizeSounds1Click(TObject *Sender)
{
	ExecCommand( COMMAND_SYNC_SOUNDS );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RefreshEnvironmentLibrary1Click(TObject *Sender)
{
	ExecCommand( COMMAND_REFRESH_SOUND_ENVS );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::RefreshEnvironmentGeometry1Click(TObject *Sender)
{
	ExecCommand( COMMAND_REFRESH_SOUND_ENV_GEOMETRY );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LoadSoundOccluder1Click(TObject *Sender)
{
	ExecCommand( COMMAND_LOAD_SOUND_OCCLUDER );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::HideSelected1Click(TObject *Sender)
{
	ExecCommand( COMMAND_HIDE_SEL, FALSE );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::HideUnselected1Click(TObject *Sender)
{
	ExecCommand( COMMAND_HIDE_UNSEL );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::HideAll1Click(TObject *Sender)
{
	ExecCommand( COMMAND_HIDE_ALL, TRUE );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Unhideall1Click(TObject *Sender)
{
	ExecCommand( COMMAND_HIDE_ALL, FALSE);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::MultiRename1Click(TObject *Sender)
{
	ExecCommand( COMMAND_MULTI_RENAME_OBJECTS );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Properties1Click(TObject *Sender)
{
	ExecCommand( COMMAND_SHOW_PROPERTIES );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::LightAnimEditor1Click(TObject *Sender)
{
	ExecCommand( COMMAND_LANIM_EDITOR );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ObjectList1Click(TObject *Sender)
{
	ExecCommand( COMMAND_SHOW_OBJECTLIST );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::Preferences1Click(TObject *Sender)
{
	ExecCommand( COMMAND_EDITOR_PREF );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miRunClick(TObject *Sender)
{
	ExecCommand( COMMAND_RUN_SCRIPT, Scene->m_ScriptRunGame );
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miCompileLevelClick(TObject *Sender)
{
	ExecCommand( COMMAND_RUN_SCRIPT, Scene->m_ScriptCompileLevel );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miCompileDetailsClick(TObject *Sender)
{
	ExecCommand( COMMAND_RUN_SCRIPT, Scene->m_ScriptCompileDetails );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miCompileAIMapClick(TObject *Sender)
{
	ExecCommand( COMMAND_RUN_SCRIPT, Scene->m_ScriptCompileAIMap );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::miCompileSpawnClick(TObject *Sender)
{
	ExecCommand( COMMAND_RUN_SCRIPT, Scene->m_ScriptCompileSpawn );	
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::About1Click(TObject *Sender)
{
	AboutForm->ShowModal();	
}
//---------------------------------------------------------------------------

