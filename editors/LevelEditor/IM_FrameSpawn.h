#ifndef IM_FrameSpawnH
#define IM_FrameSpawnH

#include "../ECore/ImGui/IM_Window.h"
#include "../ECore/ImGui/IM_Tree.h"

class IM_FrameSpawn : public IM_Window
{
	public:
    IM_Tree m_spawns;

    int m_select_percent;
    bool m_attach_object;

    public:
    IM_FrameSpawn()
    	: m_select_percent(0),
          m_attach_object(false)
    {
    }

    LPCSTR Current();
    void RefreshList();
    void MultiSelByRefObject(bool remove_current);
    void SelByRefObject(bool flag);
    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
