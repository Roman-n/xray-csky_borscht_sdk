#ifndef IM_FramePSH
#define IM_FramePSH

#include "../ECore/ImGui/IM_Window.h"
#include "../ECore/ImGui/IM_Tree.h"

class IM_FramePS : public IM_Window
{
	public:
    IM_Tree m_particles;
    bool m_initialized;

    public:
    IM_FramePS()
    	: m_initialized(false)
    {
    }

    LPCSTR Current();

    void SelectByRef(bool flag);
    void RefreshList();
    virtual void Render();
};

#endif
