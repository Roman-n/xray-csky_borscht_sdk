#include "stdafx.h"
#pragma hdrstop

#include "IM_Canvas.h"
#include "imgui.h"
#include "../Editor/device.h"
#include <Layers/xrRender/ResourceManager.h>
#include <Layers/xrRender/SH_RT.h>

#pragma package(smart_init)

#define WITH(t,v,c) \
struct ___with##t : public t { void operator () () { c } }; ((___with##t *)v)->operator()();

IM_Canvas::IM_Canvas(int width, int height)
	: m_width(width),
      m_height(height),
      m_texture(NULL),
      m_hdc(NULL),
      m_hbitmap(NULL),
      m_holdbm(NULL)
{
	CreateTexture();
}

IM_Canvas::~IM_Canvas()
{
	DestroyTexture();
}

void IM_Canvas::CreateTexture()
{
	if(!HW.pDevice)
    	return;

    if(m_texture)
    	return;

 //	CHK_DX(HW.pDevice->CreateTexture(m_width, m_height, 1,
 //	0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &m_texture, NULL));

	char name[256];
	sprintf(name, "$user$canvas_%x", this);
	m_texture = Device.Resources->_CreateRT(name, m_width, m_height, D3DFMT_X8R8G8B8);
	VERIFY(m_texture);

	if(!m_texture->pSurface)
		xr_delete(m_texture); // not created
	else
		Clear();
}

void IM_Canvas::DestroyTexture()
{
	xr_delete(m_texture);
}

void IM_Canvas::Clear()
{
	if(!m_texture)
    	return;
        
	IDirect3DTexture9* tex;
    CHK_DX(HW.pDevice->CreateTexture(m_width, m_height, 1,
	D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &tex, NULL));

	IDirect3DSurface9* S;
	CHK_DX(tex->GetSurfaceLevel(0, &S));

	D3DLOCKED_RECT lr = {0};
	CHK_DX(S->LockRect(&lr, NULL, 0));
    memset(lr.pBits, 0, m_width*m_height*4);
	CHK_DX(S->UnlockRect());

	IDirect3DSurface9* D;
	CHK_DX(m_texture->pSurface->GetSurfaceLevel(0, &D));

	CHK_DX(HW.pDevice->UpdateSurface(S, NULL, D, NULL));

	D->Release();
	S->Release();
    tex->Release();
}

HDC IM_Canvas::BeginPaint()
{
	VERIFY(!m_hdc);

    m_hdc = CreateCompatibleDC(NULL);
    VERIFY(m_hdc);

    m_hbitmap = CreateBitmap(m_width, m_height, 1, 32, NULL);
    VERIFY(m_hbitmap);

    m_holdbm = (HBITMAP)SelectObject(m_hdc, (HGDIOBJ)m_hbitmap);
    VERIFY(m_holdbm);

    return m_hdc;
}

void IM_Canvas::EndPaint()
{
	VERIFY(m_hdc);

    CreateTexture();
	if(m_texture)
    {
    	IDirect3DTexture9* tex;
        CHK_DX(HW.pDevice->CreateTexture(m_width, m_height, 1,
        D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &tex, NULL));

        RECT r = { 0, 0, m_width, m_height };
        D3DLOCKED_RECT lr = {0};
        CHK_DX(tex->LockRect(0, &lr, &r, 0));

        struct
        {
        	BITMAPINFOHEADER bmiHeader;
            DWORD colors[3];
        } bmi;

        WITH(BITMAPINFOHEADER, &bmi.bmiHeader,
        {
        	biSize = sizeof(BITMAPINFOHEADER);
            biPlanes = 1;
            biBitCount = 32;
            biCompression = BI_BITFIELDS;
            biSizeImage = 0;
            biXPelsPerMeter = 0;
            biYPelsPerMeter = 0;
            biClrUsed = 0;
            biClrImportant = 0;
        });

        bmi.bmiHeader.biWidth = m_width;
        bmi.bmiHeader.biHeight = -m_height;

        bmi.colors[0] = 0x00FF0000;
        bmi.colors[1] = 0x0000FF00;
        bmi.colors[2] = 0x000000FF;

        int n = GetDIBits(m_hdc, m_hbitmap, 0, m_height, lr.pBits, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS);
        VERIFY(n != 0);

		CHK_DX(tex->UnlockRect(0));

		IDirect3DSurface9* S;
		CHK_DX(tex->GetSurfaceLevel(0, &S));

		IDirect3DSurface9* D;
		CHK_DX(m_texture->pSurface->GetSurfaceLevel(0, &D));

		CHK_DX(HW.pDevice->UpdateSurface(S, NULL, D, NULL));

		D->Release();
		S->Release();
		tex->Release();
	}

    SelectObject(m_hdc, (HGDIOBJ)m_holdbm);
    DeleteObject((HGDIOBJ)m_hbitmap);
    DeleteDC(m_hdc);

    m_hbitmap = NULL;
    m_holdbm = NULL;
    m_hdc = NULL;
}

void IM_Canvas::Render()
{
	ImGui::Image(
	m_texture ? (void*)m_texture->pSurface : NULL,
	ImVec2(m_width, m_height),
    ImVec2(0.0, 0.0), ImVec2(1.0, 1.0), ImVec4(1,1,1,1), ImVec4(0,0,0,0));
}
