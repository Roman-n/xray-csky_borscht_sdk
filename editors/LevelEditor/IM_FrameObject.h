#ifndef IM_FRAME_OBJECT_H
#define IM_FRAME_OBJECT_H

#include "..\ECore\ImGui\IM_Window.h"
#include "..\ECore\ImGui\IM_Tree.h"

class IM_FrameObject : public IM_Window
{
	public:
    IM_Tree objects_tree;

	public:
    void RefreshList();
    virtual void Render();
};

#endif
 