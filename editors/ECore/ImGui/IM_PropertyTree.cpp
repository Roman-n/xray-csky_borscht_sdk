#include "stdafx.h"
#pragma hdrstop

#include "IM_PropertyTree.h"
#include "IM_TextEditor.h"
#include "IM_ChooseForm.h"
#include "imgui.h"
#include "utf8.h"
#include "../Editor/UI_Main.h"

#pragma package(smart_init)

/*
	PROP_UNDEF
	PROP_CAPTION    // yes
	PROP_SHORTCUT,
	PROP_BUTTON,    // yes
    PROP_CHOOSE,
	PROP_NUMERIC,   // yes
	PROP_BOOLEAN,   // yes
	PROP_FLAG,      // yes
    PROP_VECTOR,    // yes
	PROP_TOKEN,     // yes
	PROP_RTOKEN,
	PROP_RLIST,     // yes
	PROP_COLOR,     // yes
	PROP_FCOLOR,    // yes
	PROP_VCOLOR,    // yes
	PROP_RTEXT,     // yes
    PROP_STEXT,     // yes
	PROP_WAVE,
    PROP_CANVAS,
    PROP_TIME,

	PROP_CTEXT,     // yes
	PROP_CLIST,     // yes
    PROP_SH_TOKEN,
	PROP_TEXTURE2,
    PROP_GAMETYPE,  // yes
*/

IM_PropertyTree::ImTreeNode* IM_PropertyTree::GetNode(LPCSTR path, bool must_exist)
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

void IM_PropertyTree::RenderNode(ImTreeNode& node)
{
	if(!node.child)
		return;

    xr_map<xr_string, ImTreeNode>::iterator it, end;
    for(it = node.child->begin(), end = node.child->end(); it != end; it++)
    {
    	ImTreeNode& node = it->second;
        bool clicked = false;

    	if(node.child) // folder
        {
        	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

            if(node.selected)
            	flags |= ImGuiTreeNodeFlags_Selected;

            ImGui::AlignTextToFramePadding();
        	bool open = ImGui::TreeNodeEx(it->first.c_str(), flags);

            if(ImGui::IsItemClicked())
				clicked = true;

            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
	        RenderItem(node);
            ImGui::PopItemWidth();
        	ImGui::NextColumn();

            if(open)
            {
				RenderNode(node);
                ImGui::TreePop();
            }
        }
        else				 // file
        {
        	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

            if(node.selected)
            	flags |= ImGuiTreeNodeFlags_Selected;

            ImGui::AlignTextToFramePadding();
            if(bullets)
            	ImGui::Bullet();
			ImGui::Selectable(it->first.c_str(), node.selected);

            if(ImGui::IsItemClicked())
				clicked = true;

            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
	        RenderItem(node);
            ImGui::PopItemWidth();
        	ImGui::NextColumn();
        }

        if(clicked)
        {
        	if(!multiselect || (multiselect && !ImGui::GetIO().KeyCtrl))
				SelectAll(false);

			SelectNode(node);

        	if(node.item && !node.item->OnClickEvent.empty())
       			node.item->OnClickEvent(node.item);
        }
    }
}

void IM_PropertyTree::SelectNode(ImTreeNode& node, bool select)
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
	}
}

void IM_PropertyTree::RenderItem(ImTreeNode& node) //PropItem* item)
{
	PropItem* item = node.item;

	if(!item)
    {
    	ImGui::AlignTextToFramePadding();
        ImGui::NewLine();

        return;
    }

    switch(item->Type())
    {
    	case PROP_CAPTION:
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted(codepage2utf8(item->GetDrawText()).c_str());
        return;

    	case PROP_BUTTON:
        RenderButton(item);
        return;

        case PROP_CHOOSE:
        ImGui::Selectable(codepage2utf8(item->GetDrawText()).c_str(), false);
        if(ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
        	OpenChooseForm(item);
		return;

        case PROP_NUMERIC:
        if(editing_node == item->Key())
        	RenderNumeric(item);
        else
        	goto click2edit;
        return;

        case PROP_BOOLEAN:
        RenderBoolean(item);
        return;

        case PROP_FLAG:
		RenderFlag(item);
        return;

        case PROP_VECTOR:
        if(editing_node == item->Key())
        	RenderVector(item);
        else
        	goto click2edit;
		return;

        case PROP_TOKEN:
        RenderToken(item);
        return;

        case PROP_RLIST:
        RenderRList(item);
        return;

        case PROP_CLIST:
        RenderCList(item);
        return;

        case PROP_COLOR:
        RenderColor(item);
        return;

        case PROP_FCOLOR:
        RenderFColor(item);
        return;

        case PROP_VCOLOR:
        RenderVColor(item);
        return;

        case PROP_RTEXT:
        if(editing_node == item->Key())
        	RenderRText(item);
        else
        	goto click2edit;
        return;

        case PROP_STEXT:
        if(editing_node == item->Key())
        	RenderSText(item);
        else
        	goto click2edit;
        return;

        case PROP_CTEXT:
        if(editing_node == item->Key())
        	RenderCText(item);
        else
        	goto click2edit;
        return;

        case PROP_TIME:
        RenderTime(item);
        return;

        case PROP_GAMETYPE:
        if(editing_node == item->Key())
        	RenderGameType(item);
        else
        	goto click2edit;
        return;

    	default:
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted(codepage2utf8(item->GetDrawText()).c_str());
        return;

        click2edit:
        ImGui::AlignTextToFramePadding();
        ImGui::PushItemWidth(-1);
        ImGui::PushID(item);
        if(ImGui::Selectable(codepage2utf8(item->GetDrawText()).c_str()))
        	editing_node = node.item->Key();
        ImGui::PopID();

        return;
    }
}

void IM_PropertyTree::Add(LPCSTR path, PropItem* item)
{
	ImTreeNode *node = GetNode(path, false);
    node->item = item;
}

void IM_PropertyTree::Clear()
{
//	editing_node = NULL;

	ClearNode(root);
    selected.clear();
}

void IM_PropertyTree::Select(LPCSTR path, bool select)
{
	ImTreeNode *node = GetNode(path, true);

    if(node)
    {
    	if(!multiselect)
        	SelectAll(false);

		SelectNode(*node);
    }
}

void IM_PropertyTree::SelectAll(bool select)
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

PropItem* IM_PropertyTree::GetSelected()
{
	if(selected.size())
    	return selected.front()->item;
    else
    	return NULL;
}

void IM_PropertyTree::GetSelected(PropItemVec &result)
{
	xr_list<ImTreeNode*>::iterator it, end;
    for(it = selected.begin(), end = selected.end(); it != end; it++)
    {
    	if((*it)->item)
    		result.push_back((*it)->item);
    }
}

u32 IM_PropertyTree::GetSelectedCount()
{
	return selected.size();
}

void IM_PropertyTree::AssignItems(PropItemVec& items, bool full_expand, bool full_sort)
{
	// unused
	(void)full_expand;
    (void)full_sort;

    Clear();

    for(PropItemIt it = items.begin(); it != items.end(); it++)
    {
    	Add((*it)->Key(), *it);
    }
}

void IM_PropertyTree::Modified()
{
	if(!OnModifiedEvent.empty())
    	OnModifiedEvent();
}

void IM_PropertyTree::RenderButton(PropItem* item)
{
    if(!item->m_Flags.is(PropItem::flMixed))
    {
    	const xr_string& buttons = item->GetDrawText();
        u32 count = _GetItemCount(buttons.c_str(), ',');
        int clicked_id = -1;

        for(u32 i = 0; i < count ; i++)
        {
        	string256 button;
            _GetItem(buttons.c_str(), i, button, ',');

            if(i > 0) ImGui::SameLine();
            if(ImGui::Button(button))
            	clicked_id = i;
        }

        if(clicked_id != -1)
        {
        	PropItem::PropValueVec& values = item->Values();
        	for(PropItem::PropValueIt it = values.begin(); it != values.end(); it++)
        	{
        		ButtonValue* V = dynamic_cast<ButtonValue*>(*it);
        		VERIFY(V);

            	V->btn_num = clicked_id;
            	if(V->OnBtnClick(false)) // what does parameter mean ???
            		Modified();
        	}
		}
    }
    else
    {
    	ImGui::AlignTextToFramePadding();
    	ImGui::TextUnformatted(item->GetDrawText().c_str());
    }
}

class ChooseDelegate
{
	IM_PropertyTree* parent;
    PropItem* item;

    public:
    ChooseItemVec items;

	public:
    ChooseDelegate(IM_PropertyTree* props, PropItem* itm)
    	: parent(props),
          item(itm)
    {}

    void OnOK(IM_ChooseForm* form);
    void OnClose(IM_ChooseForm* form);
};

void ChooseDelegate::OnOK(IM_ChooseForm* form)
{
	shared_str res = form->GetSelected();
    if(item->AfterEdit<ChooseValue,shared_str>(res))
    	if(item->ApplyValue<ChooseValue,shared_str>(res))
        	parent->Modified();
}

void ChooseDelegate::OnClose(IM_ChooseForm*)
{
	ChooseDelegate* _this = const_cast<ChooseDelegate*>(this);
    xr_delete(_this);
}

void IM_PropertyTree::OpenChooseForm(PropItem* item)
{
	ChooseValue* V = dynamic_cast<ChooseValue*>(item->GetFrontValue());
	VERIFY(V);

	ChooseDelegate* cd = xr_new<ChooseDelegate>(this, item);
	if(!V->OnChooseFillEvent.empty())
	{
		V->m_Items = &cd->items;
		V->OnChooseFillEvent(V);
	}

	IM_ChooseForm* cf = new IM_ChooseForm( // xr_new
		EChooseMode(V->m_ChooseID), V->subitem,
		V->m_Items, TOnChooseFillItems(NULL), V->m_FillParam,
		IM_CFCallback(cd, &ChooseDelegate::OnOK), IM_CFCallback(NULL), IM_CFCallback(cd, &ChooseDelegate::OnClose)
	);

	shared_str val = V->GetValue();
	item->BeforeEdit<ChooseValue,shared_str>(val);
	cf->SetSelected(val);

	UI->AddIMWindow(cf);
}

void IM_PropertyTree::RenderNumeric(PropItem* item)
{
	PropValue*	V 		= item->GetFrontValue();
	U8Value*  	u8v		= dynamic_cast<U8Value*>(V);
    U16Value* 	u16v	= dynamic_cast<U16Value*>(V);
    U32Value* 	u32v	= dynamic_cast<U32Value*>(V);
    S8Value*  	s8v		= dynamic_cast<S8Value*>(V);
    S16Value* 	s16v	= dynamic_cast<S16Value*>(V);
    S32Value* 	s32v	= dynamic_cast<S32Value*>(V);
    FloatValue* fv		= dynamic_cast<FloatValue*>(V);

    VERIFY(u8v || u16v || u32v || s8v || s16v || s32v || fv);

    ImGui::PushID(item->Key());
    if(fv)
    {
    	float val = fv->GetValue();
        item->BeforeEdit<FloatValue,float>(val);

    	if(ImGui::InputFloat("", &val))
        	if(item->AfterEdit<FloatValue,float>(val))
            	if(item->ApplyValue<FloatValue,float>(val))
                	Modified();
    }
    else
    {
    	int val;
        if(u8v) {
        	u8 val8 = u8v->GetValue();
            item->BeforeEdit<U8Value,u8>(val8);
            val = int(val8);
        } else if(u16v) {
        	u16 val16 = u16v->GetValue();
            item->BeforeEdit<U16Value,u16>(val16);
            val = int(val16);
        } else if(u32v) {
        	u32 val32 = u32v->GetValue();
            item->BeforeEdit<U32Value,u32>(val32);
            val = int(val32); // sadly imgui doesn't support 64-bit integers
        } else if(s8v) {
        	s8 val8 = s8v->GetValue();
            item->BeforeEdit<S8Value,s8>(val8);
            val = int(val8);
        } else if(s16v) {
        	s16 val16 = s16v->GetValue();
            item->BeforeEdit<S16Value,s16>(val16);
            val = int(val16);
        } else if(s32v) {
        	s32 val32 = s32v->GetValue();
            item->BeforeEdit<S32Value,s32>(val32);
            val = int(val32);
        } else {
        	NODEFAULT;
        }

        if(ImGui::InputInt("", &val))
        {
        	if((u8v || u16v || u32v) && val < 0)
            	val = 0;

        	if(u8v) {
        		u8 val8 = u8(val);
				if(item->AfterEdit<U8Value,u8>(val8))
                	if(item->ApplyValue<U8Value,u8>(val8))
                    	Modified();
        	} else if(u16v) {
        		u16 val16 = u16(val);
				if(item->AfterEdit<U16Value,u16>(val16))
                	if(item->ApplyValue<U16Value,u16>(val16))
                    	Modified();
        	} else if(u32v) {
        		u32 val32 = u32(val);
				if(item->AfterEdit<U32Value,u32>(val32))
                	if(item->ApplyValue<U32Value,u32>(val32))
                    	Modified();
        	} else if(s8v) {
        		s8 val8 = s8(val);
				if(item->AfterEdit<S8Value,s8>(val8))
                	if(item->ApplyValue<S8Value,s8>(val8))
                    	Modified();
        	} else if(s16v) {
        		s16 val16 = s16(val);
				if(item->AfterEdit<S16Value,s16>(val16))
                	if(item->ApplyValue<S16Value,s16>(val16))
                    	Modified();
        	} else if(s32v) {
        		s32 val32 = s32(val);
				if(item->AfterEdit<S32Value,s32>(val32))
                	if(item->ApplyValue<S32Value,s32>(val32))
                    	Modified();
        	} else {
        		NODEFAULT;
        	}
        }
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderBoolean(PropItem* item)
{
	BOOLValue* V = dynamic_cast<BOOLValue*>(item->GetFrontValue());
    VERIFY(V);
    BOOL _value = V->GetValue();

	item->BeforeEdit<BOOLValue,BOOL>(_value);
    bool value = !!_value;

    ImGui::PushID(item->Key());
    if(ImGui::Checkbox("", &value))
    {
    	_value = value;
    	if(item->AfterEdit<BOOLValue,BOOL>(_value))
    		if(item->ApplyValue<BOOLValue,BOOL>((BOOL)value))
            	Modified();
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderFlag(PropItem* item)
{
    PropValue* V = item->GetFrontValue();
    Flag8Value* f8 = dynamic_cast<Flag8Value*>(V);
    Flag16Value* f16 = dynamic_cast<Flag16Value*>(V);
    Flag32Value* f32 = dynamic_cast<Flag32Value*>(V);
    VERIFY(f8 || f16 || f32);

    bool value;
    if(f8) {
    	Flags8 f = f8->GetValue();
		item->BeforeEdit<Flag8Value,Flags8>(f);
        value = f.is(f8->mask);
    } else if(f16) {
    	Flags16 f = f16->GetValue();
		item->BeforeEdit<Flag16Value,Flags16>(f);
        value = f.is(f16->mask);
    } else if(f32) {
    	Flags32 f = f32->GetValue();
		item->BeforeEdit<Flag32Value,Flags32>(f);
        value = f.is(f32->mask);
    }

    ImGui::PushID(item->Key());
    if(ImGui::Checkbox("", &value))
    {
    	if(f8) {
			Flags8 f; f.set(f8->mask, value);
			if(item->AfterEdit<Flag8Value,Flags8>(f))
            	if(item->ApplyValue<Flag8Value,Flags8>(f))
                	Modified();
    	} else if(f16) {
			Flags16 f; f.set(f16->mask, value);
			if(item->AfterEdit<Flag16Value,Flags16>(f))
            	if(item->ApplyValue<Flag16Value,Flags16>(f))
                	Modified();
        } else if(f32) {
			Flags32 f; f.set(f32->mask, value);
			if(item->AfterEdit<Flag32Value,Flags32>(f))
            	if(item->ApplyValue<Flag32Value,Flags32>(f))
                	Modified();
        }
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderVector(PropItem* item)
{
    VectorValue* V = dynamic_cast<VectorValue*>(item->GetFrontValue());
    VERIFY(V);

    Fvector vec = V->GetValue();
	item->BeforeEdit<VectorValue,Fvector>(vec);

    ImGui::PushID(item->Key());
    bool updated;
    if(ImGui::GetIO().KeyShift)
    	updated = ImGui::DragFloat3("", (float*)&vec, 0.1f, 0.0f, 0.0f, "%.3f", 1.0f);
    else
    	updated = ImGui::InputFloat3("", (float*)&vec, 4);

    if(updated)
    {
		if(item->AfterEdit<VectorValue,Fvector>(vec))
        	if(item->ApplyValue<VectorValue,Fvector>(vec));
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderToken(PropItem* item)
{
	ImGui::PushID(item->Key());
	if(ImGui::BeginCombo("", item->GetDrawText().c_str()))
    {
    	u32 current;

        Token8Value* t8 = dynamic_cast<Token8Value*>(item->GetFrontValue());
        Token16Value* t16 = dynamic_cast<Token16Value*>(item->GetFrontValue());
        Token32Value* t32 = dynamic_cast<Token32Value*>(item->GetFrontValue());
        VERIFY(t8 || t16 || t32);

        if(t8) {
        	u8 value = t8->GetValue();
            item->BeforeEdit<Token8Value,u8>(value);
            current = value;
        } else if(t16) {
        	u16 value = t16->GetValue();
            item->BeforeEdit<Token16Value,u16>(value);
            current = value;
        } else if(t32) {
        	u32 value = t32->GetValue();
            item->BeforeEdit<Token32Value,u32>(value);
            current = value;
        }

    	TokenValueCustom* V = dynamic_cast<TokenValueCustom*>(item->GetFrontValue());
        VERIFY(V);

        xr_token* t = V->token;
        while(t->name)
        {
            if(ImGui::Selectable(t->name, t->id == (int)current))
            {
            	if(t8) {
                	u8 newvalue = u8(t->id);
                    if(item->AfterEdit<Token8Value,u8>(newvalue))
                    	if(item->ApplyValue<Token8Value,u8>(newvalue))
                        	Modified();
                } else if(t16) {
                	u16 newvalue = u16(t->id);
                    if(item->AfterEdit<Token16Value,u16>(newvalue))
                    	if(item->ApplyValue<Token16Value,u16>(newvalue))
                        	Modified();
                } else if(t32) {
                	u32 newvalue = u32(t->id);
                    if(item->AfterEdit<Token32Value,u32>(newvalue))
                    	if(item->ApplyValue<Token32Value,u32>(newvalue))
                        	Modified();
                }
            }
        	t++;
        }

    	ImGui::EndCombo();
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderRList(PropItem* item)
{
	ImGui::PushID(item->Key());
    if(ImGui::BeginCombo("", item->GetDrawText().c_str()))
    {
    	RListValue* V = dynamic_cast<RListValue*>(item->GetFrontValue());
        VERIFY(V);

        shared_str current = V->GetValue();
        item->BeforeEdit<RListValue,shared_str>(current);

        for(u32 i = 0; i < V->item_count; i++)
        {
        	bool selected = current.equal(V->items[i]);
        	if(ImGui::Selectable(V->items[i].c_str(), selected))
            {
            	shared_str newval = V->items[i];
            	if(item->AfterEdit<RListValue,shared_str>(newval))
                	if(item->ApplyValue<RListValue,shared_str>(newval))
                    	Modified();
            }
        }

    	ImGui::EndCombo();
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderCList(PropItem* item)
{
	ImGui::PushID(item->Key());
    if(ImGui::BeginCombo("", item->GetDrawText().c_str()))
    {
    	CListValue* V = dynamic_cast<CListValue*>(item->GetFrontValue());
        VERIFY(V);

        LPSTR current = V->GetValue();
        item->BeforeEdit<CListValue,LPSTR>(current);

        for(u32 i = 0; i < V->item_count; i++)
        {
        	bool selected = V->items[i].compare(current); // isn't very fast, but CList used only in shader editor, so it's no problem
        	if(ImGui::Selectable(V->items[i].c_str(), selected))
            {
            	LPSTR newval = xr_strdup(V->items[i].c_str());
                if(V->items[i].length() > (size_t)V->lim)
                	newval[V->lim] = '\0';

            	if(item->AfterEdit<CListValue,LPSTR>(newval))
                	if(item->ApplyValue<CListValue,LPSTR>(newval))
                    	Modified();

                xr_free(newval);
            }
        }

    	ImGui::EndCombo();
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderColor(PropItem* item)
{
	U32Value* V = dynamic_cast<U32Value*>(item->GetFrontValue());
    VERIFY(V);

    u32 clr = V->GetValue();
    item->BeforeEdit<U32Value,u32>(clr);

    Fcolor fclr; fclr.set(clr);

    ImGui::PushID(item->Key());
    if(ImGui::ColorEdit4("", (float*)&fclr))
    {
    	clr = fclr.get();
    	if(item->AfterEdit<U32Value,u32>(clr))
        	if(item->ApplyValue<U32Value,u32>(clr))
            	Modified();
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderFColor(PropItem* item)
{
	ColorValue* V = dynamic_cast<ColorValue*>(item->GetFrontValue());
    VERIFY(V);

    Fcolor clr = V->GetValue();
    item->BeforeEdit<ColorValue,Fcolor>(clr);

    ImGui::PushID(item->Key());
    if(ImGui::ColorEdit4("", (float*)&clr))
    {
    	if(item->AfterEdit<ColorValue,Fcolor>(clr))
        	if(item->ApplyValue<ColorValue,Fcolor>(clr))
            	Modified();
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderVColor(PropItem* item)
{
	VectorValue* V = dynamic_cast<VectorValue*>(item->GetFrontValue());
    VERIFY(V);

    Fvector clr = V->GetValue();
    item->BeforeEdit<VectorValue,Fvector>(clr);

    ImGui::PushID(item->Key());
    if(ImGui::ColorEdit3("", (float*)&clr))
    {
    	if(item->AfterEdit<VectorValue,Fvector>(clr))
        	if(item->ApplyValue<VectorValue,Fvector>(clr))
            	Modified();
    }
    ImGui::PopID();
}

struct TextDelegate
{
	IM_PropertyTree* parent;
	PropItem* item;

	TextDelegate(IM_PropertyTree* _parent, PropItem* _item)
	: parent(_parent),
      item(_item)
	{}

	void RText_OK(IM_TextEditor* editor);
    void SText_OK(IM_TextEditor* editor);
    void CText_OK(IM_TextEditor* editor);

    void OnClose(IM_TextEditor*);
};

void TextDelegate::RText_OK(IM_TextEditor* editor)
{
	shared_str newvalue = editor->GetText().c_str();
    if(item->AfterEdit<RTextValue,shared_str>(newvalue))
    	if(item->ApplyValue<RTextValue,shared_str>(newvalue))
        	parent->Modified();
}

void TextDelegate::SText_OK(IM_TextEditor* editor)
{
	xr_string newvalue = editor->GetText();
    if(item->AfterEdit<STextValue,xr_string>(newvalue))
    	if(item->ApplyValue<STextValue,xr_string>(newvalue))
        	parent->Modified();
}

void TextDelegate::CText_OK(IM_TextEditor* editor)
{
	CTextValue* V = dynamic_cast<CTextValue*>(item->GetFrontValue());
    VERIFY(V);

    const xr_string& newvalue = editor->GetText();
	size_t length = _min((size_t)V->lim, newvalue.length());
    LPSTR str = xr_alloc<CHAR>(length+1);
    strncpy(str, newvalue.c_str(), length);
    str[length] = '\0';

    if(item->AfterEdit<CTextValue,LPCSTR>(str))
    	if(item->ApplyValue<CTextValue,LPCSTR>(str))
        	parent->Modified();

    xr_free(str);
}

void TextDelegate::OnClose(IM_TextEditor*)
{
	TextDelegate* _this = const_cast<TextDelegate*>(this);
	xr_delete(_this);
}

void IM_PropertyTree::RenderRText(PropItem* item)
{
	RTextValue* V = dynamic_cast<RTextValue*>(item->GetFrontValue());
    VERIFY(V);

    shared_str current = V->GetValue();
    item->BeforeEdit<RTextValue,shared_str>(current);

    if(current.equal(NULL))
    	current = "";

    xr_vector<char> text;
    text.resize(strlen(*current) + 1 + 4096);
    strcpy(&*text.begin(), *current);

    ImGui::PushID(item->Key());
    if(ImGui::InputText("", &*text.begin(), text.size()))
    {
    	shared_str newvalue = &*text.begin();
        if(item->AfterEdit<RTextValue,shared_str>(newvalue))
        	if(item->ApplyValue<RTextValue,shared_str>(newvalue))
            	Modified();
    }
    if(ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
    {
    	TextDelegate *d = xr_new<TextDelegate>(this, item);
        IM_TextEditor* e = xr_new<IM_TextEditor>(item->Key(), *current,
        	IM_TECallback(d, &TextDelegate::RText_OK),
            IM_TECallback(NULL),
            IM_TECallback(d, &TextDelegate::OnClose));

        UI->AddIMWindow(e);
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderSText(PropItem* item)
{
	STextValue* V = dynamic_cast<STextValue*>(item->GetFrontValue());
    VERIFY(V);

    xr_string current = V->GetValue();
    item->BeforeEdit<STextValue,xr_string>(current);

    xr_vector<char> text;
    text.resize(strlen(current.c_str()) + 1 + 4096);
    strcpy(&*text.begin(), current.c_str());

    ImGui::PushID(item->Key());
    if(ImGui::InputText("", &*text.begin(), text.size()))
    {
    	xr_string newvalue = &*text.begin();
        if(item->AfterEdit<STextValue,xr_string>(newvalue))
        	if(item->ApplyValue<STextValue,xr_string>(newvalue))
            	Modified();
    }
    if(ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
    {
    	TextDelegate *d = xr_new<TextDelegate>(this, item);
        IM_TextEditor* e = xr_new<IM_TextEditor>(item->Key(), current,
        	IM_TECallback(d, &TextDelegate::SText_OK),
            IM_TECallback(NULL),
            IM_TECallback(d, &TextDelegate::OnClose));

        UI->AddIMWindow(e);
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderCText(PropItem* item)
{
	CTextValue* V = dynamic_cast<CTextValue*>(item->GetFrontValue());
    VERIFY(V);

    LPSTR current = V->GetValue();
    item->BeforeEdit<CTextValue,LPSTR>(current);

    size_t buf_size = V->lim + 1;
    xr_vector<char> text;
    text.resize(buf_size);
    strcpy(&*text.begin(), current);

    ImGui::PushID(item->Key());
    if(ImGui::InputText("", &*text.begin(), text.size()))
    {
    	LPSTR newvalue = &*text.begin();
        if(item->AfterEdit<CTextValue,LPSTR>(newvalue))
        	if(item->ApplyValue<CTextValue,LPSTR>(newvalue))
            	Modified();
    }
    if(ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0))
    {
    	TextDelegate *d = xr_new<TextDelegate>(this, item);
        IM_TextEditor* e = xr_new<IM_TextEditor>(item->Key(), current,
        	IM_TECallback(d, &TextDelegate::CText_OK),
            IM_TECallback(NULL),
            IM_TECallback(d, &TextDelegate::OnClose));

        UI->AddIMWindow(e);
    }
    ImGui::PopID();
}

void IM_PropertyTree::RenderTime(PropItem* item)
{
	FloatValue* V = dynamic_cast<FloatValue*>(item->GetFrontValue());
	VERIFY(V);

	float ftime = V->GetValue();
    item->BeforeEdit<FloatValue,float>(ftime);

    u32 time = u32(ftime);

    int tc[3];

	tc[0] = time/(60*60);		// hours
	tc[1] = (time%(60*60))/60;	// minutes
	tc[2] = (time%(60*60))%60;	// seconds

	bool changed = false;

    ImGui::PushID(item->Key());
    if(ImGui::InputInt3("", tc))
    {
    	tc[0] = _min(tc[0], 23);
        tc[0] = _max(tc[0], 0);

    	tc[1] = _min(tc[1], 59);
        tc[1] = _max(tc[1], 0);

    	tc[2] = _min(tc[2], 59);
        tc[2] = _max(tc[2], 0);

        changed = true;
    }
    ImGui::PopID();

    if(changed)
    {
    	ftime = (tc[0]*(60*60))+(tc[1]*60)+tc[2];
        if(item->AfterEdit<FloatValue,float>(ftime))
        	if(item->ApplyValue<FloatValue,float>(ftime))
            	Modified();
    }
}

void IM_PropertyTree::RenderGameType(PropItem* item)
{
	GameTypeValue* V = dynamic_cast<GameTypeValue*>(item->GetFrontValue());
    VERIFY(V);

    GameTypeChooser gtc = V->GetValue();
    item->BeforeEdit<GameTypeValue,GameTypeChooser>(gtc);

    Flags16& flags = gtc.m_GameType;
    bool b;

    b = flags.test(eGameIDSingle);
    if(ImGui::Checkbox("Single", &b))
    	flags.set(eGameIDSingle, b);

    b = flags.test(eGameIDDeathmatch);
    if(ImGui::Checkbox("DM", &b))
    	flags.set(eGameIDDeathmatch, b);

    b = flags.test(eGameIDTeamDeathmatch);
    if(ImGui::Checkbox("TDM", &b))
    	flags.set(eGameIDTeamDeathmatch, b);

    b = flags.test(eGameIDArtefactHunt);
    if(ImGui::Checkbox("AH", &b))
    	flags.set(eGameIDArtefactHunt, b);

    b = flags.test(eGameIDCaptureTheArtefact);
    if(ImGui::Checkbox("CTA", &b))
    	flags.set(eGameIDCaptureTheArtefact, b);

    b = flags.test(eGameIDDominationZone);
    if(ImGui::Checkbox("DZ", &b))
    	flags.set(eGameIDDominationZone, b);
        
    b = flags.test(eGameIDTeamDominationZone);
    if(ImGui::Checkbox("TDZ", &b))
    	flags.set(eGameIDTeamDominationZone, b);

    if(item->AfterEdit<GameTypeValue,GameTypeChooser>(gtc))
    	if(item->ApplyValue<GameTypeValue,GameTypeChooser>(gtc))
        	Modified();
}

void IM_PropertyTree::Render()
{
	ImGui::Columns(2, NULL, true);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));

	RenderNode(root);

    ImGui::PopStyleVar();
    ImGui::Columns(1);
}

// **************************************************************************
// IM_PropertiesWnd
// **************************************************************************

IM_PropertiesWnd::IM_PropertiesWnd(const xr_string& caption, bool modal,
    TOnModifiedEvent on_modified, IM_PropertyTree::TOnItemFocused on_focused, TOnCloseEvent on_close,
    char folder_separator, bool allow_multiselect, bool draw_bullets)
    : m_caption(caption),
      m_close_event(on_close),
      m_props(folder_separator, allow_multiselect, draw_bullets),
      m_open(false),
      m_modal(modal)
{
	m_props.OnItemFocused = on_focused;
    m_props.OnModifiedEvent = on_modified;
}

bool IM_PropertiesWnd::IsOpen()
{
	return m_open;
}

void IM_PropertiesWnd::Open()
{
	m_open = true;
}

void IM_PropertiesWnd::Close()
{
	m_open = false;
    
    if(!m_close_event.empty())
    	m_close_event();
}

IM_PropertyTree& IM_PropertiesWnd::Props()
{
	return m_props;
}

void IM_PropertiesWnd::AssignItems(PropItemVec& items)
{
	m_props.AssignItems(items, false, false);
}

void IM_PropertiesWnd::Render()
{
	if(!m_open)
    	return;
        
    ImGui::SetWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

    if(m_modal)
    	ImGui::OpenPopup(m_caption.c_str());

    if(m_modal
       ? ImGui::BeginPopupModal(m_caption.c_str(), &m_open)
       : ImGui::Begin(m_caption.c_str(), &m_open))
    {
        m_props.Render();

        if(m_modal)
    		ImGui::EndPopup();
    }

    if(!m_open)
    	Close();

    if(!m_modal)
    	ImGui::End();
}
