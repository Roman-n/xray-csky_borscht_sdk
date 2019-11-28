#ifndef IM_TreeH
#define IM_TreeH

#include "IM_Window.h"
#include "IM_Canvas.h"
#include "../../xrEProps/xrEProps.h"
#include "../../xrEProps/ItemListTypes.h"

typedef fastdelegate::FastDelegate3<shared_str,shared_str,bool> IM_TOnNodeSelected;
typedef fastdelegate::FastDelegate3<LPCSTR,HDC,const Irect&> IM_TOnDrawThumbnail;

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

		IM_Canvas* canvas;

		ImTreeNode()
			: child(NULL),
              selected(false),
			  name(NULL),
			  value(NULL),
			  item(NULL),
			  canvas(NULL)
		{}

		void Clear()
		{
			if(child)
				xr_delete(child);
			if(item)
				xr_delete(item);
			if(canvas)
            	xr_delete(canvas);
		}

		void ClearNotFree()
		{
			child = NULL;
			item = NULL;
			canvas = NULL;
		}

		~ImTreeNode()
		{
			Clear();
        }
	};

	char newname[512];
	ImTreeNode* renaming;

    ImTreeNode root;
	xr_list<ImTreeNode*> selected;

    ImTreeNode*		GetNode(LPCSTR path, bool must_exist);
    void 			RenderNode(ImTreeNode &node);
	void 			ClearNode(ImTreeNode &node) { node.Clear(); }
	void			SelectNode(ImTreeNode &node, bool select = true);
	bool			RenameNode(ImTreeNode &parent, LPCSTR oldname, LPCSTR newname);

	void			ShowContextMenu(ImTreeNode& node, bool& removed);

	void			GetItems(ImTreeNode &node, ListItemsVec &result);

    public: // properties

    bool DrawBullets;
	bool CheckmarkMode;
	bool DrawThumbnails;
    int MaxSelectedCount;
	IM_TOnNodeSelected OnNodeSelected;
	IM_TOnDrawThumbnail OnDrawThumbnail;

    public:
    IM_Tree(char folder_separator = '\\', bool allow_multiselect = false, bool draw_bullets = false)
    	: separator(folder_separator),
		  multiselect(allow_multiselect),
		  renaming(NULL),
          DrawBullets(draw_bullets),
		  CheckmarkMode(false),
		  DrawThumbnails(false),
		  MaxSelectedCount(-1),
		  OnNodeSelected(NULL),
		  OnDrawThumbnail(NULL)
	{ }

    ~IM_Tree()
	{
		Clear();
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

	int 			GetSelectedCount();

	// for compatibility with xrEProps item list
	TOnILItemsFocused 	OnItemsFocused;
	TOnILItemFocused 	OnItemFocused;
	TOnItemRename		OnItemRename;
	TOnItemRemove		OnItemRemove;

	void			AssignItems(ListItemsVec& items, bool full_expand, bool full_sort = false);
	void			GetSelected(ListItemsVec& result);

	void			GetItems(ListItemsVec& result);

    virtual void 	Render();
};

#endif
 