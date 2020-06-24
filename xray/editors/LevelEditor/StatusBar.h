#ifndef __STATUS_BAR_H__
#define __STATUS_BAR_H__

#define STATUSBAR_ID 4000

void SB_Initialize(HWND parent);
BOOL SB_SetStatus(LPCSTR text);
void SB_SetInfo(int n, LPCSTR text);
void SB_DrawProgress(void);

// message handling subroutine
BOOL SB_ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam);

#endif