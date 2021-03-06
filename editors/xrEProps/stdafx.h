//----------------------------------------------------
// file: stdafx.h
//----------------------------------------------------
#ifndef stdafxH
#define stdafxH

#pragma once   

#include <xrCore.h>

#define smart_cast dynamic_cast

//refs
namespace CDB{
	class MODEL;
};

#include "xrEProps.h"

#include "FolderLib.h"                 

#define ENGINE_API
#define DLL_API		__declspec(dllimport)
#define ECORE_API	__declspec(dllexport)

#include "Defines.h"                 

// libs
#pragma comment		(lib,"xrSoundB.lib")
#pragma comment		(lib,"xrCoreB.lib")

#define INI_NAME(buf)		(FS.update_path(buf, "$local_root$", GetIniFileName().c_str()))
#define DEFINE_INI(storage)	{string_path buf; INI_NAME(buf); storage->IniFileName=buf;}

#endif //stdafxH

