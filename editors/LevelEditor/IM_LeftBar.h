#ifndef IM_LEFTBAR_H
#define IM_LEFTBAR_H

#include "..\ECore\ImGui\IM_Window.h"
#include "IM_FrameObject.h"

class IM_LeftBar : public IM_Window
{
	public:
	IM_FrameObject fraObject;

    bool m_enable_snap_list;
    bool m_select_snap_objs_mode;

    bool m_show_scene;
    bool m_show_tools;
    bool m_show_editmode;
    bool m_show_snaplist;
    
	public:
    virtual void Render();
};

extern IM_LeftBar imLeftBar;

#endif
 