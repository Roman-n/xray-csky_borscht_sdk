#ifndef IM_FramePSH
#define IM_FramePSH

#include "../ECore/ImGui/IM_Window.h"
#include "../ECore/ImGui/IM_Tree.h"

class IM_FramePS : public IM_Window
{
	public:
    IM_Tree m_particles;

    public:
    LPCSTR Current();

    void SelectByRef(bool flag);
    void RefreshList();
    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
