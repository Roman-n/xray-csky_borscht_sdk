#ifndef IM_PropertyTreeH
#define IM_PropertyTreeH

#include "IM_Window.h"
#include "../../xrEProps/xrEProps.h"
#include "../../xrEProps/PropertiesListTypes.h"

namespace Eltree
{
	class TElTreeItem;
}

ECORE_API class IM_PropertyTree : public IM_Window
{
	private:
	char separator;
    bool multiselect;
    bool bullets;

	struct ImTreeNode
    {
		xr_map<xr_string,ImTreeNode> * child;
        bool selected;

        PropItem* item;

        ImTreeNode()
        	: child(NULL),
              selected(false),
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

    shared_str		editing_node;

    ImTreeNode*		GetNode(LPCSTR path, bool must_exist);
    void 			RenderNode(ImTreeNode &node);
    void 			ClearNode(ImTreeNode &node) { node.~ImTreeNode(); }
    void			SelectNode(ImTreeNode &node, bool select = true);

    void			RenderItem(ImTreeNode& node);

    public:
    IM_PropertyTree(char folder_separator = '\\', bool allow_multiselect = false, bool draw_bullets = true)
    	: separator(folder_separator),
          multiselect(allow_multiselect),
          bullets(draw_bullets),
          editing_node(NULL)
	{ }

    ~IM_PropertyTree()
    {
    }

    void			Add(LPCSTR path, PropItem* item);
    void 			Clear();

    void 			Select(LPCSTR path, bool select = true);
    void			SelectAll(bool select = true);
    PropItem* 		GetSelected();
    void 			GetSelected(PropItemVec &result); // for multiselect tree
    u32 			GetSelectedCount();

    // for compatibility with xrEProps property list
    typedef fastdelegate::FastDelegate1<Eltree::TElTreeItem*> TOnItemFocused;

    TOnItemFocused	OnItemFocused;
    TOnModifiedEvent OnModifiedEvent;

    void			AssignItems(PropItemVec& items, bool full_expand, bool full_sort = false);
    void			Modified();

    //
    void			RenderButton(PropItem* item);
    void			OpenChooseForm(PropItem* item);
    void			RenderNumeric(PropItem* item);
    void			RenderBoolean(PropItem* item);
    void 			RenderFlag(PropItem* item);
    void			RenderVector(PropItem* item);
	void			RenderToken(PropItem* item);
	void			RenderRToken(PropItem* item);
    void			RenderRList(PropItem* item);
    void			RenderCList(PropItem* item);
    void			RenderColor(PropItem* item);
    void			RenderFColor(PropItem* item);
    void			RenderVColor(PropItem* item);
    void			RenderRText(PropItem* item);
    void			RenderSText(PropItem* item);
    void			RenderCText(PropItem* item);
    void			RenderTime(PropItem* item);
    void			RenderGameType(PropItem* item);

    virtual void 	Render();
};

ECORE_API class IM_PropertiesWnd : public IM_Window
{
	public:
    xr_string m_caption;
    IM_PropertyTree m_props;
    bool m_open;
    bool m_modal;

    TOnCloseEvent m_close_event;

    public:
    IM_PropertiesWnd(const xr_string& caption, bool modal,
    TOnModifiedEvent on_modified = NULL, IM_PropertyTree::TOnItemFocused on_focused = NULL, TOnCloseEvent on_close = NULL,
    char folder_separator = '\\', bool allow_multiselect = false, bool draw_bullets = true);

    bool IsOpen();
    void Open();
    void Close();

    IM_PropertyTree& Props();
    void AssignItems(PropItemVec& items);

    virtual void Render();
};

#endif
