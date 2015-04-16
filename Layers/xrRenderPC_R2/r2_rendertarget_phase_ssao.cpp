#include "stdafx.h"

//#include "../../xrEngine/igame_persistent.h"
//#include "../../xrEngine/environment.h"

#pragma pack(push,4)
struct v_ssao {
	Fvector4	p;
	Fvector2	uv0;
	Fvector2	uv1;
};
#pragma pack(pop)

float	hclip(float v, float dim);

void CRenderTarget::phase_ssao	()
{
	Fvector2	p0,p1;
	u32			Offset = 0;

	// Targets
	u_setrt									( rt_ssao_temp,NULL,NULL,NULL );		// No need for ZBuffer at all
	u32		clr4clear					= color_rgba(0,0,0,0);	// 0x00
	CHK_DX	(HW.pDevice->Clear			( 0L, NULL, D3DCLEAR_TARGET, clr4clear, 1.0f, 0L));

	CHK_DX		(HW.pDevice->SetRenderState	( D3DRS_ZENABLE,		FALSE				));

	RCache.set_Stencil					(TRUE,D3DCMP_LESSEQUAL,0x01,0xff,0x00);	// stencil should be >= 1
	if (RImplementation.o.nvstencil)	
	{
		u_stencil_optimize				(FALSE);
		RCache.set_ColorWriteEnable		();
	}

	RCache.set_Stencil(FALSE);//TODO - disable later

	{
		Fmatrix	m_v2w;				m_v2w.invert(Device.mView);
		// Fill VB
		float	_w					= float(Device.dwWidth);
		float	_h					= float(Device.dwHeight);
		p0.set						(.5f/_w, .5f/_h);
		p1.set						((_w+.5f)/_w, (_h+.5f)/_h );

		float		fSSAONoise = 2.0f;
		fSSAONoise *= tan(deg2rad(67.5f));
		fSSAONoise /= tan(deg2rad(Device.fFOV));

		float		fSSAOKernelSize = 150.0f;
		fSSAOKernelSize *= tan(deg2rad(67.5f));
		fSSAOKernelSize /= tan(deg2rad(Device.fFOV));

		float	scale_X				= float(Device.dwWidth)	/ float(TEX_jitter);
		float	scale_Y				= float(Device.dwHeight)/ float(TEX_jitter);

		FVF::TL* pv					= (FVF::TL*)	RCache.Vertex.Lock	(4,g_combine_VP->vb_stride,Offset);
		pv->set						(hclip(EPS,		_w),	hclip(_h+EPS,	_h),	p0.x, p1.y, 0, 0,			scale_Y	);	pv++;
		pv->set						(hclip(EPS,		_w),	hclip(EPS,		_h),	p0.x, p0.y, 0, 0,			0		);	pv++;
		pv->set						(hclip(_w+EPS,	_w),	hclip(_h+EPS,	_h),	p1.x, p1.y, 0, scale_X,	scale_Y	);	pv++;
		pv->set						(hclip(_w+EPS,	_w),	hclip(EPS,		_h),	p1.x, p0.y, 0, scale_X,	0		);	pv++;
		RCache.Vertex.Unlock		(4,g_combine_VP->vb_stride);

		RCache.set_Element			(s_ssao->E[0]);
		RCache.set_Geometry			(g_combine_VP		);
		RCache.set_c				("ssao_params",		fSSAONoise, fSSAOKernelSize, 0.0f, 0.0f);
		RCache.set_c				("m_v2w",			m_v2w);
		RCache.Render				(D3DPT_TRIANGLELIST,Offset,0,4,0,2);
	}

	// re-enable z-buffer
	CHK_DX		(HW.pDevice->SetRenderState	( D3DRS_ZENABLE,	TRUE				));
	RCache.set_Stencil(FALSE);
}
