#ifndef IM_PropertyTreeH
#define IM_PropertyTreeH

#include "IM_Window.h"
#include "IM_Canvas.h"
#include <xrServerEntities/xrEProps.h>
#include <xrServerEntities/PropertiesListTypes.h>

namespace Eltree
{
	class TElTreeItem;
}

class ECORE_API IM_PropertyTree : public IM_Window
{
	private:
	char separator;
	bool multiselect;
	bool bullets;

	bool modified;

	struct ImTreeNode
	{
		xr_string name;
		xr_list<ImTreeNode> * child;
		bool selected;

		PropItem* item;
		IM_Canvas* canvas;

		ImTreeNode(const xr_string& node_name)
			: name(node_name),
			  child(NULL),
			  selected(false),
			  item(NULL),
			  canvas(NULL)
		{ }

		void Clear()
		{
			if(child)
				xr_delete(child);
			if(item)
				xr_delete(item);
			if(canvas)
				xr_delete(canvas);
		}

		~ImTreeNode()
		{
			Clear();
		}
		
		bool operator < (ImTreeNode& other)
		{
			return name < other.name;
		}
		
		void Sort()
		{
			if(child)
			{
				child->sort();
				for(xr_list<ImTreeNode>::iterator it = child->begin(); it != child->end(); it++)
					it->Sort();
			}
		}
	};

	ImTreeNode root;
	xr_list<ImTreeNode*> selected;

	shared_str		editing_node;
	bool          full_expand;

	ImTreeNode*		GetNodeChild(ImTreeNode &node, const xr_string& name);
	ImTreeNode*		GetNode(LPCSTR path, bool must_exist);
	void 			RenderNode(ImTreeNode &node);
	void 			ClearNode(ImTreeNode &node) { node.Clear(); }
	void			SelectNode(ImTreeNode &node, bool select = true);

	void			RenderItem(ImTreeNode& node);
	xr_string		GetDrawText(PropItem* item);

	public:
	IM_PropertyTree(char folder_separator = '\\', bool allow_multiselect = false, bool draw_bullets = true)
		: separator(folder_separator),
		  multiselect(allow_multiselect),
		  bullets(draw_bullets),
		  modified(false),
		  root(""),
		  editing_node(NULL)
	{ }

	~IM_PropertyTree()
	{
		Clear();
	}

	void			Add(LPCSTR path, PropItem* item);
	void 			Clear();

	void 			Select(LPCSTR path, bool select = true);
	void			SelectAll(bool select = true);
	PropItem* 		GetSelected();
	void 			GetSelected(PropItemVec &result); // for multiselect tree
	u32 			GetSelectedCount();

	// for compatibility with xrEProps property list
	typedef fastdelegate::FastDelegate<void(Eltree::TElTreeItem*)> TOnItemFocused;

	TOnItemFocused	OnItemFocused;
	TOnModifiedEvent OnModifiedEvent;

	void			AssignItems(PropItemVec& items, bool full_expand, bool full_sort = false);
	void			Modified();
	bool			IsModified();

	//
	void			RenderShortcut(PropItem* item);
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
	void			RenderCanvas(PropItem* item, IM_Canvas*& c);
	void			RenderTime(PropItem* item);
	void			RenderGameType(PropItem* item);

	virtual void 	Render();
};

class ECORE_API IM_PropertiesWnd : public IM_Window
{
	public:
	IM_PropertyTree m_props;
	bool m_open;
	
	xr_string Caption;
	bool Modal;
	bool ShowButtonsBar;

	TOnCloseEvent OnClose;
	TOnCloseEvent OnOK;
	TOnCloseEvent OnCancel;

	public:
	IM_PropertiesWnd(const xr_string& caption,
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
