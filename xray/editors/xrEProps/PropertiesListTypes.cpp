#include "stdafx.h"
#pragma hdrstop

#include "../../xrServerEntities/PropertiesListTypes.h"
#ifndef NO_VCL
#include "MxShortcut.hpp"
#endif
//------------------------------------------------------------------------------
            
xr_string	ShortcutValue::GetDrawText		(TOnDrawTextEvent OnDrawText)
{
#ifndef NO_VCL
    xr_string 	txt = MxShortCutToText(value->hotkey).c_str();
    if (!OnDrawText.empty())	OnDrawText(this, txt);
    return 			txt;
#else
	if(value->key != 0)
	{	
		char text[256] = "";
		char key_name[64];
		u8 key = value->key;
	
		if(value->ext.is(xr_shortcut::flShift)) 
			strcat(text, "Shift + ");	
		if(value->ext.is(xr_shortcut::flCtrl)) 
			strcat(text, "Ctrl + ");
		if(value->ext.is(xr_shortcut::flAlt)) 
			strcat(text, "Alt + ");
			
		if(key != VK_CONTROL && key != VK_MENU && key != VK_SHIFT)
		{
			GetKeyNameText(MapVirtualKey(key, 0) << 16, key_name, sizeof(key_name));
			strcat(text, key_name);
		}
		
		return text;
	}
	else
		return "None";
#endif
}

xr_string GameTypeValue::GetDrawText(TOnDrawTextEvent)
{
	string512 str;
    sprintf_s(str,sizeof(str),"%s%s%s%s%s",
	GetValue().MatchType(eGameIDSingle)?"Single ":"",
	GetValue().MatchType(eGameIDDeathmatch)?"DM ":"",
	GetValue().MatchType(eGameIDTeamDeathmatch)?"TDM ":"",
	GetValue().MatchType(eGameIDArtefactHunt)?"AH ":"",
	GetValue().MatchType(eGameIDCaptureTheArtefact)?"CTA":""    );
	return xr_string(str);
}
