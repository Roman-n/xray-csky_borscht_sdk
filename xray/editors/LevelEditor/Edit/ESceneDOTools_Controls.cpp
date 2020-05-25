#include "stdafx.h"
#pragma hdrstop

#include "ESceneDOTools.h"
#ifndef NO_VCL
#include "FrameDetObj.h"
#endif
#include "UI_LevelTools.h"
#include "ESceneControlsCustom.h"

void EDetailManager::CreateControls()
{
	AddControl		(xr_new<TUI_CustomControl>(estDefault,	etaSelect, this));
#ifndef NO_VCL
	// frame
    pFrame 			= xr_new<TfraDetailObject>((TComponent*)0,this);
#endif
}
//----------------------------------------------------
 
void EDetailManager::RemoveControls()
{
	inherited::RemoveControls();
}
//----------------------------------------------------

                     