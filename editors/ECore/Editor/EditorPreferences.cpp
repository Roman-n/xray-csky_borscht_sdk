//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "PropertiesList.h"
#include "ui_main.h"
#include "ui_toolscustom.h"
//---------------------------------------------------------------------------
CCustomPreferences* EPrefs=0;
//---------------------------------------------------------------------------

CCustomPreferences::CCustomPreferences()
{
	m_Prefs["Tools"].set("editor_prefs", "tools_settings", ptFlags, &Tools->m_Settings, Tools->m_Settings);
    
    m_Prefs["Device"].set("editor_prefs", "device_flags", ptFlags, &psDeviceFlags, psDeviceFlags);

	m_Prefs["Sounds"].set("editor_prefs", "sounds_flags", ptFlags, &psSoundFlags, psSoundFlags)
    	.addFlag("Sounds\\Use\\Hardware", 	ss_Hardware)
        .addFlag("Sounds\\Use\\EAX",        ss_EAX);

	m_Prefs["Objects"].set("editor_prefs", "object_flags", ptFlags, &object_flags, Flags32().zero())
		.addFlag("Objects\\Library\\Discard Instance", 		epoDiscardInstance)
		.addFlag("Objects\\Skeleton\\Draw Joints", 			epoDrawJoints)
		.addFlag("Objects\\Skeleton\\Draw Bone Axis",		epoDrawBoneAxis)
		.addFlag("Objects\\Skeleton\\Draw Bone Names",		epoDrawBoneNames)
		.addFlag("Objects\\Skeleton\\Draw Bone Shapes",		epoDrawBoneShapes)
		.addFlag("Objects\\Show\\Hint",						epoShowHint)
		.addFlag("Objects\\Show\\Pivot",					epoDrawPivot)
		.addFlag("Objects\\Show\\Animation Path",			epoDrawAnimPath)
		.addFlag("Objects\\Show\\LOD",						epoDrawLOD)
		.addFlag("Objects\\Loading\\Deferred Loading RB",	epoDeffLoadRB)
		.addFlag("Objects\\Loading\\Deferred Loading CF",	epoDeffLoadCF)
		.addFlag("Objects\\Saving\\LZH Compression",		epoLZHCompress);

	m_Prefs["Scene\\Common\\Recent Count"].set		("editor_prefs", "scene_recent_count", 	ptInteger, 	&scene_recent_count, 10,   0,    25);
    m_Prefs["Scene\\Common\\Undo Level"].set		("editor_prefs", "scene_undo_level", 	ptInteger, 	&scene_undo_level, 	 125,  0,    125);
    m_Prefs["Scene\\Grid\\Cell Size"].set			("editor_prefs", "grid_cell_size", 		ptFloat, 	&grid_cell_size,     1.0f, 0.1f, 10.f);
    m_Prefs["Scene\\Grid\\Cell Count"].set			("editor_prefs", "grid_cell_count",		ptInteger, 	&grid_cell_count,    100,  10,   1000);

    m_Prefs["Tools\\Box Pick\\Limited Depth"].set	("editor_prefs", "bp_lim_depth",		ptBool,		&bp_lim_depth, 		TRUE);
    m_Prefs["Tools\\Box Pick\\Backface Culling"].set("editor_prefs", "bp_cull",				ptBool,		&bp_cull,       	TRUE);
    m_Prefs["Tools\\Box Pick\\Depth Tolerance"].set	("editor_prefs", "bp_depth_tolerance",	ptFloat,	&bp_depth_tolerance, 0.1f, 0.f, 10000.f);
    m_Prefs["Tools\\Sens\\Move"].set				("editor_prefs", "tools_sens_move",		ptFloat,	&tools_sens_move, 	0.3f);
    m_Prefs["Tools\\Sens\\Rotate"].set				("editor_prefs", "tools_sens_rot",		ptFloat,	&tools_sens_rot, 	0.3f);
    m_Prefs["Tools\\Sens\\Scale"].set				("editor_prefs", "tools_sens_scale",	ptFloat,	&tools_sens_scale, 	0.3f);
    m_Prefs["Tools\\Snap\\Angle"].set				("editor_prefs", "snap_angle",			ptAngle,	&snap_angle, 		deg2rad(5.f), 0, PI_MUL_2);
    m_Prefs["Tools\\Snap\\Move"].set				("editor_prefs", "snap_move",			ptFloat,	&snap_move, 		0.1f, 0.01f, 1000.f);
    m_Prefs["Tools\\Snap\\Move To"].set				("editor_prefs", "snap_moveto",			ptFloat,	&snap_moveto, 		0.5f, 0.01f, 1000.f);

    m_Prefs["Viewport\\Camera\\Move Sens"].set		("editor_prefs", "cam_sens_move",		ptFloat,	&cam_sens_move, 	0.6f);
    m_Prefs["Viewport\\Camera\\Rotate Sens"].set	("editor_prefs", "cam_sens_rot",		ptFloat,	&cam_sens_rot, 		0.6f);
    m_Prefs["Viewport\\Camera\\Free Fly Speed"].set	("editor_prefs", "cam_free_fly_speed",	ptFloat,	&cam_free_fly_speed, 5.0f, 0.01f, 100.f);
    m_Prefs["Viewport\\Camera\\Fly Speed"].set		("editor_prefs", "cam_fly_speed",		ptFloat,	&cam_fly_speed, 	5.0f, 0.01f, 100.f);
    m_Prefs["Viewport\\Camera\\Fly Altitude"].set	("editor_prefs", "cam_fly_alt",			ptFloat,	&cam_fly_alt,		1.8f, 0.f, 1000.f);
    m_Prefs["Viewport\\Fog\\Color"].set				("editor_prefs", "fog_color",			ptColor,	&fog_color,			0x00555555);
    m_Prefs["Viewport\\Fog\\Fogness"].set			("editor_prefs", "fog_fogness",			ptFloat,	&fog_fogness,		0.9f, 0.f, 100.f);
    m_Prefs["Viewport\\Near Plane"].set				("editor_prefs", "view_np",				ptFloat,	&view_np,			0.1f, 0.01f, 10.f);
    m_Prefs["Viewport\\Far Plane"].set				("editor_prefs", "view_fp",				ptFloat,	&view_fp,			1500.f, 10.f, 10000.f);
    m_Prefs["Viewport\\FOV"].set					("editor_prefs", "view_fov",			ptAngle,	&view_fov,			deg2rad(60.f), deg2rad(0.1f), deg2rad(170.f));
    m_Prefs["Viewport\\Clear Color"].set			("editor_prefs", "scene_clear_color",	ptColor,	&scene_clear_color,	DEFAULT_CLEARCOLOR);

    m_Prefs["Style\\Log\\Default Color"].set		("styles", "log_default_color", 		ptColor,	&log_default_color, 0x00E8E8E8);
    m_Prefs["Style\\Log\\Error Color"].set			("styles", "log_error_color", 			ptColor,	&log_error_color,   0x00FFC4C4);
    m_Prefs["Style\\Log\\Info Color"].set			("styles", "log_info_color",			ptColor,	&log_info_color,    0x00E7FFE6);
    m_Prefs["Style\\Log\\Confirmation Color"].set	("styles", "log_confirmation_color",	ptColor,	&log_confirmation_color,    0x00E7E6FF);

    m_Prefs["Style\\Text Form\\Background Color"].set("styles", "textform_background_color",	ptColor,	&textform_background_color, 0x00A0A0A0);
    m_Prefs["Style\\Text Form\\Text Color"].set		("styles", "textform_text_color",		ptColor,	&textform_text_color,		0x00000000);

    m_Prefs["Weather\\Raindrop Collision Detection"].set("editor_prefs", "weather_raindrop_collision", ptBool, &raindrop_collision, TRUE);

    // it is necessary to set default values there?
    /*
	// view
    view_np				= 0.1f;
    view_fp				= 1500.f;
    view_fov			= deg2rad(60.f);
	// fog    
    fog_color			= 0x00555555;
    fog_fogness			= 0.9;
    // camera
    cam_fly_speed		= 5.0f;
    cam_fly_alt			= 1.8f;
    cam_sens_rot		= 0.6f;
    cam_sens_move		= 0.6f;
	// tools mouse
    tools_sens_move		= 0.3f;
    tools_sens_rot		= 0.3f;
    tools_sens_scale	= 0.3f;
    // box pick
    bp_lim_depth		= TRUE;
    bp_cull				= TRUE;
    bp_depth_tolerance	= 0.1f;
    // snap
    snap_angle			= deg2rad(5.f);
    snap_move			= 0.1f;
    snap_moveto			= 0.5f;
    // grid
    grid_cell_size		= 1.f;
    grid_cell_count		= 100;
    // scene
    scene_undo_level	= 125;
    scene_recent_count	= 10;
    scene_clear_color	= DEFAULT_CLEARCOLOR;
    // objects
    object_flags.zero	();
    */
}
//---------------------------------------------------------------------------

CCustomPreferences::~CCustomPreferences()
{
}

void CCustomPreferences::ApplyValues()
{
	Tools->m_MoveSnap		= snap_move;
	Tools->m_MoveSnapTo		= snap_moveto;
	Tools->m_RotateSnapAngle= snap_angle;

    Device.m_Camera.SetViewport(view_np, view_fp, rad2deg(view_fov));
    Tools->SetFog	(fog_color,fog_fogness);

    UI->m_MouseSM	= 0.2f*tools_sens_move*tools_sens_move;
    UI->m_MouseSR	= 0.02f*tools_sens_rot*tools_sens_rot;
    UI->m_MouseSS	= 0.02f*tools_sens_scale*tools_sens_scale;

    Device.m_Camera.SetSensitivity	(cam_sens_move, cam_sens_rot);
    Device.m_Camera.SetFlyParams	(cam_free_fly_speed, cam_fly_speed, cam_fly_alt);

    ExecCommand		(COMMAND_UPDATE_GRID);
}
//---------------------------------------------------------------------------

void __stdcall CCustomPreferences::OnClose	()
{
	ApplyValues	();	
}
//---------------------------------------------------------------------------


void CheckValidate(ShortcutValue*, const xr_shortcut& new_val, bool& result)
{
	result 					= true;

	if(new_val.similar(xr_shortcut(0, FALSE, FALSE, FALSE)))
		return;

	if(new_val.key==0) { // key == 0 && ext != 0 - invalid
		result = false;
		return;
	}

	ECommandVec& cmds		= GetEditorCommands();
    for (u32 cmd_idx=0; cmd_idx<cmds.size(); cmd_idx++){
    	SECommand*& CMD		= cmds[cmd_idx];
        if (CMD&&CMD->editable){
        	VERIFY(!CMD->sub_commands.empty());
		    for (u32 sub_cmd_idx=0; sub_cmd_idx<CMD->sub_commands.size(); sub_cmd_idx++){
            	SESubCommand*& SUB_CMD = CMD->sub_commands[sub_cmd_idx];
                if (SUB_CMD->shortcut.similar(new_val)){ result = false; return;}
            }
        }
    }
}

void CCustomPreferences::OnKeyboardCommonFileClick(ButtonValue* B, bool& bModif, bool&)
{
    bModif = false;
    xr_string fn;
	switch(B->btn_num){
    case 0:
        if(EFS.GetOpenName("$import$", fn, false, NULL, 6)){
            CInifile* 	I 	= xr_new<CInifile>(fn.c_str(), TRUE, TRUE, TRUE);
		    LoadShortcuts	(I);
            xr_delete		(I);
            m_ItemProps->RefreshForm();
        }
    break;
    case 1:
        if(EFS.GetSaveName("$import$", fn, NULL, 6)){
		    CInifile* 	I 	= xr_new<CInifile>(fn.c_str(), FALSE, FALSE, TRUE);
		    SaveShortcuts	(I);
            xr_delete		(I);
        }
    break;
	}
}

void CCustomPreferences::FillProp(PropItemVec& props)
{
	xr_map<LPCSTR, SPreference>::iterator it, end;
    for(it = m_Prefs.begin(), end = m_Prefs.end(); it != end; it++)
    {
    	SPreference& R = it->second;
    	switch(R.Type)
        {
        	case ptBool: 	PHelper().CreateBOOL	(props, it->first, (BOOL*)R.IntValue); break;
            case ptInteger: PHelper().CreateU32		(props, it->first, R.IntValue, R.IntMin, R.IntMax, R.IntInc); break;
            case ptFloat:	PHelper().CreateFloat	(props, it->first, R.FloatValue, R.FloatMin, R.FloatMax, R.FloatInc, R.FloatDecimal); break;
			case ptAngle:	PHelper().CreateAngle	(props, it->first, R.FloatValue, R.FloatMin, R.FloatMax, R.FloatInc, R.FloatDecimal); break;
            case ptColor:	PHelper().CreateColor	(props, it->first, R.IntValue); break;
            case ptFlags:
			{
            	xr_vector<SPreference::SFlag>::iterator fl_it, fl_end;
                for(fl_it = R.Flags.begin(), fl_end = R.Flags.end(); fl_it != fl_end; fl_it++)
                	PHelper().CreateFlag32(props, (*fl_it).Name, R.FlagsValue, (*fl_it).Flag);
            }
        }
	}

    ButtonValue* B = PHelper().CreateButton	(props,"Keyboard\\Common\\File","Load,Save", 0);
    B->OnBtnClickEvent.bind	(this,&CCustomPreferences::OnKeyboardCommonFileClick);
    ECommandVec& cmds		= GetEditorCommands();
    for (u32 cmd_idx=0; cmd_idx<cmds.size(); cmd_idx++){
    	SECommand*& CMD		= cmds[cmd_idx];
        if (CMD&&CMD->editable){
        	VERIFY(!CMD->sub_commands.empty());
		    for (u32 sub_cmd_idx=0; sub_cmd_idx<CMD->sub_commands.size(); sub_cmd_idx++){
            	SESubCommand*& SUB_CMD = CMD->sub_commands[sub_cmd_idx];
                string128 nm; 		sprintf(nm,"%s%s%s",CMD->Desc(),!SUB_CMD->desc.empty()?"\\":"",SUB_CMD->desc.c_str());
                ShortcutValue* V 	= PHelper().CreateShortcut(props,PrepareKey("Keyboard\\Shortcuts",nm), &SUB_CMD->shortcut);
                V->OnValidateResultEvent.bind(CheckValidate);
			}
		}
	}

	// fonts
	static xr_vector<shared_str> fonts;
	fonts.clear();

	string_path fn;
	if(FS.exist(fn, "$game_config$", "fonts.ltx"))
	{
		CInifile *ini = CInifile::Create(fn);
		for(CInifile::RootIt it = ini->sections().begin(); it != ini->sections().end(); it++)
			fonts.push_back((*it)->Name);
		CInifile::Destroy(ini);
	}
	else
		fonts.push_back("hud_font_small");

	PHelper().CreateCaption(props, "Style\\Font\\Hint", "Font changes will take effect when you restart editor");
	PHelper().CreateRList(props, "Style\\Font\\Screen Font", &screen_font, &fonts.front(), fonts.size());
}

void CCustomPreferences::Edit()
{
    // fill prop
	PropItemVec props;

    FillProp						(props);

	m_ItemProps->AssignItems		(props);
    m_ItemProps->ShowPropertiesModal();

    // save changed options
	Save							();
}
//---------------------------------------------------------------------------

void CCustomPreferences::Load(CInifile* I)
{
	xr_map<LPCSTR, SPreference>::iterator p_it, p_end;
    for(p_it = m_Prefs.begin(), p_end = m_Prefs.end(); p_it != p_end; p_it++)
    {
    	SPreference& R = p_it->second;
        switch(R.Type)
        {
        	case ptBool: *R.IntValue = R_BOOL_SAFE(R.Section, R.Name, R.IntDefault); break;
            case ptFloat:
            case ptAngle: *R.FloatValue = R_FLOAT_SAFE(R.Section, R.Name, R.FloatDefault); break;
            case ptInteger:
            case ptColor: *R.IntValue = R_U32_SAFE(R.Section, R.Name, R.IntDefault); break;
            case ptFlags: R.FlagsValue->flags = R_U32_SAFE(R.Section, R.Name, R.FlagsDefault.flags); break;
        }
    }

	// read recent list    
    for (u32 i=0; i<scene_recent_count; i++){
    	shared_str fn  	= R_STRING_SAFE	("editor_prefs",AnsiString().sprintf("recent_files_%d",i).c_str(),shared_str("") );
        if (fn.size())
        {
        	AStringIt it =   std::find(scene_recent_list.begin(), scene_recent_list.end(), fn.c_str() ) ;
            if (it==scene_recent_list.end())
	        	scene_recent_list.push_back(*fn);
        }
    }
    sWeather 			= R_STRING_SAFE	("editor_prefs", "weather", shared_str("") );
    env_from_time 		= R_FLOAT_SAFE	("editor_prefs", "weather_from_time", 0.f);
    env_to_time 		= R_FLOAT_SAFE  ("editor_prefs", "weather_to_time", 24.f*60.f*60.f);
	env_speed			= R_FLOAT_SAFE	("editor_prefs", "weather_time_factor", 12.f);

	screen_font			= R_STRING_SAFE ("editor_prefs", "screen_font", shared_str("hud_font_small"));

    // load shortcuts
    LoadShortcuts		(I);

    UI->LoadSettings	(I);
}

void CCustomPreferences::Save(CInifile* I)
{
	xr_map<LPCSTR, SPreference>::iterator p_it, p_end;
    for(p_it = m_Prefs.begin(), p_end = m_Prefs.end(); p_it != p_end; p_it++)
    {
    	SPreference& R = p_it->second;
    	switch(R.Type)
        {
        	case ptBool: 	I->w_bool(R.Section, R.Name, !!(*R.IntValue)); break;
            case ptAngle:
            case ptFloat: 	I->w_float(R.Section, R.Name, *R.FloatValue); break;
            case ptInteger:
            case ptColor:	I->w_u32(R.Section, R.Name, *R.IntValue); break;
            case ptFlags:   I->w_u32(R.Section, R.Name, R.FlagsValue->flags); break;
        }
    }

    for (AStringIt it=scene_recent_list.begin(); it!=scene_recent_list.end(); it++){
    	AnsiString L; L.sprintf("recent_files_%d",it-scene_recent_list.begin());
    	AnsiString V; V.sprintf("\"%s\"",it->c_str());
		I->w_string("editor_prefs",L.c_str(),V.c_str());
    }
    I->w_string("editor_prefs", "weather",   sWeather.c_str() );
    I->w_float("editor_prefs", "weather_from_time", env_from_time);
    I->w_float("editor_prefs", "weather_to_time", env_to_time);
	I->w_float("editor_prefs", "weather_time_factor", env_speed);

	I->w_string("editor_prefs", "screen_font", screen_font.c_str() );

    // load shortcuts
    SaveShortcuts		(I);
    UI->SaveSettings	(I);
}

void CCustomPreferences::Load()
{
	string_path			fn;
	INI_NAME			(fn);
    CInifile* I			= xr_new<CInifile>(fn, TRUE, TRUE, TRUE);
    Load				(I);
    xr_delete			(I);
    ApplyValues			();
}
void CCustomPreferences::Save()
{
	string_path			fn;
	INI_NAME			(fn);
    CInifile* I 		= xr_new<CInifile>(fn, FALSE, TRUE, TRUE);
    I->set_override_names(TRUE);
	Save				(I);
	xr_delete			(I);
}

void CCustomPreferences::AppendRecentFile(LPCSTR name)
{
	if(scene_recent_count == 0)
		return;
		
    for (AStringIt it=scene_recent_list.begin(); it!=scene_recent_list.end(); it++){
    	if (*it==name){
        	scene_recent_list.erase	(it);
            break;
        }
    }
	scene_recent_list.insert(scene_recent_list.begin(),name);
	while (scene_recent_list.size()>=EPrefs->scene_recent_count) 
    	scene_recent_list.pop_back();

    ExecCommand				(COMMAND_REFRESH_UI_BAR);
}
//---------------------------------------------------------------------------

void CCustomPreferences::OnCreate()
{
	Load				();
	m_ItemProps 		= TProperties::CreateModalForm("Editor Preferences",false,0,0,TOnCloseEvent(this,&CCustomPreferences::OnClose),TProperties::plItemFolders|TProperties::plFullSort); //TProperties::plFullExpand TProperties::plFullSort TProperties::plNoClearStore|TProperties::plFolderStore|
}
//---------------------------------------------------------------------------

void CCustomPreferences::OnDestroy()
{
    TProperties::DestroyForm(m_ItemProps);
    Save				();
}
//---------------------------------------------------------------------------

