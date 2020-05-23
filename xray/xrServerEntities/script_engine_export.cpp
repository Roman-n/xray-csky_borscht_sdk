////////////////////////////////////////////////////////////////////////////
//	Module 		: script_engine_export.cpp
//	Created 	: 01.04.2004
//  Modified 	: 22.06.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script Engine export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"
#define SCRIPT_REGISTRATOR
#include "script_export_space.h"
#include "script_engine_export.h"

#pragma optimize("s",on)

template <class... Ts> void Register(lua_State* L, type_pack<Ts...>)
{
    ((
#ifdef XRGAME_EXPORTS
#    ifdef DEBUG
    Msg("Exporting %s", typeid(Ts).name()),
#    endif
#endif
    Ts::script_register(L)),...);
}

void export_classes	(lua_State *L)
{
	Register(L, script_type_list);
}
