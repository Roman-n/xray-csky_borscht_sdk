//---------------------------------------------------------------------------

#ifndef ObjectListH
#define ObjectListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "CSPIN.h"
#include "ElTree.hpp"
#include "ElXPThemedControl.hpp"
#include "ExtBtn.hpp"
#include <ImgList.hpp>

#include "mxPlacemnt.hpp"
#include "ESceneClassList.h"
#include "ElEdits.hpp"
#include "ElTreeInplaceEditors.hpp"

//---------------------------------------------------------------------------
class TfrmObjectList : public TForm
{
__published:	// IDE-managed Components
	TPanel *paOptions;
	TRadioGroup *rgSO;
	TExtBtn *ebShowSel;
	TExtBtn *ebHideSel;
	TFormStorage *fsStorage;
	TPanel *paBottom;
	TExtBtn *sbRefreshList;
	TExtBtn *sbClose;
	TExtBtn *ebShowProperties;
	TPanel *paItems;
	TElTree *tvItems;
	TPanel *paSearch;
	TElEdit *ElEdit1;
	TRadioGroup *rgTools;
    void __fastcall         sbCloseClick		(TObject *Sender);
    void __fastcall         FormShow			(TObject *Sender);
    void __fastcall         ebHideSelClick		(TObject *Sender);
    void __fastcall         ebShowSelClick		(TObject *Sender);
    void __fastcall         sbRefreshListClick	(TObject *Sender);
    void __fastcall         tmRefreshListTimer	(TObject *Sender);
    void __fastcall         FormClose			(TObject *Sender, TCloseAction &Action);
    void __fastcall         FormKeyDown			(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall         rgSOClick			(TObject *Sender);
	void __fastcall         tvItemsKeyPress		(TObject *Sender, char &Key);
	void __fastcall         tvItemsItemFocused	(TObject *Sender);
	void __fastcall         tvItemsAfterSelectionChange(TObject *Sender);
	void __fastcall         ebShowPropertiesClick(TObject *Sender);
	void __fastcall         tvItemsDblClick		(TObject *Sender);
	void __fastcall ElEdit1Change(TObject *Sender);
	void __fastcall ElEdit1Exit(TObject *Sender);
	void __fastcall ElEdit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall rgToolsClick(TObject *Sender);
private:	// User declarations
    int 					obj_count;
	ObjClassID 				m_cur_cls;
	bool					m_bAllTools;
    void __fastcall 		InitListBox			();
    TElTreeItem* 			FindObjectByType	(int type, void *obj);
    TElTreeItem* 			FindFolderByType	(int type);
    TElTreeItem* 			AddFolder			(LPCSTR name, void* data, TElTreeItem* parent_node);
    TElTreeItem* 			AddObject			(TElTreeItem* node, LPCSTR name, void* obj, TColor color);
    void 					UpdateState			();
    void 					UpdateSelection		();
    bool 					bLockUpdate;
    TElTreeItem* 			find_node;
    bool 					stored_parent_colors;
	TColor					stored_bk_color;
	TColor					stored_row_color;
    void					ProcessFindItemInList(TElTreeItem* from, AnsiString str);

    struct SFolderStore{
    	bool expanded;
    };
    DEFINE_MAP				(AnsiString,SFolderStore,FolderStoreMap,FolderStorePairIt);
    FolderStoreMap			ItemsStore;

	void					storeExpandedItems();
    void					restoreExpandedItems();    
public:		// User declarations
    __fastcall 				TfrmObjectList		(TComponent* Owner);
	static TfrmObjectList* 	CreateForm			(TWinControl* parent=0);
	static void 			DestroyForm			(TfrmObjectList*& obj_list);
    void __fastcall 		ShowObjectListModal	();
    void __fastcall 		ShowObjectList		(bool bSearch = false);
	void __fastcall 		HideObjectList		();
	void __fastcall 		UpdateObjectList	();
};
//---------------------------------------------------------------------------
extern void frmObjectListShow();
//---------------------------------------------------------------------------
#endif
