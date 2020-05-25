#ifndef IM_FrameAIMapH
#define IM_FrameAIMapH

#include "../ECore/ImGui/IM_Window.h"

class ESceneAIMapTool;

class IM_FrameAIMap : public IM_Window
{
	public:
    ESceneAIMapTool* m_parent_tool;

    bool m_ignore_constraints;
    bool m_auto_link;

    bool m_link_add;
    bool m_link_del;
    bool m_link_invert;

    SStringVec m_ignored_materials;

	public:
    IM_FrameAIMap()
    	: m_parent_tool(NULL),
          m_ignore_constraints(false),
          m_auto_link(true),

          m_link_add(true),
          m_link_del(false),
          m_link_invert(false)
    {
    }

    void LoadCompilerErrors();
    void MakeLink(int side);

    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
