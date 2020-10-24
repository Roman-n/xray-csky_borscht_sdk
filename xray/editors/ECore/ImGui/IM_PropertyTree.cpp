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
	PROP_SHORTCUT,  // yes
	PROP_BUTTON,    // yes
	PROP_CHOOSE,
	PROP_NUMERIC,   // yes
	PROP_BOOLEAN,   // yes
	PROP_FLAG,      // yes
	PROP_VECTOR,    // yes
	PROP_TOKEN,     // yes
	PROP_RTOKEN,    // yes
	PROP_RLIST,     // yes
	PROP_COLOR,     // yes
	PROP_FCOLOR,    // yes
	PROP_VCOLOR,    // yes
	PROP_RTEXT,     // yes
	PROP_STEXT,     // yes
	PROP_WAVE,
	PROP_CANVAS,    // yes
	PROP_TIME,      // yes

	PROP_CTEXT,     // yes
	PROP_CLIST,     // yes
	PROP_SH_TOKEN,
	PROP_TEXTURE2,
	PROP_GAMETYPE,  // yes
*/

IM_PropertyTree::ImTreeNode* IM_PropertyTree::GetNodeChild(ImTreeNode &node, const xr_string &name)
{
	if(node.child)
	{
		xr_list<ImTreeNode>::iterator it, end;
		for(it = node.child->begin(), end = node.child->end(); it != end; it++)
			if((*it).name == name)
				return &*it;
	}

	return NULL;
}

IM_PropertyTree::ImTreeNode* IM_PropertyTree::GetNode(LPCSTR path, bool must_exist)
{
	ImTreeNode *node = &root;
	int count = _GetItemCount(path, separator);

	for(int i = 0; i < count; i++)
	{
		char str[256];
		_GetItem(path, i, str, separator);

		if(must_exist)
		{
			node = GetNodeChild(*node, str);
			if(!node)
				return NULL;
		}
		else
		{
			if(!node->child)
				node->child = xr_new<xr_list<ImTreeNode> >();

			ImTreeNode *n = GetNodeChild(*node, str);
			if(!n)
			{
				node->child->push_back(ImTreeNode(str));
				node = &node->child->back();
			}
			else
				node = n;
		}
	}

	return node;
}

void IM_PropertyTree::RenderNode(ImTreeNode& node)
{
	if(!node.child)
		return;

	xr_list<ImTreeNode>::iterator it, end;
	for(it = node.child->begin(), end = node.child->end(); it != end; it++)
	{
		ImTreeNode& node = *it;
		bool clicked = false;

		//bool disabled = node.item ? node.item->m_Flags.is(PropItem::flDisabled) : false;

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 3));
		ImGui::Separator();
		ImGui::PopStyleVar(1);

		if(node.child) // folder
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

			if(full_expand)
				flags |= ImGuiTreeNodeFlags_DefaultOpen;
			if(node.selected)
				flags |= ImGuiTreeNodeFlags_Selected;

			//if(disabled)
			//	ImGui::PushStyleColor(ImGuiCol_Text,
			//	ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));

			ImGui::AlignTextToFramePadding();
			bool open = ImGui::TreeNodeEx(node.name.c_str(), flags);

			//if(disabled)
			//	ImGui::PopStyleColor();

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

			//if(disabled)
			//	ImGui::PushStyleColor(ImGuiCol_Text,
			//	ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));

			ImGui::AlignTextToFramePadding();
			if(bullets)
				ImGui::Bullet();
			ImGui::Selectable(node.name.c_str(), node.selected);

			//if(disabled)
			//	ImGui::PopStyleColor();

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

void IM_PropertyTree::RenderItem(ImTreeNode& node)
{
	PropItem* item = node.item;

	if(!item)
	{
		ImGui::AlignTextToFramePadding();
		ImGui::NewLine();

		return;
	}

	bool disabled = item->m_Flags.is(PropItem::flDisabled);

	if(disabled)
		ImGui::PushStyleColor(ImGuiCol_Text,
		ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));

	switch(item->Type())
	{
		case PROP_CAPTION:
		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted(GetDrawText(item).c_str());
		break;
		
		case PROP_SHORTCUT:
		if(editing_node == item->Key())
			RenderShortcut(item);
		else
			goto click2edit;
		break;

		case PROP_BUTTON:
		RenderButton(item);
		break;

		case PROP_CHOOSE:
		ImGui::Selectable(codepage2utf8(item->GetDrawText()).c_str(), false);
		if(ImGui::IsItemClicked(0) && ImGui::IsMouseDoubleClicked(0) && !disabled)
			OpenChooseForm(item);
		break;

		case PROP_NUMERIC:
		if(editing_node == item->Key())
			RenderNumeric(item);
		else
			goto click2edit;
		break;

		case PROP_BOOLEAN:
		RenderBoolean(item);
		break;

		case PROP_FLAG:
		RenderFlag(item);
		break;

		case PROP_VECTOR:
		if(editing_node == item->Key())
			RenderVector(item);
		else
			goto click2edit;
		break;

		case PROP_TOKEN:
		RenderToken(item);
		break;

		case PROP_RTOKEN:
		RenderRToken(item);
		break;

		case PROP_RLIST:
		RenderRList(item);
		break;

		case PROP_CLIST:
		RenderCList(item);
		break;

		case PROP_COLOR:
		RenderColor(item);
		break;

		case PROP_FCOLOR:
		RenderFColor(item);
		break;

		case PROP_VCOLOR:
		RenderVColor(item);
		break;

		case PROP_RTEXT:
		if(editing_node == item->Key())
			RenderRText(item);
		else
			goto click2edit;
		break;

		case PROP_STEXT:
		if(editing_node == item->Key())
			RenderSText(item);
		else
			goto click2edit;
		break;

		case PROP_CTEXT:
		if(editing_node == item->Key())
			RenderCText(item);
		else
			goto click2edit;
		break;

		case PROP_CANVAS:
		RenderCanvas(item, node.canvas);
		break;

		case PROP_TIME:
		RenderTime(item);
		break;

		case PROP_GAMETYPE:
		if(editing_node == item->Key())
			RenderGameType(item);
		else
			goto click2edit;
		break;

		default:
		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted(GetDrawText(item).c_str());
		break;

		click2edit:
		ImGui::AlignTextToFramePadding();
		ImGui::PushItemWidth(-1);
		ImGui::PushID(item);

		if(ImGui::Selectable(GetDrawText(item).c_str()))
			editing_node = node.item->Key();
		ImGui::PopID();

		break;
	}

	if(disabled)
		ImGui::PopStyleColor();
}

xr_string IM_PropertyTree::GetDrawText(PropItem* item)
{
	xr_string text = item->GetDrawText();
	size_t lf = text.find('\n');
	if(lf != xr_string::npos)
		text = text.substr(0,lf) + " ...";

	return codepage2utf8(text);
}

void IM_PropertyTree::Add(LPCSTR path, PropItem* item)
{
	ImTreeNode *node = GetNode(path, false);
	node->item = item;
}

void IM_PropertyTree::Clear()
{
	editing_node = NULL;
	modified = false;

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
	this->full_expand = true;//full_expand;

	Clear();

	for(PropItemIt it = items.begin(); it != items.end(); it++)
	{
		Add((*it)->Key(), *it);
	}
	
	if(full_sort)
		root.Sort();
}

void IM_PropertyTree::Modified()
{
	if(!OnModifiedEvent.empty())
		OnModifiedEvent();

	modified = true;
}

bool IM_PropertyTree::IsModified()
{
	return modified;
}

void IM_PropertyTree::RenderShortcut(PropItem* item)
{
	if(item->m_Flags.is(PropItem::flMixed))
	{
		ImGui::AlignTextToFramePadding();
		ImGui::TextUnformatted(item->GetDrawText().c_str());
		return;
	}
	
	ImGui::PushID(item);
	
	PropValue* V = item->GetFrontValue();
	ShortcutValue* v = dynamic_cast<ShortcutValue*>(V);
	
	u8 key = 0;
	ImGuiIO& io = ImGui::GetIO();
	for(int i = 0; i < 256; i++)
		if(io.KeysDown[i])
			key = i;
	
	char text[256] = "";
	if(io.KeyShift) strcat(text, "Shift + ");	
	if(io.KeyCtrl) strcat(text, "Ctrl + ");
	if(io.KeyAlt) strcat(text, "Alt + ");
	
	if(key != 0 && key != VK_CONTROL && key != VK_MENU && key != VK_SHIFT)
	{
		char key_name[64];
		GetKeyNameText(MapVirtualKey(key, 0) << 16, key_name, sizeof(key_name));
		strcat(text, key_name);
		
		xr_shortcut new_val;
		new_val.key = key;
		new_val.ext.set(xr_shortcut::flShift, io.KeyShift);
		new_val.ext.set(xr_shortcut::flCtrl, io.KeyCtrl);
		new_val.ext.set(xr_shortcut::flAlt, io.KeyAlt);
		
		if(item->AfterEdit<ShortcutValue,xr_shortcut>(new_val))
			if(item->ApplyValue<ShortcutValue,xr_shortcut>(new_val))
			{
				Modified();
				editing_node = NULL;
			}
	}
	
	if(!text[0])
		strcpy(text, item->GetDrawText().c_str());
	
	ImGui::Button(text);
	ImGui::SameLine();
	if(ImGui::Button("Reset"))
	{
		xr_shortcut empty;
		if(item->AfterEdit<ShortcutValue,xr_shortcut>(empty))
			if(item->ApplyValue<ShortcutValue,xr_shortcut>(empty))
			{
				Modified();
				editing_node = NULL;
			}
	}
	
	ImGui::PopID();
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

		bool disabled = item->m_Flags.is(PropItem::flDisabled);

		if(clicked_id != -1 && !disabled)
		{
			PropItem::PropValueVec& values = item->Values();
			for(PropItem::PropValueIt it = values.begin(); it != values.end(); it++)
			{
				ButtonValue* V = dynamic_cast<ButtonValue*>(*it);
				VERIFY(V);

				V->btn_num = clicked_id;
				bool dummy = false;
				if(V->OnBtnClick(dummy)) // what does parameter mean ???
					Modified();

				if(V->m_Flags.is(ButtonValue::flFirstOnly))
					break;
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

	IM_ChooseForm* cf = xr_new<IM_ChooseForm>(
		EChooseMode(V->m_ChooseID), V->subitem,
		V->m_Items, TOnChooseFillItems(NULL), V->m_FillParam
	);

	cf->OnOK = IM_CFCallback(cd, &ChooseDelegate::OnOK);
	cf->OnClose = IM_CFCallback(cd, &ChooseDelegate::OnClose);

	shared_str val = V->GetValue();
	item->BeforeEdit<ChooseValue,shared_str>(val);
	cf->SetSelected(val);
	
	if(cf->GetSelected().equal(""))
		cf->SetSelected(V->m_StartPath);

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

	bool disabled = item->m_Flags.is(PropItem::flDisabled);

	ImGui::PushID(item->Key());
	if(fv)
	{
		float val = fv->GetValue();
		item->BeforeEdit<FloatValue,float>(val);

		if(ImGui::InputFloat("", &val) && !disabled)
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

		if(ImGui::InputInt("", &val) && !disabled)
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

	bool disabled = item->m_Flags.is(PropItem::flDisabled);

	ImGui::PushID(item->Key());
	if(ImGui::Checkbox("", &value) && !disabled)
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

	bool value, have_caption;
	if(f8) {
		Flags8 f = f8->GetValue();
		item->BeforeEdit<Flag8Value,Flags8>(f);
		value = f.is(f8->mask);
		have_caption = f8->HaveCaption();
	} else if(f16) {
		Flags16 f = f16->GetValue();
		item->BeforeEdit<Flag16Value,Flags16>(f);
		value = f.is(f16->mask);
		have_caption = f16->HaveCaption();
	} else if(f32) {
		Flags32 f = f32->GetValue();
		item->BeforeEdit<Flag32Value,Flags32>(f);
		value = f.is(f32->mask);
		have_caption = f32->HaveCaption();
	}

	bool modified;
	ImGui::PushID(item->Key());
	if(have_caption)
	{
		if(ImGui::Selectable(item->GetDrawText().c_str(), false))
		{
			value = !value;
			modified = true;
		}
	}
	else
		modified = ImGui::Checkbox("", &value);

	bool disabled = item->m_Flags.is(PropItem::flDisabled);

	if(modified && !disabled)
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

	bool disabled = item->m_Flags.is(PropItem::flDisabled);

	if(updated && !disabled)
	{
		if(item->AfterEdit<VectorValue,Fvector>(vec))
			if(item->ApplyValue<VectorValue,Fvector>(vec));
	}
	ImGui::PopID();
}

void IM_PropertyTree::RenderToken(PropItem* item)
{
	// strange but with PushID(item->Key()) combobox doesn't open sometimes
	ImGui::PushID(item);//->Key());
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

		bool disabled = item->m_Flags.is(PropItem::flDisabled);

		xr_token* t = V->token;
		while(t->name)
		{
			if(ImGui::Selectable(t->name, t->id == (int)current) && !disabled)
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

void IM_PropertyTree::RenderRToken(PropItem* item)
{
	ImGui::PushID(item->Key());
	if(ImGui::BeginCombo("", item->GetDrawText().c_str()))
	{
		u32 current;

		RToken8Value* t8 = dynamic_cast<RToken8Value*>(item->GetFrontValue());
		RToken16Value* t16 = dynamic_cast<RToken16Value*>(item->GetFrontValue());
		RToken32Value* t32 = dynamic_cast<RToken32Value*>(item->GetFrontValue());
		VERIFY(t8 || t16 || t32);

		if(t8) {
			u8 value = t8->GetValue();
			item->BeforeEdit<RToken8Value,u8>(value);
			current = value;
		} else if(t16) {
			u16 value = t16->GetValue();
			item->BeforeEdit<RToken16Value,u16>(value);
			current = value;
		} else if(t32) {
			u32 value = t32->GetValue();
			item->BeforeEdit<RToken32Value,u32>(value);
			current = value;
		}

		RTokenValueCustom* V = dynamic_cast<RTokenValueCustom*>(item->GetFrontValue());
		VERIFY(V);

		bool disabled = item->m_Flags.is(PropItem::flDisabled);

		for(u32 i = 0; i < V->token_count; i++)
		{
			const xr_rtoken& t = V->token[i];
			if(ImGui::Selectable(*t.name, t.id == (int)current) && !disabled)
			{
				if(t8) {
					u8 newvalue = u8(t.id);
					if(item->AfterEdit<RToken8Value,u8>(newvalue))
						if(item->ApplyValue<RToken8Value,u8>(newvalue))
							Modified();
				} else if(t16) {
					u16 newvalue = u16(t.id);
					if(item->AfterEdit<RToken16Value,u16>(newvalue))
						if(item->ApplyValue<RToken16Value,u16>(newvalue))
							Modified();
				} else if(t32) {
					u32 newvalue = u32(t.id);
					if(item->AfterEdit<RToken32Value,u32>(newvalue))
						if(item->ApplyValue<RToken32Value,u32>(newvalue))
							Modified();
				}
			}
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

		bool disabled = item->m_Flags.is(PropItem::flDisabled);

		for(u32 i = 0; i < V->item_count; i++)
		{
			bool selected = current.equal(V->items[i]);
			if(ImGui::Selectable(V->items[i].c_str(), selected) && !disabled)
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

		xr_string current = V->GetValue();
		item->BeforeEdit<CListValue,xr_string>(current);

		bool disabled = item->m_Flags.is(PropItem::flDisabled);

		for(u32 i = 0; i < V->item_count; i++)
		{
			bool selected = V->items[i].compare(current); // isn't very fast, but CList used only in shader editor, so it's no problem
			if(ImGui::Selectable(V->items[i].c_str(), selected) && !disabled)
			{
				xr_string newval = V->items[i];
				if(V->items[i].length() > (size_t)V->lim)
					newval[V->lim] = '\0';

				if(item->AfterEdit<CListValue,xr_string>(newval))
					if(item->ApplyValue<CListValue,LPCSTR>(newval.c_str()))
						Modified();
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
	bool disabled = item->m_Flags.is(PropItem::flDisabled);
	if(ImGui::ColorEdit4("", (float*)&fclr) && !disabled)
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
	bool disabled = item->m_Flags.is(PropItem::flDisabled);
	if(ImGui::ColorEdit4("", (float*)&clr) && !disabled)
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
	bool disabled = item->m_Flags.is(PropItem::flDisabled);
	if(ImGui::ColorEdit3("", (float*)&clr) && !disabled)
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
	bool disabled;

	TextDelegate(IM_PropertyTree* _parent, PropItem* _item)
	: parent(_parent),
	  item(_item)
	{
		disabled = item->m_Flags.is(PropItem::flDisabled);
	}

	void RText_OK(IM_TextEditor* editor);
	void SText_OK(IM_TextEditor* editor);
	void CText_OK(IM_TextEditor* editor);

	void OnClose(IM_TextEditor*);
};

void TextDelegate::RText_OK(IM_TextEditor* editor)
{
	if(disabled)
		return;

	shared_str newvalue = editor->GetText().c_str();
	if(item->AfterEdit<RTextValue,shared_str>(newvalue))
		if(item->ApplyValue<RTextValue,shared_str>(newvalue))
			parent->Modified();
}

void TextDelegate::SText_OK(IM_TextEditor* editor)
{
	if(disabled)
		return;

	xr_string newvalue = editor->GetText();
	if(item->AfterEdit<STextValue,xr_string>(newvalue))
		if(item->ApplyValue<STextValue,xr_string>(newvalue))
			parent->Modified();
}

void TextDelegate::CText_OK(IM_TextEditor* editor)
{
	if(disabled)
		return;

	CTextValue* V = dynamic_cast<CTextValue*>(item->GetFrontValue());
	VERIFY(V);

	xr_string newvalue = editor->GetText().substr(0, V->lim);
	if(item->AfterEdit<CTextValue,xr_string>(newvalue))
		if(item->ApplyValue<CTextValue,LPCSTR>(newvalue.c_str()))
			parent->Modified();
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
	bool disabled = item->m_Flags.is(PropItem::flDisabled);
	if(ImGui::InputText("", &*text.begin(), text.size()) && !disabled)
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
	bool disabled = item->m_Flags.is(PropItem::flDisabled);
	if(ImGui::InputText("", &*text.begin(), text.size()) && !disabled)
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

	xr_string current = V->GetValue();
	item->BeforeEdit<CTextValue,xr_string>(current);

	size_t buf_size = V->lim + 1;
	xr_vector<char> text;
	text.resize(buf_size);
	strcpy(&*text.begin(), current.c_str());

	ImGui::PushID(item->Key());
	bool disabled = item->m_Flags.is(PropItem::flDisabled);
	if(ImGui::InputText("", &*text.begin(), text.size()) && !disabled)
	{
		xr_string newvalue = &*text.begin();
		if(item->AfterEdit<CTextValue,xr_string>(newvalue))
			if(item->ApplyValue<CTextValue,LPCSTR>(newvalue.c_str()))
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

void IM_PropertyTree::RenderCanvas(PropItem* item, IM_Canvas*& c)
{
	CanvasValue* V = dynamic_cast<CanvasValue*>(item->GetFrontValue());
	VERIFY(V);

	if(!c || c->Height() != V->height)
	{
		xr_delete(c);
		c = xr_new<IM_Canvas>(V->height*2, V->height);
	}

	TCanvas* cv = new TCanvas();
	cv->Handle = c->BeginPaint();

	V->OnDrawCanvasEvent(V, (void*)cv, Irect().set(0,0,c->Width(),c->Height()));

	c->EndPaint();
	delete cv;

	c->Render();
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
	char str[256];
	sprintf(str, "%02d:%02d:%02d", tc[0], tc[1], tc[2]);

	ImGui::PushID(item->Key());
	if(ImGui::InputText("", str, sizeof(str)))
	{
		if(sscanf(str, "%d:%d:%d", &tc[0], &tc[1], &tc[2]) == 3)
		{
			if(tc[0] >= 0 && tc[0] < 24 &&
			   tc[1] >= 0 && tc[1] < 60 &&
			   tc[2] >= 0 && tc[2] < 60)
				changed = true;
		}
	}
	ImGui::PopID();

	if(changed && !item->m_Flags.is(PropItem::flDisabled))
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

IM_PropertiesWnd::IM_PropertiesWnd(const xr_string& caption,
	TOnModifiedEvent on_modified, IM_PropertyTree::TOnItemFocused on_focused, TOnCloseEvent on_close,
	char folder_separator, bool allow_multiselect, bool draw_bullets)
	: Caption(caption),
	  Modal(false),
	  ShowButtonsBar(true),
	  OnClose(on_close),
	  m_props(folder_separator, allow_multiselect, draw_bullets),
	  m_open(false)
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
	
	if(!OnClose.empty())
		OnClose();
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
		
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	if(Modal)
	{
		static float width = ImGui::CalcTextSize("OK").x + ImGui::CalcTextSize("Cancel").x + ImGui::GetStyle().ItemSpacing.x
			+ ImGui::GetStyle().FramePadding.x * 5;
		static float height
			= ImGui::CalcTextSize("OK").y + ImGui::GetStyle().FramePadding.y * 2 + ImGui::GetStyle().ItemSpacing.y;
        
		ImGui::OpenPopup(Caption.c_str());
		if(ImGui::BeginPopupModal(Caption.c_str(), &m_open))
		{
			ImGui::BeginChild("ItemProps", ImVec2(0, ShowButtonsBar ? -height : 0), true);
			m_props.Render();
			ImGui::EndChild();
			
			if(ShowButtonsBar)
			{
				ImGui::Indent(ImGui::GetContentRegionAvailWidth() - width);
				if(ImGui::Button("OK"))
				{
					if(!OnOK.empty())
						OnOK();
                  
						m_open = false;
				}
          
				ImGui::SameLine();
				if(ImGui::Button("Cancel"))
				{
					if(!OnCancel.empty())
						OnCancel();
                  
					m_open = false;
				}
			}
			    
			ImGui::EndPopup();
		}
	}
	else
	{
		if(ImGui::Begin(Caption.c_str(), &m_open))
			m_props.Render();
      
		ImGui::End();
	}

	if(!m_open)
    Close();
}
