//----------------------------------------------------
// file: stdafx.h
//----------------------------------------------------
#ifndef stdafxH
#define stdafxH

#pragma once   

#ifndef __BORLANDC__
#include "framework.h"
#include "../ECore/builder_types.h"
#endif

#include <xrCore/xrCore.h>

#define smart_cast dynamic_cast

//refs
namespace CDB{
	class MODEL;
};

#include <xrServerEntities/xrEProps.h>

#include "FolderLib.h"

#define ENGINE_API
#define DLL_API		__declspec(dllimport)
#define ECORE_API	__declspec(dllexport)

#include "../../xrEngine/Defines.h"                 

// libs
#ifdef __BORLANDC__
#pragma comment		(lib,"xrSoundB.lib")
#pragma comment		(lib,"xrCoreB.lib")
#pragma comment		(lib,"EToolsB.lib")
#endif

#endif //stdafxH

