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
    return {};
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
