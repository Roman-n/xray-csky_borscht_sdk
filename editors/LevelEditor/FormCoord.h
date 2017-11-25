//---------------------------------------------------------------------------

#ifndef FormCoordH
#define FormCoordH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ExtBtn.hpp"
//---------------------------------------------------------------------------
class TfrmCoord : public TForm
{
__published:	// IDE-managed Components
	TEdit *edCoord;
	TExtBtn *ebCancel;
	TExtBtn *ebOk;
	void __fastcall ebOkClick(TObject *Sender);
	void __fastcall ebCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCoord(TComponent* Owner);

    bool Run(const char *caption, float &x, float &y, float &z);
    float X, Y, Z;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCoord *frmCoord;
//---------------------------------------------------------------------------
#endif
