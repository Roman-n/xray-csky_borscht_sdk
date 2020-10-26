//---------------------------------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include <xrEngine/xr_input.h>
#include "UI_ToolsCustom.h"

#include "UI_Main.h"
#include <Layers/xrRender/D3DUtils.h>
#include "SoundManager.h"
#include <Layers/xrRender/PSLibrary.h>

#ifndef NO_VCL
#include "ImageEditor.h"
#include "SoundEditor.h"
#include "../../xrEProps/ChoseForm.h"
#endif
#include <utils/ETools/ETools.h>

#include "..\ImGui\imgui.h"
#include "..\ImGui\imgui_impl_dx9.h"
#include "..\ImGui\IM_Window.h"
#include "..\ImGui\IM_Log.h"

#include "..\ImGui\ImGuizmo.h"

static void ImGui_Init(HWND hwnd, IDirect3DDevice9 *d3ddevice)
{
	ImGui::CreateContext();
    ImGui_ImplDX9_Init(hwnd, d3ddevice);

    // load font
    ImGuiIO &io = ImGui::GetIO();
    ImFontAtlas &fonts 	= *io.Fonts;

	const char* font_name = "extras\\Anonymous Pro.ttf";
	if(FileExists(font_name))
	{
		ImFont *font = fonts.AddFontFromFileTTF(font_name, 14, NULL, fonts.GetGlyphRangesCyrillic());
		fonts.AddFontFromFileTTF(font_name, 24, NULL, fonts.GetGlyphRangesCyrillic());

		io.FontDefault = font;
	}
	else
		ELog.Msg(mtError, "Cannot find font file '%s'!", font_name);
}

static void ImGui_Shutdown(void)
{
	ImGui_ImplDX9_Shutdown();
    ImGui::DestroyContext();
}

TUI* 	UI			= 0;

TUI::TUI()
{
	UI				= this;
    m_bAppActive 	= false;
	m_bReady 		= false;
    m_D3DWindow 	= 0;
    m_D3DPanel		= 0;
    bNeedAbort   	= false;

	m_CurrentRStart.set(0,0,0);
	m_CurrentRNorm.set(0,0,0);

	m_Flags.assign	(flResize);

	m_Pivot.set		( 0, 0, 0 );

	m_MouseCaptured = false;
    m_MouseMultiClickCaptured = false;
 	m_SelectionRect = false;
    bMouseInUse		= false;

    m_bHintShowing	= false;
	m_pHintWindow	= 0;
	m_LastHint		= "";

    show_demo_window = false;
}
//---------------------------------------------------------------------------
TUI::~TUI()
{
	VERIFY(m_ProgressItems.size()==0);
    VERIFY(m_EditorState.size()==0);

    xr_vector<IM_Window*>::iterator it, end;
	for(it = imwindows.begin(), end = imwindows.end(); it != end; it++)
    {
    	(*it)->OnRemove();
    }
}

void TUI::OnDeviceCreate()
{
	DUImpl.OnDeviceCreate();
    ImGui_Init(m_D3DWindow->Handle, HW.pDevice);
}

void TUI::OnDeviceDestroy()
{
	DUImpl.OnDeviceDestroy();
    ImGui_Shutdown();
}

bool TUI::IsModified()
{
	return ExecCommand(COMMAND_CHECK_MODIFIED);
}
//---------------------------------------------------------------------------

void TUI::EnableSelectionRect( bool flag ){
	m_SelectionRect = flag;
	m_SelEnd.x = m_SelStart.x = 0;
	m_SelEnd.y = m_SelStart.y = 0;
}

void TUI::UpdateSelectionRect( const Ivector2& from, const Ivector2& to ){
	m_SelStart.set(from);
	m_SelEnd.set(to);
}

bool __fastcall TUI::KeyDown (WORD Key, TShiftState Shift)
{
	if (!m_bReady) return false;
//	m_ShiftState = Shift;
//	Log("Dn  ",Shift.Contains(ssShift)?"1":"0");

	if(Key < 256)
		ImGui::GetIO().KeysDown[Key] = true;

	if (ImGui::GetIO().WantCaptureKeyboard)
	{
		RedrawScene();
		return true;
	}

	if (Device.m_Camera.KeyDown(Key,Shift))
		return true;

	return Tools->KeyDown(Key, Shift);
}

bool __fastcall TUI::KeyUp   (WORD Key, TShiftState Shift)
{
	if (!m_bReady) return false;
//	m_ShiftState = Shift;

	if(Key < 256)
		ImGui::GetIO().KeysDown[Key] = false;

	if (ImGui::GetIO().WantCaptureKeyboard)
	{
		RedrawScene();
		return false;
	}

	if (Device.m_Camera.KeyUp(Key,Shift))
		return true;

	return Tools->KeyUp(Key, Shift);
}

bool __fastcall TUI::KeyPress(WORD Key, TShiftState Shift)
{
	if (!m_bReady) return false;

	ImGui::GetIO().AddInputCharacter(Key);
	if (ImGui::GetIO().WantCaptureKeyboard)
	{
		RedrawScene();
		return true;
	}

	return Tools->KeyPress(Key, Shift);
}
//----------------------------------------------------

void TUI::MousePress(TShiftState Shift, int X, int Y)
{
	if (!m_bReady) return;
    if (m_MouseCaptured) return;

    bMouseInUse = true;

    m_ShiftState = Shift;

    ImGui::GetIO().MouseDown[0] = Shift.Contains(ssLeft);
    ImGui::GetIO().MouseDown[1] = Shift.Contains(ssRight);
    ImGui::GetIO().MouseDown[2] = Shift.Contains(ssMiddle);

    // camera activate
    if(!ImGui::GetIO().WantCaptureMouse && !Device.m_Camera.MoveStart(m_ShiftState)){
    	if (Tools->Pick(Shift)) return;
        if( !m_MouseCaptured ){
            if( Tools->HiddenMode() ){
				IR_GetMousePosScreen(m_StartCpH);
                m_DeltaCpH.set(0,0);
            }else{
                IR_GetMousePosReal(Device.m_hRenderWnd, m_CurrentCp);
                m_StartCp = m_CurrentCp;
                Device.m_Camera.MouseRayFromPoint(m_CurrentRStart, m_CurrentRNorm, m_CurrentCp );
            }

            if(Tools->MouseStart(m_ShiftState)){
                if(Tools->HiddenMode()) ShowCursor( FALSE );
                m_MouseCaptured = true;
            }
        }
    }
    RedrawScene();
}

void TUI::MouseRelease(TShiftState Shift, int X, int Y)
{
	if (!m_bReady) return;

    m_ShiftState = Shift;

    ImGui::GetIO().MouseDown[0] = Shift.Contains(ssLeft);
    ImGui::GetIO().MouseDown[1] = Shift.Contains(ssRight);
    ImGui::GetIO().MouseDown[2] = Shift.Contains(ssMiddle);

    // editor may need to know about mouse release even it hover imgui window

    if( Device.m_Camera.IsMoving() ){
        if (Device.m_Camera.MoveEnd(m_ShiftState)) bMouseInUse = false;
    }else{
	    bMouseInUse = false;
        if( m_MouseCaptured ){
            if( !Tools->HiddenMode() ){
                IR_GetMousePosReal(Device.m_hRenderWnd, m_CurrentCp);
                Device.m_Camera.MouseRayFromPoint(m_CurrentRStart,m_CurrentRNorm,m_CurrentCp );
            }
            if( Tools->MouseEnd(m_ShiftState) ){
                if( Tools->HiddenMode() ){
                    SetCursorPos(m_StartCpH.x,m_StartCpH.y);
                    ShowCursor( TRUE );
                }
                m_MouseCaptured = false;
            }
        }
    }
    // update tools (change action)
    Tools->OnFrame	();
    RedrawScene		();
}
//----------------------------------------------------
void TUI::MouseMove(TShiftState Shift, int X, int Y)
{
	if (!m_bReady) return;
    m_ShiftState = Shift;

    ImGui::GetIO().MousePos.x = ((float)X * Device.m_ScreenQuality);
    ImGui::GetIO().MousePos.y = ((float)Y * Device.m_ScreenQuality);

    RedrawScene();
}
//----------------------------------------------------
void TUI::IR_OnMouseMove(int x, int y){
	if (!m_bReady) return;
    bool bRayUpdated = false;

	if (!Device.m_Camera.Process(m_ShiftState,x,y)){
        if( m_MouseCaptured || m_MouseMultiClickCaptured ){
            if( Tools->HiddenMode() ){
				m_DeltaCpH.set(x,y);
                if( m_DeltaCpH.x || m_DeltaCpH.y ){
                	Tools->MouseMove(m_ShiftState);
                }
            }else{
                IR_GetMousePosReal(Device.m_hRenderWnd, m_CurrentCp);
                Device.m_Camera.MouseRayFromPoint(m_CurrentRStart,m_CurrentRNorm,m_CurrentCp);
                Tools->MouseMove(m_ShiftState);
            }
		    RedrawScene();
            bRayUpdated = true;
        }
    }
    if (!bRayUpdated){
		IR_GetMousePosReal(Device.m_hRenderWnd, m_CurrentCp);
        Device.m_Camera.MouseRayFromPoint(m_CurrentRStart,m_CurrentRNorm,m_CurrentCp);
    }
    // Out cursor pos
    OutUICursorPos	();
}

void TUI::IR_OnMouseWheel(int direction)
{
    ImGui::GetIO().MouseWheel = direction > 0 ? +1.0f : -1.0f;
    RedrawScene();
}
//---------------------------------------------------------------------------

void TUI::OnAppActivate()
{
	VERIFY(m_bReady);
	if (pInput){
        m_ShiftState.Clear();
     	pInput->OnAppActivate();
        Device.seqAppActivate.Process	(rp_AppActivate);
    }
    m_bAppActive 	= true;
}
//---------------------------------------------------------------------------

void TUI::OnAppDeactivate()
{
	VERIFY(m_bReady);
	if (pInput){
		pInput->OnAppDeactivate();
        m_ShiftState.Clear();
        Device.seqAppDeactivate.Process(rp_AppDeactivate);
    }
    HideHint();
    m_bAppActive 	= false;
}
//---------------------------------------------------------------------------

AnsiString _ListToSequence2(const AStringVec& lst)
{
    AnsiString out;
    out = "";
    if (lst.size()) {
        out = lst.front();
        for (AStringVec::const_iterator s_it = lst.begin() + 1; s_it != lst.end(); s_it++) {
            out += AnsiString("\n") + (*s_it);
        }
    }
    return out;
}

bool TUI::ShowHint(const AStringVec& SS)
{
	VERIFY(m_bReady);
    if (SS.size()){
        AnsiString S=_ListToSequence2(SS);
        if (m_bHintShowing&&(S==m_LastHint)) return true;
        m_LastHint = S;
        m_bHintShowing = true;
        #ifndef NO_VCL
        if (!m_pHintWindow){
            m_pHintWindow = xr_new<THintWindow>((TComponent*)0);
            m_pHintWindow->Brush->Color = (TColor)0x0d9F2FF;
        }
        TRect rect = m_pHintWindow->CalcHintRect(320,S,0);
        rect.Left+=m_HintPoint.x;    rect.Top+=m_HintPoint.y;
        rect.Right+=m_HintPoint.x;   rect.Bottom+=m_HintPoint.y;
        m_pHintWindow->ActivateHint(rect,S);
        #endif
    }else{
    	m_bHintShowing = false;
        m_LastHint = "";
    }
    return m_bHintShowing;
}
//---------------------------------------------------------------------------

void TUI::HideHint()
{
	VERIFY(m_bReady);
    m_bHintShowing = false;
    xr_delete(m_pHintWindow);
}
//---------------------------------------------------------------------------

void TUI::ShowHint(const AnsiString& s)
{
	VERIFY			(m_bReady);
    GetCursorPos	(&m_HintPoint);
	AStringVec 		SS;
    SS.push_back	(s);
	Tools->OnShowHint(SS);
    if (!ShowHint(SS)&&m_pHintWindow) HideHint();
}
//---------------------------------------------------------------------------

void TUI::ShowObjectHint()
{
	VERIFY(m_bReady);
    if (!EPrefs->object_flags.is(epoShowHint)){
//    	if (m_bHintShowing) HideHint();
    	return;
    }
    if (Device.m_Camera.IsMoving()||m_MouseCaptured) return;
    if (!m_bAppActive) return;

    GetCursorPos(&m_HintPoint);
    #ifndef NO_VCL
    TWinControl* ctr = FindVCLWindow(m_HintPoint);
    if (ctr!=m_D3DWindow) return;
    #endif

	AStringVec SS;
	Tools->OnShowHint(SS);
    if (!ShowHint(SS)&&m_pHintWindow) HideHint();
}
//---------------------------------------------------------------------------
void TUI::CheckWindowPos(TForm* form)
{
    #ifndef NO_VCL
	if (form->Left+form->Width>Screen->Width) 	form->Left	= Screen->Width-form->Width;
	if (form->Top+form->Height>Screen->Height)	form->Top 	= Screen->Height-form->Height;
	if (form->Left<0) 							form->Left	= 0;
	if (form->Top<0) 							form->Top 	= 0;
    #endif
}
//---------------------------------------------------------------------------
#include <xrEngine/IGame_Persistent.h>
#include <xrEngine/Environment.h>
    static bool b_imgui_rendering = false;
void TUI::PrepareRedraw()
{
	VERIFY(m_bReady);
	if (m_Flags.is(flResize)) 			RealResize();
// set render state
    Device.SetRS(D3DRS_TEXTUREFACTOR,	0xffffffff);
    // fog
    u32 fog_color;
	float fog_start, fog_end;
    Tools->GetCurrentFog	(fog_color, fog_start, fog_end);
/*
    if (0==g_pGamePersistent->Environment().GetWeather().size())
    {
        g_pGamePersistent->Environment().CurrentEnv->fog_color.set	(color_get_R(fog_color),color_get_G(fog_color),color_get_B(fog_color));
        g_pGamePersistent->Environment().CurrentEnv->fog_far		= fog_end;
        g_pGamePersistent->Environment().CurrentEnv->fog_near		= fog_start;
    }
*/    
	Device.SetRS( D3DRS_FOGCOLOR,		fog_color			);         
	Device.SetRS( D3DRS_RANGEFOGENABLE,	FALSE				);
	if (HW.Caps.bTableFog)	{
		Device.SetRS( D3DRS_FOGTABLEMODE,	D3DFOG_LINEAR 	);
		Device.SetRS( D3DRS_FOGVERTEXMODE,	D3DFOG_NONE	 	);
	} else {
		Device.SetRS( D3DRS_FOGTABLEMODE,	D3DFOG_NONE	 	);
		Device.SetRS( D3DRS_FOGVERTEXMODE,	D3DFOG_LINEAR	);
	}
	Device.SetRS( D3DRS_FOGSTART,	*(DWORD *)(&fog_start)	);
	Device.SetRS( D3DRS_FOGEND,		*(DWORD *)(&fog_end)	);
    // filter
    for (u32 k=0; k<HW.Caps.raster.dwStages; k++){
        if( psDeviceFlags.is(rsFilterLinear)){
            Device.SetSS(k,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
            Device.SetSS(k,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
            Device.SetSS(k,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
        } else {
            Device.SetSS(k,D3DSAMP_MAGFILTER,D3DTEXF_POINT);
            Device.SetSS(k,D3DSAMP_MINFILTER,D3DTEXF_POINT);
            Device.SetSS(k,D3DSAMP_MIPFILTER,D3DTEXF_POINT);
        }
    }
	// ligthing
    if (psDeviceFlags.is(rsLighting)) 	Device.SetRS(D3DRS_AMBIENT,0x00000000);
    else                				Device.SetRS(D3DRS_AMBIENT,0xFFFFFFFF);

    Device.SetRS			(D3DRS_FILLMODE, Device.dwFillMode);
    Device.SetRS			(D3DRS_SHADEMODE,Device.dwShadeMode);

    RCache.set_xform_world	(Fidentity);

    if(!b_imgui_rendering)
    {
    	b_imgui_rendering = true;

        ImGui_ImplDX9_NewFrame();
        ImGui::GetIO().DisplaySize = ImVec2(Device.dwWidth, Device.dwHeight);
        
        ImGuizmo::BeginFrame();

    	if(show_demo_window)
    		ImGui::ShowDemoWindow(&show_demo_window);

        xr_vector<IM_Window*> windows = imwindows; // copy
    	for(xr_vector<IM_Window*>::iterator it = windows.begin(); it != windows.end(); it++)
			(*it)->Render();

        b_imgui_rendering = false;
    }
}
void TUI::Redraw()
{
	PrepareRedraw();
    try{
    	Device.Statistic->RenderDUMP_RT.Begin();
        if (Device.Begin()){
            Device.UpdateView		();
            Device.ResetMaterial	();

            Tools->RenderEnvironment	();

            //. temporary reset filter (уберется после того как Олесь сделает шейдеры)
            for (u32 k=0; k<HW.Caps.raster.dwStages; k++){
                if( psDeviceFlags.is(rsFilterLinear)){
                    Device.SetSS(k,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
                    Device.SetSS(k,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
                    Device.SetSS(k,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
                } else {
                    Device.SetSS(k,D3DSAMP_MAGFILTER,D3DTEXF_POINT);
                    Device.SetSS(k,D3DSAMP_MINFILTER,D3DTEXF_POINT);
                    Device.SetSS(k,D3DSAMP_MIPFILTER,D3DTEXF_POINT);
                }
            }

            // draw grid
            if (psDeviceFlags.is(rsDrawGrid)){
                DUImpl.DrawGrid		();
                DUImpl.DrawPivot		(m_Pivot);
            }

            try{
	            Tools->Render			();
		    }catch(...){
		    	ELog.DlgMsg(mtError, "Please notify AlexMX!!! Critical error has occured in render routine!!! [Type B]");
            }

            if(!b_imgui_rendering) {
            	ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            }

            // draw selection rect
            if(m_SelectionRect) 	DUImpl.DrawSelectionRect(m_SelStart,m_SelEnd);

            // draw axis
            DUImpl.DrawAxis(Device.m_Camera.GetTransform());

            try{
	            // end draw
    	        Device.End();
		    }catch(...){
		    	ELog.DlgMsg(mtError, "Please notify AlexMX!!! Critical error has occured in render routine!!! [Type C]");
            }
        }
    	Device.Statistic->RenderDUMP_RT.End();
    }catch(...){
    	ELog.DlgMsg(mtError, "Please notify AlexMX!!! Critical error has occured in render routine!!! [Type A]");
//		_clear87();
//		FPU::m24r();
//    	ELog.DlgMsg(mtError, "Critical error has occured in render routine.\nEditor may work incorrectly.");
        Device.End();
//		Device.Resize(m_D3DWindow->Width,m_D3DWindow->Height);
    }

	OutInfo();
}
//---------------------------------------------------------------------------
void TUI::RealResize()
{
   	ImGui_Shutdown		();
    Device.Resize		(m_D3DWindow->Width,m_D3DWindow->Height); 
    m_Flags.set			(flResize,FALSE);
    ExecCommand			(COMMAND_UPDATE_PROPERTIES);
	ImGui_Init			(m_D3DWindow->Handle, HW.pDevice);
}
void TUI::RealUpdateScene()
{
    Tools->UpdateProperties	(false);
    m_Flags.set			(flUpdateScene,FALSE);
}
void TUI::RealRedrawScene()
{
    if (!psDeviceFlags.is(rsRenderRealTime)) 
    	m_Flags.set		(flRedraw,FALSE);
    Redraw				();         
}
void TUI::OnFrame()
{
	Device.FrameMove	();
    SndLib->OnFrame		();
    // tools on frame
    if (m_Flags.is(flUpdateScene)) RealUpdateScene();
    Tools->OnFrame		();
	// show hint
    ShowObjectHint		();
	ResetBreak			();
#if USE_MAILSLOT
	// check mail
    CheckMailslot		();
#endif
    // OnFrame
    #ifndef NO_VCL
    TfrmImageLib::OnFrame();
    TfrmSoundLib::OnFrame();
    TfrmChoseItem::OnFrame();
    #endif
    // Progress
    ProgressDraw		();
}
void TUI::Idle()         
{
	VERIFY(m_bReady);
#ifndef NO_VCL
    Device.b_is_Active  = Application->Active;
#else
    Device.b_is_Active  = !!GetActiveWindow();
#endif
	// input
    pInput->OnFrame();
    Sleep(1);
    if (ELog.in_use) return;

    OnFrame			();
    if (m_Flags.is(flRedraw))	RealRedrawScene();

    // test quit
    if (m_Flags.is(flNeedQuit))	RealQuit();
}
//---------------------------------------------------------------------------
void ResetActionToSelect()
{
    ExecCommand(COMMAND_CHANGE_ACTION, etaSelect);
}
//---------------------------------------------------------------------------

#define MIN_PANEL_HEIGHT 15
void __fastcall PanelMinMax(TPanel *pa)
{
    #ifndef NO_VCL
	if (pa&&(pa->Align!=alClient)){
        if (pa->Tag > 0){
            pa->Height = pa->Tag;
            pa->Tag    = 0;
        }else{
            pa->Tag    = pa->Height;
            pa->Height = MIN_PANEL_HEIGHT;
        }
        ExecCommand(COMMAND_UPDATE_TOOLBAR);
    }
    #endif
}
void __fastcall PanelMinimize(TPanel *pa)
{
    #ifndef NO_VCL
	if (pa&&(pa->Align!=alClient)){
        if (pa->Tag <= 0){
            pa->Tag    = pa->Height;
            pa->Height = MIN_PANEL_HEIGHT;
        }
        ExecCommand(COMMAND_UPDATE_TOOLBAR);
    }
    #endif
}
void __fastcall PanelMaximize(TPanel *pa)
{
    #ifndef NO_VCL
	if (pa&&(pa->Align!=alClient)){
        if (pa->Tag > 0){
            pa->Height = pa->Tag;
            pa->Tag    = 0;
        }
        ExecCommand(COMMAND_UPDATE_TOOLBAR);
    }
    #endif
}
void __fastcall PanelMinMaxClick(TObject* Sender)
{
#ifndef NO_VCL
    PanelMinMax(((TPanel*)((TControl*)Sender)->Parent));
#endif
}
void __fastcall PanelMinimizeClick(TObject* Sender)
{
#ifndef NO_VCL
    PanelMinimize(((TPanel*)((TControl*)Sender)->Parent));
#endif
}
void __fastcall PanelMaximizeClick(TObject* Sender)
{
#ifndef NO_VCL
    PanelMaximize(((TPanel*)((TControl*)Sender)->Parent));
#endif
}
//---------------------------------------------------------------------------

bool TUI::OnCreate(TD3DWindow* w, TPanel* p)
{
// create base class
	Device.InitTimer();

    m_D3DWindow 	= w;
    m_D3DPanel		= p;
    VERIFY(m_D3DWindow);
    Device.Initialize();
    
	// Creation
	ETOOLS::ray_options	(CDB::OPT_ONLYNEAREST | CDB::OPT_CULL);

    pInput			= xr_new<CInput>(FALSE,mouse_device_key);
    UI->IR_Capture	();

    m_bReady		= true;

#if USE_MAILSLOT
    if (!CreateMailslot()){
    	ELog.DlgMsg	(mtError,"Can't create mail slot.\nIt's possible two Editors started.");
        return 		false;
    }
#endif

    if (!FS.path_exist(_local_root_)){
    	ELog.DlgMsg	(mtError,"Undefined Editor local directory.");
        return 		false;
    }

	BeginEState		(esEditScene);

    AddIMWindow(&imLog);

    return true;
}

void TUI::OnDestroy()
{
	VERIFY(m_bReady);
	m_bReady		= false;
	UI->IR_Release	();
    xr_delete		(pInput);
    EndEState		();

    Device.ShutDown	();
    
}

SPBItem* TUI::ProgressStart		(float max_val, LPCSTR text)
{
	VERIFY(m_bReady);
	SPBItem* item 				= xr_new<SPBItem>(text,"",max_val);
    m_ProgressItems.push_back	(item);
    ELog.Msg					(mtInformation,text);
    ProgressDraw				();
	return item;
}
void TUI::ProgressEnd			(SPBItem*& pbi)
{
	VERIFY(m_bReady);
    if (pbi){
        PBVecIt it=std::find(m_ProgressItems.begin(),m_ProgressItems.end(),pbi); VERIFY(it!=m_ProgressItems.end());
        m_ProgressItems.erase	(it);
        xr_delete				(pbi);
        ProgressDraw			();
    }
}

void SPBItem::GetInfo			(AnsiString& txt, float& p, float& m)
{
    txt = text.c_str();
    if (info.size()) {
        txt += " (";
        txt += info.c_str();
        txt += ")";
    }
    p				= progress;
    m				= max;
}  
void SPBItem::Inc				(LPCSTR info, bool bWarn)
{
    Info						(info,bWarn);
    Update						(progress+1.f);
}
void SPBItem::Update			(float val)
{
    progress					= val;
    UI->ProgressDraw			();
}
void SPBItem::Info				(LPCSTR text, bool bWarn)
{
	if (text&&text[0]){
    	info					= text;
        AnsiString 				txt;
        float 					p,m;
        GetInfo					(txt,p,m);
	    ELog.Msg				(bWarn?mtError:mtInformation,txt.c_str());
	    UI->ProgressDraw		();
    }
}

void TUI::AddIMWindow(IM_Window *wnd)
{
	imwindows.push_back(wnd);
    wnd->OnAdd();
}

void TUI::RemoveIMWindow(IM_Window* wnd)
{
	xr_vector<IM_Window*>::iterator it, end;
	for(it = imwindows.begin(), end = imwindows.end(); it != end; it++)
    {
    	if(*it == wnd)
        {
        	(*it)->OnRemove();
        	imwindows.erase(it);
            return;
        }
    }
}
