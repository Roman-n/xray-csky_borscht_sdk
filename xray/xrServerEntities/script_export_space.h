////////////////////////////////////////////////////////////////////////////
//	Module 		: script_export_space.h
//	Created 	: 22.09.2003
//  Modified 	: 01.04.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script export space 
////////////////////////////////////////////////////////////////////////////

#ifndef script_export_spaceH
#define script_export_spaceH

#pragma once

struct lua_State;

#ifdef SCRIPT_REGISTRATOR
template <class T> struct just_type { using type = T; };
template <class... Ts> struct type_pack {};
using empty_pack = type_pack<>;
template <class... Ts, class T> constexpr type_pack<Ts..., T> push_back(type_pack<Ts...>, just_type<T>) { return {}; }
#	define script_type_list       empty_pack{}
#   define add_to_type_list(type) auto TypeList_##type = push_back(script_type_list, just_type<type>{});
#	define save_type_list(type)	  TypeList_##type
#else
#	define	script_type_list		
#	define	add_to_type_list(type)	;
#	define	save_type_list(type)		
#endif

#define DECLARE_SCRIPT_REGISTER_FUNCTION public: static void script_register(lua_State *);
#define DECLARE_SCRIPT_REGISTER_FUNCTION_STRUCT static void script_register(lua_State *);

template <typename T> struct enum_exporter{DECLARE_SCRIPT_REGISTER_FUNCTION};
template <typename T> struct class_exporter{DECLARE_SCRIPT_REGISTER_FUNCTION};

#endif
