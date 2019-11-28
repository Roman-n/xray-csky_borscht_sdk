#include "stdafx.h"
#pragma hdrstop

#include "Environment.h"
#ifndef _EDITOR
    #include "render.h"
#endif
#include "xr_efflensflare.h"
#include "rain.h"
#include "thunderbolt.h"

#ifndef _EDITOR
#	include "igame_level.h"
#endif

//-----------------------------------------------------------------------------
// Environment render
//-----------------------------------------------------------------------------
extern ENGINE_API float psHUD_FOV;
//BOOL bNeed_re_create_env = FALSE;
void CEnvironment::RenderSky		()
{
#ifndef _EDITOR
	if (0==g_pGameLevel)		return;
#endif

	m_pRender->RenderSky(*this);
}

void CEnvironment::RenderClouds			()
{
#ifndef _EDITOR
	if (0==g_pGameLevel)		return	;
#endif
	// draw clouds
	if (fis_zero(CurrentEnv->clouds_color.w,EPS_L))	return;

	m_pRender->RenderClouds(*this);
}

void CEnvironment::RenderFlares		()
{
#ifndef _EDITOR
	if (0==g_pGameLevel)			return	;
#endif
	// 1
	eff_LensFlare->Render			(FALSE,TRUE,TRUE);
}

void CEnvironment::RenderLast		()
{
#ifndef _EDITOR
	if (0==g_pGameLevel)			return	;
#endif
	// 2
	eff_Rain->Render				();
	eff_Thunderbolt->Render			();
}

void CEnvironment::OnDeviceCreate()
{
//.	bNeed_re_create_env			= TRUE;
	m_pRender->OnDeviceCreate();

	// weathers
	{
		EnvsMapIt _I,_E;
		_I		= WeatherCycles.begin();
		_E		= WeatherCycles.end();
		for (; _I!=_E; _I++)
			for (EnvIt it=_I->second.begin(); it!=_I->second.end(); it++)
				(*it)->on_device_create();
	}
	// effects
	{
		EnvsMapIt _I,_E;
		_I		= WeatherFXs.begin();
		_E		= WeatherFXs.end();
		for (; _I!=_E; _I++)
			for (EnvIt it=_I->second.begin(); it!=_I->second.end(); it++)
				(*it)->on_device_create();
	}


	Invalidate	();
	OnFrame		();
}

void CEnvironment::OnDeviceDestroy()
{
	m_pRender->OnDeviceDestroy();

	// weathers
	{
		EnvsMapIt _I,_E;
		_I		= WeatherCycles.begin();
		_E		= WeatherCycles.end();
		for (; _I!=_E; _I++)
			for (EnvIt it=_I->second.begin(); it!=_I->second.end(); it++)
				(*it)->on_device_destroy();
	}
	// effects
	{
		EnvsMapIt _I,_E;
		_I		= WeatherFXs.begin();
		_E		= WeatherFXs.end();
		for (; _I!=_E; _I++)
			for (EnvIt it=_I->second.begin(); it!=_I->second.end(); it++)
				(*it)->on_device_destroy();
	}
	CurrentEnv->destroy();

}

#ifdef _EDITOR
void CEnvironment::ED_Reload()
{
	OnDeviceDestroy			();
	OnDeviceCreate			();
}
#endif

