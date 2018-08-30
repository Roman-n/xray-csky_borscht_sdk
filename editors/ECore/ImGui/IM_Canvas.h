#ifndef IM_CanvasH
#define IM_CanvasH

#include "IM_Window.h"

ECORE_API class IM_Canvas : public IM_Window
{
	private:
    int m_width, m_height;
   	ID3DTexture2D* m_texture;
    HDC m_hdc;
    HBITMAP m_hbitmap, m_holdbm;

	public:
    IM_Canvas(int width, int height);
    ~IM_Canvas();

    private:
    void CreateTexture();
    void DestroyTexture();

    public:

    int Width() { return m_width; }
    int Height() { return m_height; }

    void Clear();

    HDC BeginPaint();
    void EndPaint();

    virtual void Render();
};

#endif
