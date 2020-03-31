//---------------------------------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include "FormCoord.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ExtBtn"
#pragma resource "*.dfm"
TfrmCoord *frmCoord;
//---------------------------------------------------------------------------
__fastcall TfrmCoord::TfrmCoord(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool TfrmCoord::Run(const char *caption, float &x, float &y, float &z)
{
	Caption = caption;
	edCoord->Text = AnsiString().sprintf("%f, %f, %f", x, y, z);

    if(ShowModal() == mrOk)
    {
    	x = X;
        y = Y;
        z = Z;
        return true;
    }
    else
    	return false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCoord::ebOkClick(TObject *Sender)
{
	if(sscanf(edCoord->Text.c_str(), "%f, %f, %f", &X, &Y, &Z) != 3)
    	MessageDlg("Invalid coordinates", mtError, TMsgDlgButtons() << mbOK, 0);
	else
    	ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfrmCoord::ebCancelClick(TObject *Sender)
{
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

