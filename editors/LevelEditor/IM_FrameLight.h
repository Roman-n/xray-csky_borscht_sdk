#ifndef IM_FrameLightH
#define IM_FrameLightH

#include "..\ECore\ImGui\IM_Window.h"

class IM_FrameLight : public IM_Window
{
	public:
    void UseInD3D(bool bAll, bool bFlag);

    public:
    virtual void Render();
};

#endif
