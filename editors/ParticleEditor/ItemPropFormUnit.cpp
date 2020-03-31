//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "ItemPropFormUnit.h"
#include "UI_ParticleMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "mxPlacemnt"
#pragma resource "*.dfm"
TfmItemProp *fmItemProp;
//---------------------------------------------------------------------------
__fastcall TfmItemProp::TfmItemProp(TComponent* Owner)
	: TForm(Owner)
{
	DEFINE_INI(fsStorage);
}
//---------------------------------------------------------------------------
void __fastcall TfmItemProp::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
	CanClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TfmItemProp::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caMinimize;
}
//---------------------------------------------------------------------------
