#include "stdafx.h"
#pragma hdrstop

#include "AppendObjectInfoForm.h"
#include "CustomObject.h"

#ifndef NO_VCL

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TfrmAppendObjectInfo* 		g_frmConflictLoadObject = NULL;
//---------------------------------------------------------------------------
__fastcall TfrmAppendObjectInfo::TfrmAppendObjectInfo(TComponent* Owner)
	: TForm(Owner)
{
	m_result 					= 4;//auto-rename all
}

void TfrmAppendObjectInfo::Prepare()
{
    StaticText2->Caption 		= m_existing_object->Name;
}    

void __fastcall TfrmAppendObjectInfo::btOverwriteClick(TObject *Sender)
{
	TButton* bt = (TButton*)Sender;
	m_result = bt->Tag;
    if(CheckBox1->Checked)
		m_result	+= 1;
            
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

#else // NO_VCL

TfrmAppendObjectInfo* g_frmConflictLoadObject = NULL;

INT_PTR TfrmAppendObjectInfo_DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_INITDIALOG)
    {
        SetDlgItemText(hWnd, 105, g_frmConflictLoadObject->m_existing_object->GetName());
    }
    
    if(msg == WM_COMMAND)
    {
        BOOL dontAskAgain = IsDlgButtonChecked(hWnd, 103);
         
        if(wParam == 100) // Overwrite
        {
        	g_frmConflictLoadObject->m_result = 1;
        	EndDialog(hWnd, 0);
        }
        
        if(wParam == 101) // Auto rename
        {
        	g_frmConflictLoadObject->m_result = 3;
        	EndDialog(hWnd, 0);
        }
        
        if(wParam == 102) // Skip
        {
        	g_frmConflictLoadObject->m_result = 5;
        	EndDialog(hWnd, 0);
        }
        
        if(dontAskAgain)
            g_frmConflictLoadObject->m_result++;
    }

    return NULL;
}

void TfrmAppendObjectInfo::ShowModal()
{
    extern HWND g_MainWnd;
    DialogBox(NULL, "DIALOG_ALREADYEXIST", g_MainWnd, TfrmAppendObjectInfo_DlgProc);
} 

void TfrmAppendObjectInfo::Prepare()
{
} 

#endif

