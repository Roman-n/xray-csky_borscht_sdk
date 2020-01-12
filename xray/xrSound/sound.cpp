#include "stdafx.h"
#include "SoundRender_CoreA.h"
#include "SoundRender_NoSound.h"

XRSOUND_API xr_token*		snd_devices_token	= NULL;
XRSOUND_API u32				snd_device_id		= u32(-1);

void CSound_manager_interface::_create(int stage)
{
	if(stage==0)
	{
		if (strstr(Core.Params, "-nosound")) {
			Sound = xr_new<SoundRender_NoSound>();
		}
		else {
			SoundRenderA = xr_new<CSoundRender_CoreA>();
			SoundRender = SoundRenderA;
			Sound = SoundRender;
		}
	}
	if (!Sound->_initialize(stage)) {
		xr_delete(Sound);
		Sound = xr_new<SoundRender_NoSound>();
	}
}

void CSound_manager_interface::_destroy	()
{
	Sound->_clear		();
    xr_delete			(Sound);
    Sound				= 0;
}

