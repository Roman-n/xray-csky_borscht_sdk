#ifndef IM_FrameFogVolH
#define IM_FrameFogVolH

#include "../ECore/ImGui/IM_Window.h"

class ESceneFogVolumeTool;

class IM_FrameFogVol : public IM_Window
{
	public:
    ESceneFogVolumeTool *m_parent_tool;

    bool m_show_commands;

	public:
    IM_FrameFogVol()
    	: m_parent_tool(NULL),
          m_show_commands(true)
    {
    }

    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
