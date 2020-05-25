#ifndef IM_FrameLightH
#define IM_FrameLightH

#include "..\ECore\ImGui\IM_Window.h"

class IM_FrameLight : public IM_Window
{
	public:

    bool m_show_useind3d;

    void UseInD3D(bool bAll, bool bFlag);

    public:

    IM_FrameLight()
        : m_show_useind3d(true)
    {
    }

    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
