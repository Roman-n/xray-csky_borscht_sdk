#ifndef IM_TREE_H
#define IM_TREE_H

#include "IM_Window.h"
#include "../../xrEProps/xrEProps.h"
#include "../../xrEProps/ItemListTypes.h"

typedef fastdelegate::FastDelegate3<shared_str,shared_str,bool> IM_TOnNodeSelected;

ECORE_API class IM_Tree : public IM_Window
{
	private:
	char separator;
    bool multiselect;

	struct ImTreeNode
    {
		xr_map<xr_string,ImTreeNode> * child;
        bool selected;

        shared_str name;
        shared_str value;
        ListItem*  item;

        ImTreeNode()
        	: child(NULL),
              selected(false),
              name(NULL),
              value(NULL),
              item(NULL)
        { }

        ~ImTreeNode()
        {
        	if(child)
            	xr_delete(child);
            if(item)
            	xr_delete(item);
        }
    };

    ImTreeNode root;
    xr_list<ImTreeNode*> selected;

    ImTreeNode*		GetNode(LPCSTR path, bool must_exist);
    void 			RenderNode(ImTreeNode &node);
    void 			ClearNode(ImTreeNode &node) { node.~ImTreeNode(); }
    void			SelectNode(ImTreeNode &node, bool select = true);

    public: // properties

    bool DrawBullets;
    bool CheckmarkMode;
    int MaxSelectedCount;
    IM_TOnNodeSelected OnNodeSelected;

    public:
    IM_Tree(char folder_separator = '\\', bool allow_multiselect = false, bool draw_bullets = false)
    	: separator(folder_separator),
          multiselect(allow_multiselect),
          DrawBullets(draw_bullets),
          CheckmarkMode(false),
          MaxSelectedCount(-1)
	{ }

    ~IM_Tree()
    {
    }

    void 			Add(LPCSTR path, LPCSTR value);
    void			Add(LPCSTR path, ListItem* item);
    void 			Clear();

    void 			Select(LPCSTR path, bool select = true);
    void			SelectAll(bool select = true);

    shared_str 		GetSelected();
    void 			GetSelected(xr_vector<shared_str>& result); // for multiselect tree

    shared_str		GetSelectedPath();
    void			GetSelectedPaths(xr_vector<shared_str>& result);

    u32 			GetSelectedCount();

    // for compatibility with xrEProps item list
    TOnILItemsFocused 	OnItemsFocused;
    TOnILItemFocused 	OnItemFocused;

    void			AssignItems(ListItemsVec& items, bool full_expand, bool full_sort = false);
	void			GetSelected(ListItemsVec& result);

    virtual void 	Render();
};

#endif
 