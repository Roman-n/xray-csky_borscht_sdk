//---------------------------------------------------------------------------
#ifndef ItemListHelperH
#define ItemListHelperH

#ifdef VCL
#include "FolderLib.h"
#endif
#include <xrServerEntities/ItemListTypes.h>

//---------------------------------------------------------------------------
class CListHelper: public IListHelper{
//------------------------------------------------------------------------------
public:
    virtual ListItem* 		__stdcall 	FindItem		(ListItemsVec& items,	LPCSTR key);
 	virtual bool 			__stdcall	NameAfterEdit	(ListItem* sender, LPCSTR value, shared_str& edit_val);
public:
	virtual ListItem*		__stdcall	CreateItem		(ListItemsVec& items, LPCSTR key, int type, u32 item_flags=0, void* object=0);
};
//---------------------------------------------------------------------------
#endif
