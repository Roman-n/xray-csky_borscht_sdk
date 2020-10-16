// LevelEditor.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "LevelEditor.h"
#include "../ECore/Editor/EditMesh.h"
#ifndef NO_VCL
#include "main.h"
#endif
#include "Edit/scene.h"
#include "Edit/UI_LevelMain.h"
#include "Edit/UI_LevelTools.h"

#include "ImGui/IM_LeftBar.h"
#include "ImGui/IM_TopBar.h"
#include "ImGui/IM_ContextMenu.h"

#include "../xrEProps/EditorChooseEvents.H"

#include "StatusBar.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // current instance
char szTitle[MAX_LOADSTRING]; // The title bar text
char szWindowClass[MAX_LOADSTRING]; // the main window class name
HWND g_MainWnd;
bool g_idle = false;
TShiftState g_ShiftKey;
TD3DWindow* g_d3dWnd = 0;

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_LEVELEDITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    Debug._initialize(false);
    Core._initialize("level", ELogCallback, 1, 0, true);
    CEditableMesh::m_bDraftMeshMode = TRUE;

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LEVELEDITOR));

    g_d3dWnd = xr_new<TD3DWindow>();
    g_d3dWnd->Handle = g_MainWnd;
    RECT r;
    GetClientRect(g_MainWnd, &r);

    Tools					= xr_new<CLevelTool>();
    UI						= xr_new<CLevelMain>();
    UI->RegisterCommands	();
	Scene					= xr_new<EScene>();
	SetWindowText(g_MainWnd, UI->EditorDesc());

	Device.SetHandle		(g_MainWnd,g_MainWnd);
    EnableReceiveCommands	();
    if (!ExecCommand(COMMAND_INITIALIZE,(uintptr_t)g_d3dWnd,(uintptr_t)0)){ 
    	FlushLog			();
    	TerminateProcess(GetCurrentProcess(),-1);
    }

    ShowWindow(g_MainWnd, nCmdShow);
    UpdateWindow(g_MainWnd);

    UI->AddIMWindow(&imLeftBar);
    UI->AddIMWindow(&imTopBar);
    UI->AddIMWindow(&imContextMenu);

		FillChooseEvents();

    // Main message loop:
    g_idle = true;
    MSG msg {};
    while (msg.message != WM_QUIT) {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            continue;
        }
        DispatchQueueedCommands();
        if (g_idle) UI->Idle();
    }
    
    ClearChooseEvents();

    UI->ClearCommands		();
    xr_delete				(Scene);
    xr_delete				(Tools);
    xr_delete				(UI);

    Core._destroy			();

    return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_CLASSDC;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LEVELEDITOR));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    g_MainWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr,
        nullptr, hInstance, nullptr);

    if (!g_MainWnd) {
        return FALSE;
    }

    return TRUE;
}

TShiftState getShiftState()
{
    TShiftState shift;
    if (GetKeyState(VK_MENU) < 0)
        shift << ssAlt;
    if (GetKeyState(VK_SHIFT) < 0)
        shift << ssShift;
    if (GetKeyState(VK_CONTROL) < 0)
        shift << ssCtrl;
    return shift;
}

TShiftState getMouseShiftState(WPARAM wParam)
{
    TShiftState shift;
    if (GetKeyState(VK_MENU) < 0)
        shift << ssAlt;
    if (wParam & MK_SHIFT)
        shift << ssShift;
    if (wParam & MK_CONTROL)
        shift << ssCtrl;
    if (wParam & MK_LBUTTON)
        shift << ssLeft;
    if (wParam & MK_MBUTTON)
        shift << ssMiddle;
    if (wParam & MK_RBUTTON)
        shift << ssRight;
    if (wParam & MK_CONTROL)
        shift << ssCtrl;
    if (wParam & MK_CONTROL)
        shift << ssCtrl;

    return shift;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if(SB_ProcessMessage(message, wParam, lParam))
    	return 0;
    	
    switch (message) {
    case WM_CREATE: {
        SB_Initialize(hWnd);
    } break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId) {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    } break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
	    if (UI && UI->m_bReady)
            UI->RedrawScene();
    } break;
    case WM_SIZE: {  
        int newWidth = GET_X_LPARAM(lParam);
        int newHeight = GET_Y_LPARAM(lParam);
        if (newWidth != 0 && newHeight != 0) {
            g_d3dWnd->Width = newWidth;
            g_d3dWnd->Height = newHeight;
            ExecCommand(COMMAND_RENDER_RESIZE);
            if (UI) UI->Resize();
        }  
    } break;
    case WM_CLOSE:
        g_idle = false;
        ExecCommand				(COMMAND_DESTROY);
        DestroyWindow(g_MainWnd);
        break;
    case WM_KEYDOWN: case WM_SYSKEYDOWN:
        g_ShiftKey = getShiftState();
        if (!UI->KeyDown(wParam, g_ShiftKey)){UI->ApplyShortCut(wParam, g_ShiftKey);}
        break;
    case WM_KEYUP: case WM_SYSKEYUP:
        if (!UI->KeyUp(wParam, getShiftState())){;}
        break;
    case WM_CHAR:
        if (!UI->KeyPress(wParam, g_ShiftKey)){;}
        break;
    case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:
        UI->MousePress(getMouseShiftState(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
        UI->RedrawScene();
        break;
    case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
        UI->MouseRelease(getMouseShiftState(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
        UI->RedrawScene();
        break;
    case WM_MOUSEMOVE:
        UI->MouseMove(getMouseShiftState(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
