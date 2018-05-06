#ifndef IM_LEFTBAR_H
#define IM_LEFTBAR_H

#include "..\ECore\ImGui\IM_Window.h"
#include "IM_FrameObject.h"
#include "IM_FrameLight.h"
#include "IM_FrameFogVol.h"
#include "IM_FrameDetail.h"
#include "IM_FrameSector.h"
#include "IM_FramePortal.h"
#include "IM_FrameShape.h"
#include "IM_FramePS.h"
#include "IM_FrameWayPoint.h"
#include "IM_FrameSpawn.h"
#include "IM_FrameGroup.h"
#include "IM_FrameAIMap.h"

class IM_LeftBar : public IM_Window
{
	public:
	IM_FrameObject fraObject;
    IM_FrameLight fraLight;
    IM_FrameFogVol fraFogVol;
    IM_FrameDetail fraDetail;
    IM_FrameSector fraSector;
    IM_FramePortal fraPortal;
    IM_FrameShape fraShape;
    IM_FramePS fraPS;
    IM_FrameWayPoint fraWayPoint;
    IM_FrameSpawn fraSpawn;
    IM_FrameGroup fraGroup;
    IM_FrameAIMap fraAIMap;

    bool m_enable_snap_list;
    bool m_select_snap_objs_mode;

    bool m_show_scene;
    bool m_show_tools;
    bool m_show_editmode;
    bool m_show_snaplist;

    bool m_detach_main_menu;
    bool m_detach_tool_frame;

    xr_string m_title;

	public:
    IM_LeftBar()
    	: m_detach_tool_frame(false),
          m_detach_main_menu(false)
    {
    }

    virtual void OnAdd();
    virtual void OnRemove();

    virtual void Render();
    void RenderToolFrame();
    void RenderMainMenu();
    void RenderToolsMenu();
};

extern IM_LeftBar imLeftBar;

#endif
 