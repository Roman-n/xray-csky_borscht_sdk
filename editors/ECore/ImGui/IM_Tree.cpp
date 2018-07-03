#include "stdafx.h"
#pragma hdrstop

#include "imgui.h"
#include "IM_Tree.h"

IM_Tree::ImTreeNode* IM_Tree::GetNode(LPCSTR path, bool must_exist)
{
	ImTreeNode *node = &root;
    int count = _GetItemCount(path, separator);

    for(int i = 0; i < count; i++)
    {
    	char str[256];
        _GetItem(path, i, str, separator);

        if(must_exist && (!node->child || node->child->find(str) == node->child->end()))
        	return NULL;
        if(!must_exist && !node->child)
        	node->child = xr_new<xr_map<xr_string,ImTreeNode> >();

        node = &(*node->child)[str];
    }

    return node;
}

void IM_Tree::RenderNode(ImTreeNode& node)
{
	if(!node.child)
		return;

    xr_map<xr_string, ImTreeNode>::iterator it, end;
    for(it = node.child->begin(), end = node.child->end(); it != end; it++)
    {
    	ImTreeNode& node = it->second;

    	if(node.child) // folder
        {
        	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

            if(node.selected)
            	flags |= ImGuiTreeNodeFlags_Selected;

        	bool open = ImGui::TreeNodeEx(it->first.c_str(), flags);

            if(ImGui::IsItemClicked())
            {
            	if(!multiselect || (multiselect && !ImGui::GetIO().KeyCtrl))
					SelectAll(false);
                    
            	SelectNode(node);
            }

            if(open)
            {
				RenderNode(node);
                ImGui::TreePop();
            }
        }
        else				 // file
        {
        	if(bullets)
            	ImGui::Bullet();
                
        	ImGui::Selectable(it->first.c_str(), node.selected);

            if(ImGui::IsItemClicked())
            {
				if(!multiselect || (multiselect && !ImGui::GetIO().KeyCtrl))
					SelectAll(false);

				SelectNode(node);

                if(node.item && !node.item->OnClickEvent.empty())
                	node.item->OnClickEvent(node.item);
            }
        }
    }
}

void IM_Tree::SelectNode(ImTreeNode& node, bool select)
{
	if(node.selected && !select)
	{
		selected.remove(&node);
		node.selected = false;
	}
	else if(!node.selected && select)
	{
		selected.push_back(&node);
		node.selected = true;

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

void IM_Tree::Add(LPCSTR path, LPCSTR value)
{
	ImTreeNode *node = GetNode(path, false);
    node->value = value;
}

void IM_Tree::Add(LPCSTR path, ListItem* item)
{
	ImTreeNode *node = GetNode(path, false);
    node->item = item;
}

void IM_Tree::Clear()
{
	ClearNode(root);
    selected.clear();
}

void IM_Tree::Select(LPCSTR path, bool select)
{
	ImTreeNode *node = GetNode(path, true);

    if(node)
    {
    	if(!multiselect)
        	SelectAll(false);

		SelectNode(*node);
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
    	xr_list<ImTreeNode*>::iterator it, end;
        for(it = selected.begin(), end = selected.end(); it != end; it++)
        	(*it)->selected = false;

        selected.clear();
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
	xr_list<ImTreeNode*>::iterator it, end;
    for(it = selected.begin(), end = selected.end(); it != end; it++)
    {
    	result.push_back((*it)->value);
    }
}

u32 IM_Tree::GetSelectedCount()
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

void IM_Tree::Render()
{
	RenderNode(root);
}


