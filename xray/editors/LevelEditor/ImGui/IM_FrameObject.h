#ifndef IM_FRAME_OBJECT_H
#define IM_FRAME_OBJECT_H

#include "..\ECore\ImGui\IM_Window.h"
#include "..\ECore\ImGui\IM_Tree.h"

class ESceneObjectTool;
class IM_ChooseForm;

class IM_FrameObject : public IM_Window
{
	public:
    ESceneObjectTool* m_parent_tool;
    IM_Tree m_objects_tree;

    bool m_random_append;
    int m_select_percent;

    bool m_show_commands;
    bool m_show_refselect;
    bool m_show_currentobject;

	public:
    IM_FrameObject()
    	: m_parent_tool(NULL),
          m_random_append(false),
          m_select_percent(0),
          m_show_commands(true),
          m_show_refselect(true),
          m_show_currentobject(true)
	{
		m_objects_tree.MaxSelectedCount = 1;
		m_objects_tree.OnDrawThumbnail.bind(this, &IM_FrameObject::DrawThumbnail);
	}

    LPCSTR Current();

	void __stdcall MultipleAppend(IM_ChooseForm* form);
	void __stdcall SelectObject(IM_ChooseForm* form);
	void __stdcall DrawThumbnail(LPCSTR name, HDC hdc, const Irect& rect);

    void MultiSelByRefObject(bool clear_prev);
    void SelByRefObject(bool flag);

    void RefreshList();

    virtual void OnAdd();
    virtual void OnRemove();
    virtual void Render();
};

#endif
 