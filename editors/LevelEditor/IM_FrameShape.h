#ifndef IM_FrameShapeH
#define IM_FrameShapeH

#include "../ECore/ImGui/IM_Window.h"

class ESceneShapeTool;

class IM_FrameShape : public IM_Window
{
	public:
    ESceneShapeTool* m_parent_tool;

    bool m_append_box;
    bool m_append_sphere;

    bool m_attach_shape;

    bool m_edit_level_bound;

	public:
    IM_FrameShape()
    	: m_parent_tool(NULL),
          m_append_box(true),
          m_append_sphere(false),
          m_attach_shape(false),
          m_edit_level_bound(false)
    {
    }

    virtual void Render();
};

#endif
