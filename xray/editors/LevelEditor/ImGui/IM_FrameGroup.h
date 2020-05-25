#ifndef IM_FrameGroupH
#define IM_FrameGroupH

#include "../ECore/ImGui/IM_Window.h"

class ESceneGroupTool;
class IM_ChooseForm;

class IM_FrameGroup : public IM_Window
{
	public:
    ESceneGroupTool *m_parent_tool;
    xr_string m_current;
    int m_select_percent;

	public:
    IM_FrameGroup()
    	: m_parent_tool(NULL),
          m_current(""),
          m_select_percent(0)
    {
    }

    void __stdcall OnGroupSelected(IM_ChooseForm* form);

    void MultiSelByRefObject(bool clear_prev);
    void SelByRefObject(bool flag);

    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
