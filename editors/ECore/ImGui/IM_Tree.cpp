#include "stdafx.h"
#pragma hdrstop

#include "IM_Tree.h"
#include "imgui.h"

IM_Tree::ImTreeNode* IM_Tree::GetNode(LPCSTR path, bool must_exist)
{
	ImTreeNode *node = &root;
	int count = _GetItemCount(path, separator);

	xr_string name = "";

    for(int i = 0; i < count; i++)
	{
		char str[256];
		_GetItem(path, i, str, separator);

		if(must_exist)
		{
			if(!node->child)
				return NULL;

			xr_map<xr_string, ImTreeNode>::iterator it = node->child->find(str);
			if(it == node->child->end())
				return NULL;

			node = &it->second;
		}
		else
		{
			if(!node->child)
				node->child = xr_new<xr_map<xr_string,ImTreeNode> >();

			if(i > 0) name += "\\";
			name += str;

			xr_map<xr_string, ImTreeNode>::iterator it = node->child->find(str);
			if(it == node->child->end())
			{
				node = &(*node->child)[str];
				node->name = name.c_str();
			}
			else
            	node = &it->second;
        }
    }

    return node;
}

void IM_Tree::RenderNode(ImTreeNode& parent)
{
	if(!parent.child)
		return;

	xr_map<xr_string, ImTreeNode>::iterator it, end;
	for(it = parent.child->begin(), end = parent.child->end(); it != end;)
	{
		ImTreeNode& node = it->second;
		bool remove = false;
		bool rename = false;

		if(node.item && !node.item->Visible())
		{
			it++;
			continue;
        }

		if(renaming == &node)
		{
			ImGui::PushID(*node.name);
			ImGui::InputText("", newname, sizeof(newname));
			ImGui::SameLine();
			bool ok = ImGui::Button("OK");
			ImGui::PopID();

			if(GetAsyncKeyState(VK_RETURN) & 0x8000 || ok)
			{
				if(parent.child->find(newname) == parent.child->end())
				{
					rename = true;
					renaming = NULL;
				}
				else
					ELog.Msg(mtError, "Item '%s' already exists", newname);
			}
		}
		else if(node.child) // folder
		{
        	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			if(node.selected)
            	flags |= ImGuiTreeNodeFlags_Selected;

			bool open = ImGui::TreeNodeEx(it->first.c_str(), flags);
 /*
            if(ImGui::IsItemClicked())
			{
            	if(!multiselect || (multiselect && !ImGui::GetIO().KeyCtrl))
					SelectAll(false);
                    
            	SelectNode(node);
            }
*/

			if(ImGui::BeginPopupContextItem())
			{
				ShowContextMenu(node, remove);
				ImGui::EndPopup();
			}

            if(open)
            {
				RenderNode(node);
                ImGui::TreePop();
            }
		}
        else				 // file
        {
        	if(DrawBullets)
            	ImGui::Bullet();

			bool clicked = false;
			if(CheckmarkMode)
				clicked = ImGui::MenuItem(it->first.c_str(), NULL, node.selected);
			else
				clicked = ImGui::Selectable(it->first.c_str(), node.selected);

			if(ImGui::BeginPopupContextItem())
			{
				ShowContextMenu(node, remove);
				ImGui::EndPopup();
			}

			if(DrawThumbnails && !OnDrawThumbnail.empty())
			{
				if(!node.canvas)
				{
					const int w = 150, h = 150;
					node.canvas = xr_new<IM_Canvas>(w, h);

					HDC hdc = node.canvas->BeginPaint();
					OnDrawThumbnail(*node.name, hdc, Irect().set(0,0,w,h));
					node.canvas->EndPaint();
				}
				node.canvas->Render();
				if(ImGui::IsItemClicked())
					clicked = true;
			}

			if(clicked)
            {
            	if(!CheckmarkMode)
                {
					if(!multiselect || (multiselect && !ImGui::GetIO().KeyCtrl))
						SelectAll(false);

                	if(MaxSelectedCount < 0 || GetSelectedCount() < MaxSelectedCount)
						SelectNode(node);
                }
                else
                {
					bool select = !node.selected;

                	if((select && (MaxSelectedCount < 0 || GetSelectedCount() < MaxSelectedCount)) || !select)
                    	SelectNode(node, select);
				}

                if(node.item && !node.item->OnClickEvent.empty())
                	node.item->OnClickEvent(node.item);
            }
		}

		if(remove)
		{
			xr_map<xr_string, ImTreeNode>::iterator rm = it;
			it++;
			parent.child->erase(rm);
		}
		else if(rename)
		{
			xr_string nm = it->first;
			it++;
			RenameNode(parent, nm.c_str(), newname);
        }
		else
        	it++;
    }
}

void IM_Tree::SelectNode(ImTreeNode& node, bool select)
{
	if(node.selected && !select)
	{
		selected.remove(&node);
		node.selected = false;

        if(!OnNodeSelected.empty())
			OnNodeSelected(node.name, node.value, select);

		if(renaming == &node)
		{
            renaming = NULL;
        }
	}
	else if(!node.selected && select)
	{
		selected.push_back(&node);
    	node.selected = true;

		// so much callbacks ...
		if(!OnNodeSelected.empty())
			OnNodeSelected(node.name, node.value, select);

		if(node.item && !node.item->OnItemFocused.empty())
			node.item->OnItemFocused(node.item);

		if(OnItemFocused)
			OnItemFocused(NULL);

		if(OnItemsFocused)
		{
			ListItemsVec vec;
			GetSelected(vec);
			OnItemsFocused(vec);
		}
	}
}

bool IM_Tree::RenameNode(ImTreeNode& parent, LPCSTR oldname, LPCSTR newname)
{
	if(!parent.child || parent.child->find(oldname) == parent.child->end())
		return false;
	if(parent.child->find(newname) != parent.child->end())
		return false; // already exists

	ImTreeNode& n = (*parent.child)[oldname];
	SelectNode(n, false);

	(*parent.child)[newname] = n;
	ImTreeNode& n2 = (*parent.child)[newname];

	xr_string oldpath = *n.name;
	xr_string newpath;
	size_t pos = oldpath.rfind('\\');
	if(pos != xr_string::npos)
		newpath = oldpath.substr(0, pos+1) + newname;
	else
		newpath = newname;

	n2.name = newname;
	if(n2.item)
		n2.item->SetName(n2.name.c_str());

	if(!OnItemRename.empty())
		OnItemRename(oldpath.c_str(), newpath.c_str(),
		n2.child ? TYPE_FOLDER : TYPE_OBJECT);

	n.ClearNotFree();
	parent.child->erase(oldname);

	SelectNode(n2, true);

	return true;
}

void IM_Tree::ShowContextMenu(ImTreeNode& node, bool& removed)
{
	if(!OnItemRename.empty() && ImGui::MenuItem("Rename"))
	{
		SelectAll(false);
		SelectNode(node, true);
		strcpy(newname, *node.name);
    	renaming = &node;
	}

	if(!OnItemRemove.empty() && ImGui::MenuItem("Remove"))
		OnItemRemove(*node.name, node.child ? TYPE_FOLDER : TYPE_OBJECT,
		removed);
}

void IM_Tree::GetItems(ImTreeNode &node, ListItemsVec &result)
{
	if(!node.child)
		return;

	xr_map<xr_string,ImTreeNode>::iterator it, end;
	for(it = node.child->begin(), end = node.child->end(); it != end; it++)
	{
		if(it->second.item)
			result.push_back(it->second.item);
		GetItems(it->second, result);
    }
}

void IM_Tree::Add(LPCSTR path, LPCSTR value)
{
	if(path == NULL) __asm int 3h;
	ImTreeNode *node = GetNode(path, false);
    node->name = path;
    node->value = value;
}

void IM_Tree::Add(LPCSTR path, ListItem* item)
{
	if(path == NULL) __asm int 3h;
	ImTreeNode *node = GetNode(path, false);
    node->name = path;
    node->item = item;
}

void IM_Tree::Clear()
{
	ClearNode(root);
	selected.clear();
	renaming = NULL;
}

void IM_Tree::Select(LPCSTR path, bool select)
{
	ImTreeNode *node = GetNode(path, true);

    if(node)
    {
    	if(!multiselect)
        	SelectAll(false);

        SelectNode(*node, select);
    }
}

void IM_Tree::SelectAll(bool select)
{
	if(select)
    {
    	if(!multiselect)
        	return;

        // todo
    }
    else
    {
    	xr_list<ImTreeNode*> sel = selected; // copy
    	xr_list<ImTreeNode*>::iterator it;
        for(it = sel.begin(); it != sel.end(); it++)
        	SelectNode(**it, false);
    }
}

shared_str IM_Tree::GetSelected()
{
	if(selected.size())
    	return selected.front()->value;
    else
    	return NULL;
}

void IM_Tree::GetSelected(xr_vector<shared_str> &result)
{
	xr_list<ImTreeNode*>::iterator it;
    for(it = selected.begin(); it != selected.end(); it++)
    {
    	result.push_back((*it)->value);
    }
}

shared_str IM_Tree::GetSelectedPath()
{
	if(selected.size())
    	return selected.front()->name;
    else
    	return NULL;
}

void IM_Tree::GetSelectedPaths(xr_vector<shared_str> &result)
{
	xr_list<ImTreeNode*>::iterator it;
    for(it = selected.begin(); it != selected.end(); it++)
    {
    	result.push_back((*it)->name);
    }
}

int IM_Tree::GetSelectedCount()
{
	return selected.size();
}

void IM_Tree::AssignItems(ListItemsVec& items, bool full_expand, bool full_sort)
{
	// unused
	(void)full_expand;
    (void)full_sort;

    Clear();

    ListItemsVec::iterator it, end;
    for(it = items.begin(); it != items.end(); it++)
    {
    	Add((*it)->Key(), *it);
    }
}

void IM_Tree::GetSelected(ListItemsVec& result)
{
	for(xr_list<ImTreeNode*>::iterator it = selected.begin(); it != selected.end(); it++)
		if((*it)->item)
			result.push_back((*it)->item);
}

void IM_Tree::GetItems(ListItemsVec& result)
{
    GetItems(root, result);
}

void IM_Tree::Render()
{
	RenderNode(root);
}


