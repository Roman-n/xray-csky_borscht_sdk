#ifndef IM_FrameDetailH
#define IM_FrameDetailH

#include "../ECore/ImGui/IM_Window.h"

class EDetailManager;

class IM_FrameDetail : public IM_Window
{
	public:
    EDetailManager* parent_tool;

	public:
    IM_FrameDetail()
    	: parent_tool(NULL)
    {
    }

    virtual void Render();
};

#endif
