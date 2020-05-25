#ifndef IM_TopBarH
#define IM_TopBarH

#include "../ECore/ImGui/IM_Window.h"

class CTexture;

class IM_TopBar : public IM_Window
{
    public:
    CTexture* m_ui_texture;

    bool m_vertical;

    bool Button(int image_id, const char* tooltip = NULL, bool selected = false);
    void Separator();

    public:
    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

extern IM_TopBar imTopBar;

#endif
