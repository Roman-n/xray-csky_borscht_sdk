#ifndef IM_FRAME_OBJECT_H
#define IM_FRAME_OBJECT_H

#include "..\ECore\ImGui\IM_Window.h"
#include "..\ECore\ImGui\IM_Tree.h"

class ESceneObjectTool;

class IM_FrameObject : public IM_Window
{
	public:
    ESceneObjectTool* m_parent_tool;
    IM_Tree m_objects_tree;
	bool m_initialized;

    bool m_random_append;

    int m_select_percent;

	public:
    IM_FrameObject()
    	: m_parent_tool(NULL),
          m_initialized(false),
          m_random_append(false),
          m_select_percent(0)
    {
    }

    LPCSTR Current();

    void MultipleAppend();

    void MultiSelByRefObject(bool clear_prev);
    void SelByRefObject(bool flag);

    void RefreshList();
    virtual void Render();
};

#endif
 