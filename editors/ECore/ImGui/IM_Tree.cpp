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

void IM_Tree::RenderNode(ImTreeNode &node)
{
	if(!node.child)
		return;

    xr_map<xr_string, ImTreeNode>::iterator it, end;
    for(it = node.child->begin(), end = node.child->end(); it != end; it++)
    {
    	if(it->second.child) // folder
        {
        	if(ImGui::TreeNode(it->first.c_str()))
            {
				RenderNode(it->second);
                ImGui::TreePop();
            }
        }
        else				 // file
        {
        	ImGui::Selectable(it->first.c_str(), it->second.selected);

            if(ImGui::IsItemClicked())
            {
				if(!multiselect || (multiselect && !ImGui::GetIO().KeyCtrl))
					SelectAll(false);

				it->second.selected = true;
                selected.push_back(&it->second);
            }
        }
    }
}

void IM_Tree::Render()
{
	RenderNode(root);
}

void IM_Tree::Add(LPCSTR path, LPCSTR value)
{
	ImTreeNode *node = GetNode(path, false);
    node->value = value;
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

        if(node->selected && !select)
        {
        	selected.remove(node);
            node->selected = false;
        }
        else if(!node->selected && select)
        {
        	selected.push_back(node);
            node->selected = true;
        }
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


