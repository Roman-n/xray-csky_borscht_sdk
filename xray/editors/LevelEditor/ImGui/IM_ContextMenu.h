#ifndef IM_ContextMenuH
#define IM_ContextMenuH

#include "../ECore/ImGui/IM_Window.h"

class IM_ContextMenu : public IM_Window
{
    public:
    bool m_open;
    bool m_detach;
    
    IM_ContextMenu() : m_open(false), m_detach(false)
    {
    }
    
    public:
    virtual void Render();
    
    void Open();
    void ShowMenu();
};

extern IM_ContextMenu imContextMenu;

#endif
