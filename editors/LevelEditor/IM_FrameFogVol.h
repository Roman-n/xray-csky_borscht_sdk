#ifndef IM_FrameFogVolH
#define IM_FrameFogVolH

#include "../ECore/ImGui/IM_Window.h"

class ESceneFogVolumeTool;

class IM_FrameFogVol : public IM_Window
{
	public:
    ESceneFogVolumeTool *parent_tool;

	public:
    IM_FrameFogVol()
    	: parent_tool(NULL)
    {
    }

    virtual void Render();
};

#endif
