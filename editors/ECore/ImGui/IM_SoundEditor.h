#ifndef IM_SoundEditorH
#define IM_SoundEditorH

#include "IM_Window.h"
#include "IM_Tree.h"
#include "IM_PropertyTree.h"
#include "../Editor/EThumbnail.h"

class IM_SoundEditor : public IM_Window
{
	public:
	bool m_open;
	xr_string m_title;

	IM_Tree m_items;
	IM_PropertyTree m_props;

	DEFINE_VECTOR		(ESoundThumbnail*,THMVec,THMIt);
	THMVec				m_THM_Used;
	THMVec				m_THM_Current;

	enum
	{
    	flUpdateProperties 	= (1<<0),
        flReadOnly			= (1<<1),
	};
	Flags32 m_Flags;
	ref_sound m_Snd;
	FS_FileSet modif_map;

	BOOL bAutoPlay;

	public:
	IM_SoundEditor()
		: m_open(false),
		  m_title("Sound Editor"),
		  m_items('\\', true)
	{
		m_items.OnItemsFocused.bind(this, &IM_SoundEditor::OnItemsFocused);
		m_items.OnItemRemove.bind(this, &IM_SoundEditor::RemoveSound);
		m_items.OnItemRename.bind(this, &IM_SoundEditor::RenameSound);
	}

	void Open();
	void Close();

	virtual void OnRemove();
	virtual void Render();

	void 				InitItemsList();

	ESoundThumbnail*	FindUsedTHM			(LPCSTR name);
    void				SaveUsedTHM			();
    void				DestroyUsedTHM		();

	void				AppendModif			(LPCSTR nm);
	void 				RegisterModifiedTHM	();
	void				UpdateLib			();

	void __stdcall		OnItemsFocused		(ListItemsVec& items);
	void __stdcall  	OnControlClick		(ButtonValue* sender, bool& bModif, bool& bSafe);
	void __stdcall  	OnControl2Click		(ButtonValue* sender, bool& bModif, bool& bSafe);
	void __stdcall  	OnSyncCurrentClick	(ButtonValue* sender, bool& bModif, bool& bSafe);
	void __stdcall  	OnAttClick			(ButtonValue* sender, bool& bModif, bool& bSafe);
	void __stdcall  	OnAttenuationDraw	(CanvasValue* sender, void* _canvas, const Irect& _rect);

	void __stdcall 		RemoveSound			(LPCSTR fname, EItemType type, bool& res);
	void __stdcall 		RenameSound			(LPCSTR p0, LPCSTR p1, EItemType type);

	void				PlaySound			(LPCSTR name, u32& size, float& time);
};

extern ECORE_API IM_SoundEditor imSoundEditor;

#endif
