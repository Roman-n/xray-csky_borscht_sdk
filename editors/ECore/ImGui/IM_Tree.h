#ifndef IM_TREE_H
#define IM_TREE_H

#include "IM_Window.h"

ECORE_API class IM_Tree : public IM_Window
{
	private:
	char separator;
    bool multiselect;

	struct ImTreeNode
    {
		xr_map<xr_string,ImTreeNode> * child;
		shared_str value;
        bool selected;

        ImTreeNode()
        	: child(NULL),
              value(NULL),
              selected(false)
        { }

        ~ImTreeNode()
        {
        	if(child)
            	xr_delete(child);
        }
    };

    ImTreeNode root;
    xr_list<ImTreeNode*> selected;

    ImTreeNode*		GetNode(LPCSTR path, bool must_exist);
    void 			RenderNode(ImTreeNode &node);
    void 			ClearNode(ImTreeNode &node) { if(node.child) xr_delete(node.child); }

    public:
    IM_Tree(char folder_separator = '\\', bool allow_multiselect = false)
    	: separator(folder_separator),
          multiselect(allow_multiselect)
	{ }

    ~IM_Tree()
    {
    }

    void 			Add(LPCSTR path, LPCSTR value);
    void 			Clear();

    void 			Select(LPCSTR path, bool select = true);
    void			SelectAll(bool select = true);
    shared_str 		GetSelected();
    void 			GetSelected(xr_vector<shared_str> &result); // for multiselect tree
    u32 			GetSelectedCount();

    virtual void 	Render();
};

#endif
 