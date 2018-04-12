#include "stdafx.h"
#pragma hdrstop

#include "FrameFogVol.h"
#include "ESceneFogVolumeTools.h"
#include "../ECore/Editor/ui_main.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ExtBtn"
#pragma resource "*.dfm"


//---------------------------------------------------------------------------
__fastcall TfraFogVol::TfraFogVol(TComponent* Owner, ESceneFogVolumeTool* gt)
	: TForm(Owner)
{
	ParentTools = gt;
}
//---------------------------------------------------------------------------

void __fastcall TfraFogVol::PaneMinClick(TObject *Sender)
{
    PanelMinMaxClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfraFogVol::ExpandClick(TObject *Sender)
{
    PanelMaximizeClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfraFogVol::ebGroupClick(TObject *Sender)
{
	ParentTools->GroupSelected();
}
//---------------------------------------------------------------------------
void __fastcall TfraFogVol::ebUngroupClick(TObject *Sender)
{
	ParentTools->UnGroupCurrent();
}
//---------------------------------------------------------------------------

