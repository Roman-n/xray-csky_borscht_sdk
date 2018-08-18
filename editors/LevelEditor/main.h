//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>         
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "ExtBtn.hpp"
#include "MxMenus.hpp"
#include "mxPlacemnt.hpp"
#include "RenderWindow.hpp"
#include <ImgList.hpp>
//---------------------------------------------------------------------------
// refs

class ECORE_API TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TPanel *paLeftBar;
        TPanel *paBottomBar;
    TPanel *paTools;
    TTimer *tmRefresh;
	TFormStorage *fsStorage;
    TPanel *paMain;
    TPanel *paTopBar;
	TPanel *paRender;
	TLabel *APHeadLabel2;
	TExtBtn *sbToolsMin;
	TD3DWindow *D3DWindow;
	TExtBtn *ebAllMin;
	TExtBtn *ebAllMax;
	TSplitter *spLeftBar;
	TMainMenu *mmMainMenu;
	TMenuItem *miFile;
	TMenuItem *Edit1;
	TMenuItem *miOpen;
	TMenuItem *miSave;
	TMenuItem *miSaveAs;
	TMenuItem *miClear;
	TMenuItem *miQuit;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *miOpenSelection;
	TMenuItem *miSaveSelection;
	TMenuItem *N3;
	TMenuItem *miMakePack;
	TMenuItem *miUndo;
	TMenuItem *miRedo;
	TMenuItem *N5;
	TMenuItem *miCut;
	TMenuItem *miCopy;
	TMenuItem *miPaste;
	TMenuItem *miDelete;
	TMenuItem *N6;
	TMenuItem *miSelectAll;
	TMenuItem *miDeselectAll;
	TMenuItem *miInvertSelection;
	TMenuItem *N7;
	TMenuItem *Properties1;
	TMenuItem *Scene1;
	TMenuItem *Compile1;
	TMenuItem *Options1;
	TMenuItem *N8;
	TMenuItem *Validate1;
	TMenuItem *N9;
	TMenuItem *SummaryInfo1;
	TMenuItem *HighlightTexture1;
	TMenuItem *N10;
	TMenuItem *ClearDebugDraw1;
	TMenuItem *N11;
	TMenuItem *ExportentireSceneasObj1;
	TMenuItem *Exportselection1;
	TMenuItem *miBuild;
	TMenuItem *N12;
	TMenuItem *miMakeGame;
	TMenuItem *miMakeDetails;
	TMenuItem *miMakeHOM;
	TMenuItem *miMakeSoundOccluder;
	TMenuItem *miMakeAIMap;
	TMenuItem *N13;
	TMenuItem *ImportErrorList1;
	TMenuItem *ExportErrorList1;
	TMenuItem *ClearErrorList1;
	TMenuItem *Objects1;
	TMenuItem *Images1;
	TMenuItem *Sounds1;
	TMenuItem *LibraryEditor1;
	TMenuItem *N14;
	TMenuItem *ReloadObjects1;
	TMenuItem *CleanLibrary1;
	TMenuItem *ClipEditor1;
	TMenuItem *ImageEditor1;
	TMenuItem *N15;
	TMenuItem *ReloadTextures1;
	TMenuItem *SychronizeTextures1;
	TMenuItem *CheckNewTextures1;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *EditMinimap1;
	TMenuItem *SynchronizeTHM1;
	TMenuItem *SoundEditor1;
	TMenuItem *N18;
	TMenuItem *SynchronizeSounds1;
	TMenuItem *N19;
	TMenuItem *RefreshEnvironmentLibrary1;
	TMenuItem *RefreshEnvironmentGeometry1;
	TMenuItem *LoadSoundOccluder1;
	TMenuItem *HideSelected1;
	TMenuItem *HideUnselected1;
	TMenuItem *Unhideall1;
	TMenuItem *N20;
	TMenuItem *HideAll1;
	TMenuItem *N21;
	TMenuItem *MultiRename1;
	TMenuItem *Other1;
	TMenuItem *LightAnimEditor1;
	TMenuItem *ObjectList1;
	TMenuItem *Preferences1;
	TMenuItem *N4;
	TMenuItem *miRun;
	TMenuItem *N22;
	TMenuItem *miCompileLevel;
	TMenuItem *miCompileDetails;
	TMenuItem *miCompileAIMap;
	TMenuItem *miCompileSpawn;
	TMenuItem *N23;
	TMenuItem *About1;
        void __fastcall FormCreate(TObject *Sender);
    void __fastcall D3DWindowResize(TObject *Sender);
    void __fastcall D3DWindowKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall D3DWindowKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall sbToolsMinClick(TObject *Sender);
    void __fastcall TopClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall tmRefreshTimer(TObject *Sender);
    void __fastcall D3DWindowPaint(TObject *Sender);
    void __fastcall D3DWindowKeyPress(TObject *Sender, char &Key);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall D3DWindowChangeFocus(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall D3DWindowMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall D3DWindowMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall D3DWindowMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
	void __fastcall ebAllMinClick(TObject *Sender);
	void __fastcall ebAllMaxClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall paRenderResize(TObject *Sender);
	void __fastcall fsStorageSavePlacement(TObject *Sender);
	void __fastcall miClearClick(TObject *Sender);
	void __fastcall miOpenClick(TObject *Sender);
	void __fastcall miSaveClick(TObject *Sender);
	void __fastcall miSaveAsClick(TObject *Sender);
	void __fastcall miQuitClick(TObject *Sender);
	void __fastcall miOpenSelectionClick(TObject *Sender);
	void __fastcall miSaveSelectionClick(TObject *Sender);
	void __fastcall miMakePackClick(TObject *Sender);
	void __fastcall miUndoClick(TObject *Sender);
	void __fastcall miRedoClick(TObject *Sender);
	void __fastcall miCutClick(TObject *Sender);
	void __fastcall miCopyClick(TObject *Sender);
	void __fastcall miPasteClick(TObject *Sender);
	void __fastcall miDeleteClick(TObject *Sender);
	void __fastcall miSelectAllClick(TObject *Sender);
	void __fastcall miDeselectAllClick(TObject *Sender);
	void __fastcall miInvertSelectionClick(TObject *Sender);
	void __fastcall miBuildClick(TObject *Sender);
	void __fastcall miMakeGameClick(TObject *Sender);
	void __fastcall miMakeDetailsClick(TObject *Sender);
	void __fastcall miMakeHOMClick(TObject *Sender);
	void __fastcall miMakeSoundOccluderClick(TObject *Sender);
	void __fastcall miMakeAIMapClick(TObject *Sender);
	void __fastcall Options1Click(TObject *Sender);
	void __fastcall Validate1Click(TObject *Sender);
	void __fastcall SummaryInfo1Click(TObject *Sender);
	void __fastcall HighlightTexture1Click(TObject *Sender);
	void __fastcall ClearDebugDraw1Click(TObject *Sender);
	void __fastcall ExportentireSceneasObj1Click(TObject *Sender);
	void __fastcall Exportselection1Click(TObject *Sender);
	void __fastcall ImportErrorList1Click(TObject *Sender);
	void __fastcall ExportErrorList1Click(TObject *Sender);
	void __fastcall ClearErrorList1Click(TObject *Sender);
	void __fastcall LibraryEditor1Click(TObject *Sender);
	void __fastcall ReloadObjects1Click(TObject *Sender);
	void __fastcall CleanLibrary1Click(TObject *Sender);
	void __fastcall ClipEditor1Click(TObject *Sender);
	void __fastcall ImageEditor1Click(TObject *Sender);
	void __fastcall ReloadTextures1Click(TObject *Sender);
	void __fastcall SychronizeTextures1Click(TObject *Sender);
	void __fastcall CheckNewTextures1Click(TObject *Sender);
	void __fastcall EditMinimap1Click(TObject *Sender);
	void __fastcall SynchronizeTHM1Click(TObject *Sender);
	void __fastcall SoundEditor1Click(TObject *Sender);
	void __fastcall SynchronizeSounds1Click(TObject *Sender);
	void __fastcall RefreshEnvironmentLibrary1Click(TObject *Sender);
	void __fastcall RefreshEnvironmentGeometry1Click(TObject *Sender);
	void __fastcall LoadSoundOccluder1Click(TObject *Sender);
	void __fastcall HideSelected1Click(TObject *Sender);
	void __fastcall HideUnselected1Click(TObject *Sender);
	void __fastcall HideAll1Click(TObject *Sender);
	void __fastcall Unhideall1Click(TObject *Sender);
	void __fastcall MultiRename1Click(TObject *Sender);
	void __fastcall Properties1Click(TObject *Sender);
	void __fastcall LightAnimEditor1Click(TObject *Sender);
	void __fastcall ObjectList1Click(TObject *Sender);
	void __fastcall Preferences1Click(TObject *Sender);
	void __fastcall miRunClick(TObject *Sender);
	void __fastcall miCompileLevelClick(TObject *Sender);
	void __fastcall miCompileDetailsClick(TObject *Sender);
	void __fastcall miCompileAIMapClick(TObject *Sender);
	void __fastcall miCompileSpawnClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
private:	// User declarations
    void __fastcall IdleHandler(TObject *Sender, bool &Done);

	TShiftState	ShiftKey;
    HINSTANCE 	m_HInstance;
public:		// User declarations
    __fastcall 		TfrmMain(TComponent* Owner);
    void __fastcall UpdateCaption();
    __inline void 	SetHInst(HINSTANCE inst){ m_HInstance=inst; }
    bool            IsFocused(){return D3DWindow->Focused();}
    void			RefreshBars();
    void __fastcall miOpenRecentClick(TObject *Sender);
};
//---------------------------------------------------------------------------
extern /*ECORE_API*/ PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
