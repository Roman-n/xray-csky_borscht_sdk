//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include <colorpicker/FSColorPicker.h>
#include "ColorPicker.h"

class CTCD{
public:
	TColorDialog* cdColor;
public:
	CTCD(){
		cdColor = xr_new<TColorDialog>((TComponent*)0);
        cdColor->Options = TColorDialogOptions()<<cdFullOpen;
    }
    ~CTCD(){
    	xr_delete(cdColor);
    }
};
static CTCD TCD;

bool SelectColor(u32* currentcolor, bool bDefaultPicker){
	VERIFY(currentcolor);
	if (bDefaultPicker){
        TCD.cdColor->Color = TColor(rgb2bgr(*currentcolor));
        if (TCD.cdColor->Execute()){
			*currentcolor = bgr2rgb(TCD.cdColor->Color);
        	return true;
        }
        return false;
    }else{
    	u32 clr=*currentcolor;
  	    if (FSColorPickerDoModal(&clr, 0, 0)){
        	*currentcolor = clr;
         	return true;
        }
        return false;
    }
}

bool SelectColorWin(u32* currentcolor, bool bDefaultPicker){
	VERIFY(currentcolor);
	if (bDefaultPicker){
        TCD.cdColor->Color = TColor(*currentcolor);
        if (TCD.cdColor->Execute()){
			*currentcolor = TCD.cdColor->Color;
        	return true;
        }
        return false;
    }else{
        u32 cur = bgr2rgb(*currentcolor);
        if (FSColorPickerDoModal(&cur, 0, 0)){
			*currentcolor = rgb2bgr(cur);
        	return true;
        }
	    return false;
    }
}

