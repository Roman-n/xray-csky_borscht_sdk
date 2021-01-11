#include "stdafx.h"	
#pragma hdrstop

#include <commctrl.h>
#include "StatusBar.h"

#include "..\ECore\ImGui\IM_Log.h"
#include "..\ECore\ImGui\IM_PropertyTree.h"
#include "..\ECore\Editor\ui_main.h"
#include <xrEngine\igame_persistent.h>
#include <xrEngine\environment.h>

// menu item identifiers 
#define MI_LIGHTSCENE 101
#define MI_SHOWSTATS  102
#define MI_REALTIME   103
#define MI_DRAWSAFE   104
#define MI_DRAWGRID   105
#define MI_FOG        106
#define MI_MUTESOUNDS 107

#define MI_FILLSOLID  110
#define MI_FILLLINE   111
#define MI_FILLPOINT  112

#define MI_SHADEFLAT  113
#define MI_SHADEGOURAUD 114

#define MI_EDGEDFACES 115

#define MI_HWRENDER   116
#define MI_LINEARFLT  117
#define MI_TEXTURES   118

#define MI_QUALITY25  120
#define MI_QUALITY50  121
#define MI_QUALITY75  122
#define MI_QUALITY100 123
#define MI_QUALITY125 124
#define MI_QUALITY150 125
#define MI_QUALITY175 126
#define MI_QUALITY200 127

// weather
#define MI_W_RELOAD   130
#define MI_W_PROPS    131
#define MI_W_NONE     132
#define MI_W_ENTRY    133

#define MI_TIMEFACTOR_005 200
#define MI_TIMEFACTOR_01  201
#define MI_TIMEFACTOR_02  202
#define MI_TIMEFACTOR_03  203
#define MI_TIMEFACTOR_05  204
#define MI_TIMEFACTOR_10  205
#define MI_TIMEFACTOR_30  206
#define MI_TIMEFACTOR_50  207
#define MI_TIMEFACTOR_100 208

static HWND hSB;
static HMENU hmOptions;
static xr_string status;

static void CheckMenu(int item, BOOL check)
{
	CheckMenuItem(hmOptions, item, MF_BYCOMMAND|(check?MF_CHECKED:0));
}

static void UpdateMenu(void)
{
	CheckMenu(MI_DRAWSAFE, psDeviceFlags.test(rsDrawSafeRect));
	CheckMenu(MI_DRAWGRID, psDeviceFlags.test(rsDrawGrid));
	
	CheckMenu(MI_FOG, psDeviceFlags.test(rsFog));
	
	CheckMenu(MI_MUTESOUNDS, psDeviceFlags.test(rsMuteSounds));
	CheckMenu(MI_LIGHTSCENE, psDeviceFlags.test(rsLighting));
	CheckMenu(MI_SHOWSTATS, psDeviceFlags.test(rsStatistic));
	CheckMenu(MI_REALTIME, psDeviceFlags.test(rsRenderRealTime));
	
	CheckMenu(MI_FILLSOLID, Device.dwFillMode == D3DFILL_SOLID);
	CheckMenu(MI_FILLLINE, Device.dwFillMode == D3DFILL_WIREFRAME);
	CheckMenu(MI_FILLPOINT, Device.dwFillMode == D3DFILL_POINT);
	
	CheckMenu(MI_SHADEFLAT, Device.dwShadeMode == D3DSHADE_FLAT);
	CheckMenu(MI_SHADEGOURAUD, Device.dwShadeMode == D3DSHADE_GOURAUD);
	
	CheckMenu(MI_EDGEDFACES, psDeviceFlags.test(rsEdgedFaces));
	
	CheckMenu(MI_HWRENDER, !HW.Caps.bForceGPU_SW);
	
	CheckMenu(MI_LINEARFLT, psDeviceFlags.test(rsFilterLinear));
	CheckMenu(MI_TEXTURES, psDeviceFlags.test(rsRenderTextures));
	
	CheckMenu(MI_W_NONE, !psDeviceFlags.test(rsEnvironment));
}

static void CreateOptionsMenu(void)
{
	hmOptions = CreatePopupMenu();
	
	HMENU hmRender = CreatePopupMenu();
	
	HMENU hmQuality = CreatePopupMenu();
	for(int i = 0; i < 8; i++)
	{
		int quality = (i+1)*25;
		int s = fsimilar(quality*0.01f, Device.m_ScreenQuality) ? MF_CHECKED : MF_UNCHECKED;
		
		char str[64];
		sprintf(str, "%d%%", quality);
		AppendMenu(hmQuality, MF_ENABLED|MF_STRING|s, MI_QUALITY25+i, str);
	}
	
	AppendMenu(hmRender, MF_ENABLED|MF_POPUP, (UINT_PTR)hmQuality, "Quality");
	
	HMENU hmFill = CreatePopupMenu();
	AppendMenu(hmFill, MF_ENABLED|MF_STRING, MI_FILLSOLID, "Solid");
	AppendMenu(hmFill, MF_ENABLED|MF_STRING, MI_FILLLINE, "Line");
	AppendMenu(hmFill, MF_ENABLED|MF_STRING, MI_FILLPOINT, "Point");
	
	AppendMenu(hmRender, MF_ENABLED|MF_POPUP, (UINT_PTR)hmFill, "Fill Mode");
	
	HMENU hmShade = CreatePopupMenu();
	AppendMenu(hmShade, MF_ENABLED|MF_STRING, MI_SHADEFLAT, "Flat");
	AppendMenu(hmShade, MF_ENABLED|MF_STRING, MI_SHADEGOURAUD, "Gouraud");
	
	AppendMenu(hmRender, MF_ENABLED|MF_POPUP, (UINT_PTR)hmShade, "Shade Mode");
	AppendMenu(hmRender, MF_ENABLED|MF_STRING, MI_EDGEDFACES, "Edged Faces");
	AppendMenu(hmRender, MF_SEPARATOR, 0, 0);
	AppendMenu(hmRender, MF_ENABLED|MF_STRING, MI_HWRENDER, "HW Render");
	AppendMenu(hmRender, MF_SEPARATOR, 0, 0);
	AppendMenu(hmRender, MF_ENABLED|MF_STRING, MI_LINEARFLT, "Linear Filter");
	AppendMenu(hmRender, MF_ENABLED|MF_STRING, MI_TEXTURES, "Textures");
	
	HMENU hmWeather = CreatePopupMenu();
	AppendMenu(hmWeather, MF_ENABLED|MF_STRING, MI_W_NONE, "none");
	AppendMenu(hmWeather, MF_SEPARATOR, 0, 0);
	CEnvironment::EnvsMapIt _I=g_pGamePersistent->Environment().WeatherCycles.begin();
	CEnvironment::EnvsMapIt _E=g_pGamePersistent->Environment().WeatherCycles.end();
	for (int idx = 0; _I!=_E; _I++){
		int s = 
			psDeviceFlags.test(rsEnvironment) && 
			g_pGamePersistent->Environment().GetWeather() == _I->first 
			? MF_CHECKED : MF_UNCHECKED;
			
		AppendMenu(hmWeather, MF_ENABLED|MF_STRING|s, MI_W_ENTRY+idx, *_I->first);   
		idx++;
	}
	AppendMenu(hmWeather, MF_SEPARATOR, 0, 0);
	AppendMenu(hmWeather, MF_ENABLED|MF_STRING, MI_W_RELOAD, "Reload");
	AppendMenu(hmWeather, MF_ENABLED|MF_STRING, MI_W_PROPS, "Properties...");
	
	AppendMenu(hmOptions, MF_ENABLED|MF_POPUP, (UINT_PTR)hmRender, "Render");
	AppendMenu(hmOptions, MF_SEPARATOR, 0, 0);
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_DRAWSAFE, "Draw Safe Rect");
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_DRAWGRID, "Draw Grid");
	AppendMenu(hmOptions, MF_SEPARATOR, 0, 0);
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_FOG, "Fog");
	AppendMenu(hmOptions, MF_ENABLED|MF_POPUP, (UINT_PTR)hmWeather, "Weather");
	AppendMenu(hmOptions, MF_SEPARATOR, 0, 0);
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_MUTESOUNDS, "Mute Sounds");
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_LIGHTSCENE, "Light Scene");
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_SHOWSTATS, "Show Statistic");
	AppendMenu(hmOptions, MF_ENABLED|MF_STRING, MI_REALTIME, "Real Time");
	
	HMENU hmDevice = CreatePopupMenu();
	
	HMENU hmTimeFactor = CreatePopupMenu();
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_005, "0.05");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_01, "0.1");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_02, "0.2");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_03, "0.3");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_05, "0.5");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_10, "1.0");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_30, "3.0");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_50, "5.0");
	AppendMenu(hmTimeFactor, MF_ENABLED|MF_STRING, MI_TIMEFACTOR_100, "10.0");
	
	AppendMenu(hmDevice, MF_ENABLED|MF_POPUP, (UINT_PTR)hmTimeFactor, "Time Factor");
	
	AppendMenu(hmOptions, MF_ENABLED|MF_POPUP, (UINT_PTR)hmDevice, "Device");
	
	UpdateMenu();
}

static void DestroyOptionsMenu(void)
{
	DestroyMenu(hmOptions);
	hmOptions = NULL;
}

static void UpdateParts(void)
{
	RECT r;
	GetClientRect(hSB, &r);
	int width = r.right-r.left;

	int parts[8];
	parts[0] = 70;          // options
	parts[1] = 115;         // log
	parts[2] = 160;         // break
	parts[3] = width-380;   // status
	parts[4] = width-300;   // selection count
	parts[5] = width-180;   // camera pos
	parts[6] = width-80;    // cursor pos
	parts[7] = width;       // grid
	
	SendMessage(hSB, SB_SETPARTS, (WPARAM)8, (LPARAM)parts);
}

static BOOL SB_Notify(WPARAM wParam, LPARAM lParam)
{
	if( ((LPNMHDR)lParam)->code == NM_CLICK )
	{
		LPNMMOUSE m = (LPNMMOUSE)lParam;
		
		if(m->dwItemSpec == 0)
		{
			POINT p;
			GetCursorPos(&p);
			
			CreateOptionsMenu();
			int cmd = (int)TrackPopupMenu(hmOptions, TPM_NONOTIFY|TPM_RETURNCMD, p.x, p.y, 0, hSB, NULL);
			
			if(cmd == MI_DRAWSAFE)
				ExecCommand(COMMAND_TOGGLE_SAFE_RECT);
			if(cmd == MI_DRAWGRID)
				ExecCommand(COMMAND_TOGGLE_GRID);
				
			if(cmd == MI_FOG)
				psDeviceFlags.invert(rsFog);	
			
			if(cmd == MI_MUTESOUNDS)
				psDeviceFlags.invert(rsMuteSounds);
			if(cmd == MI_LIGHTSCENE)
				psDeviceFlags.invert(rsLighting);		
			if(cmd == MI_SHOWSTATS)
				psDeviceFlags.invert(rsStatistic);
			if(cmd == MI_REALTIME)
				psDeviceFlags.invert(rsRenderRealTime);
			
			if(cmd >= MI_QUALITY25 && cmd <= MI_QUALITY200)
			{					 
				switch(cmd)
				{
					case MI_QUALITY25:  UI->SetRenderQuality(0.25f); break;
					case MI_QUALITY50:  UI->SetRenderQuality(0.50f); break;
					case MI_QUALITY75:  UI->SetRenderQuality(0.75f); break;
					case MI_QUALITY100: UI->SetRenderQuality(1.00f); break;
					case MI_QUALITY125: UI->SetRenderQuality(1.25f); break;
					case MI_QUALITY150: UI->SetRenderQuality(1.50f); break;
					case MI_QUALITY175: UI->SetRenderQuality(1.75f); break;
					case MI_QUALITY200: UI->SetRenderQuality(2.00f); break;
				};
				UI->Resize();
			}
				
			if(cmd == MI_FILLSOLID)
				Device.dwFillMode = D3DFILL_SOLID;
			if(cmd == MI_FILLLINE)
				Device.dwFillMode = D3DFILL_WIREFRAME;
			if(cmd == MI_FILLPOINT)
				Device.dwFillMode = D3DFILL_POINT;
				
			if(cmd == MI_SHADEFLAT)
				Device.dwShadeMode = D3DSHADE_FLAT;
			if(cmd == MI_SHADEGOURAUD)
				Device.dwShadeMode = D3DSHADE_GOURAUD;
				
			if(cmd == MI_EDGEDFACES)
				psDeviceFlags.invert(rsEdgedFaces);
				
			if(cmd == MI_HWRENDER)
			{
				HW.Caps.bForceGPU_SW = !HW.Caps.bForceGPU_SW;
				UI->Resize();
			}
			
			if(cmd == MI_LINEARFLT)
				psDeviceFlags.invert(rsFilterLinear);
			if(cmd == MI_TEXTURES)
				psDeviceFlags.invert(rsRenderTextures);
				
			if(cmd == MI_W_RELOAD)
			{
				Engine.ReloadSettings();
				g_pGamePersistent->Environment().ED_Reload();
			}
			if(cmd == MI_W_PROPS)
			{
				class WeatherProps
				{
					public:
					IM_PropertiesWnd *m_wnd;
					float ft, tt, sp;
					
					WeatherProps()
					{
						m_wnd = xr_new<IM_PropertiesWnd>("Weather Properties");
						m_wnd->Modal = true;
						m_wnd->OnClose.bind(this, &WeatherProps::OnClose);
						m_wnd->OnOK.bind(this, &WeatherProps::OnOK);
						
						CEnvironment& env	= g_pGamePersistent->Environment();
						PropItemVec items;
						ft=env.ed_from_time;
						tt=env.ed_to_time;
						sp=env.fTimeFactor;
						PHelper().CreateTime	(items,"From Time", 	&ft);
						PHelper().CreateTime	(items,"To Time",   	&tt);
						PHelper().CreateFloat	(items,"Speed",			&sp, 		1.f,10000.f,1.f,1);
						
						m_wnd->AssignItems(items);
						
						m_wnd->Open();
						UI->AddIMWindow(m_wnd);
					}
					
					void OnOK()
					{
						CEnvironment& env	= g_pGamePersistent->Environment();
						env.ed_from_time	= ft;
						env.ed_to_time		= tt;
						env.fTimeFactor		= sp;
					}
					
				 	void OnClose()
					{
						UI->RemoveIMWindow(m_wnd);
						xr_delete(m_wnd);
						
						WeatherProps *_this = this;
						xr_delete(_this);
					}
				};
				
				xr_new<WeatherProps>();
			}
			if(cmd == MI_W_NONE)
			{
				psDeviceFlags.set	(rsEnvironment,FALSE);
				g_pGamePersistent->Environment().SetWeather(0);
				EPrefs->sWeather = "";
		}
		if(cmd >= MI_W_ENTRY && cmd < MI_TIMEFACTOR_005)
		{
			char name[256];
			if(GetMenuString(hmOptions, cmd, name, 255, MF_BYCOMMAND))
			{
					psDeviceFlags.set	(rsEnvironment,TRUE);
					g_pGamePersistent->Environment().SetWeather(name);
					EPrefs->sWeather = name;
			}
		}
		
		if(cmd >= MI_TIMEFACTOR_005 && cmd <= MI_TIMEFACTOR_100)
			{					 
				switch(cmd)
				{
					case MI_TIMEFACTOR_005:  Device.time_factor(0.05f); break;
					case MI_TIMEFACTOR_01:  Device.time_factor(0.1f); break;
					case MI_TIMEFACTOR_02:  Device.time_factor(0.2f); break;
					case MI_TIMEFACTOR_03:  Device.time_factor(0.3f); break;
					case MI_TIMEFACTOR_05:  Device.time_factor(0.5f); break;
					case MI_TIMEFACTOR_10:  Device.time_factor(1.0f); break;
					case MI_TIMEFACTOR_30:  Device.time_factor(3.0f); break;
					case MI_TIMEFACTOR_50:  Device.time_factor(5.0f); break;
					case MI_TIMEFACTOR_100:  Device.time_factor(10.0f); break;
				};
			}
				
			UI->RedrawScene();
			DestroyOptionsMenu();
				
			return TRUE;
		}
		
		if(m->dwItemSpec == 1)
		{
			imLog.IsOpen() ? imLog.Close() : imLog.Open();
			UI->RedrawScene();
			return TRUE;
		}
		
		if(m->dwItemSpec == 2)
		{
			ExecCommand(COMMAND_BREAK_LAST_OPERATION);
			return TRUE;
		}
		
	}
	
	return FALSE;
}

void SB_Initialize(HWND parent)
{
	InitCommonControls();
	hSB = CreateStatusWindow(WS_CHILD|WS_VISIBLE, "StatusBar", parent, STATUSBAR_ID);
	
	UpdateParts();
	
	SendMessage(hSB, SB_SETTEXT, (WPARAM)0, (LPARAM)"Options");
	SendMessage(hSB, SB_SETTEXT, (WPARAM)1, (LPARAM)"Log");
	SendMessage(hSB, SB_SETTEXT, (WPARAM)2, (LPARAM)"Break");
	SendMessage(hSB, SB_SETTEXT, (WPARAM)3|SBT_OWNERDRAW, (LPARAM)"Status");
}

BOOL SB_SetStatus(LPCSTR text)
{
	if(status != text)
	{
		status = text;
		return TRUE;
	}
	else
		return FALSE;
}

void SB_SetInfo(int n, LPCSTR text)
{
	if(n < 0 || n >= 4)
		return;
		
	SendMessage(hSB, SB_SETTEXT, (WPARAM)n+4, (LPARAM)text);
}

void SB_DrawProgress(void)
{
	RECT r;
	SendMessage(hSB, SB_GETRECT, 3, (LPARAM)&r);
	RedrawWindow(hSB, &r, NULL, RDW_INVALIDATE|RDW_UPDATENOW);
}

BOOL SB_ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_SIZE:
			SendMessage(hSB, WM_SIZE, wParam, lParam);
			UpdateParts();
			
			// вернём FALSE чтобы родительское окно тоже обработало это сообщение
			return FALSE;
			
		case WM_NOTIFY:
			if(wParam == STATUSBAR_ID)
			{
				return SB_Notify(wParam, lParam);
			}
		break;
		
		case WM_DRAWITEM:
			if(wParam == STATUSBAR_ID)
			{
				PDRAWITEMSTRUCT s = (LPDRAWITEMSTRUCT)lParam;
				RECT &r = s->rcItem;
				
				SPBItem* pbi 	= UI->ProgressLast();
				if(!pbi)
				{
					DrawStatusText(s->hDC, &r, status.c_str(), 0);
					return TRUE;
				}
				
				AnsiString 	txt;
				float 		p,m;
				pbi->GetInfo(txt,p,m);
				
				DrawStatusText(s->hDC, &r, txt.c_str(), 0);
				
				// draw progress bar
				RECT r2 = r;
				r2.left = r.right-250;
				
				Rectangle(s->hDC, r2.left, r2.top, r2.right, r2.bottom);
				
				// shrink rect a bit
				RECT r3 = r2;
				r3.left++; r3.top++; r3.right--; r3.bottom--;
				
				// set progress
				float progress = fis_zero(m) ? 0.0f : p/m;
				r3.right = r3.left + (r3.right-r3.left) * progress;
				
				HBRUSH hBrush = CreateSolidBrush(RGB(0,192,0));
				FillRect(s->hDC, &r3, hBrush);
				DeleteObject(hBrush);
				
				// draw percentage text
				char str[64];
				sprintf(str, "%d %%", (int)(progress*100));
				
				SetBkMode(s->hDC, TRANSPARENT);
				
				SetTextColor(s->hDC, RGB(0,0,0));
				DrawTextEx(s->hDC, str, -1, &r2, DT_SINGLELINE|DT_VCENTER|DT_CENTER, NULL);
				
				HRGN clipRgn = CreateRectRgnIndirect(&r3);
				SelectClipRgn(s->hDC, clipRgn);
				
				SetTextColor(s->hDC, RGB(255,255,255));
				DrawTextEx(s->hDC, str, -1, &r2, DT_SINGLELINE|DT_VCENTER|DT_CENTER, NULL);
				
				SelectClipRgn(s->hDC, NULL);
				DeleteObject(clipRgn);
				
				SetBkMode(s->hDC, OPAQUE);
				SetTextColor(s->hDC, RGB(0,0,0));
				
				return TRUE;
			}
		break;
	}
	
	return FALSE;
}
