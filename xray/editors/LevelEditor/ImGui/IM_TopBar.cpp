#include "stdafx.h"
#pragma hdrstop

#include "../ECore/ImGui/ImGui.h"

#include "IM_TopBar.h"
#include "../ECore/Editor/device.h"
#include <Layers/xrRender/ResourceManager.h>
#include <Layers/xrRender/SH_Texture.h>

#include "../Edit/UI_LevelMain.h"
#include "../Edit/UI_LevelTools.h"

#pragma package(smart_init)

#define ATLAS_SIZE_X 8
#define ATLAS_SIZE_Y 8

bool IM_TopBar::Button(int image_id, const char* tooltip, bool selected)
{
    // tc's
    float u = float(image_id % ATLAS_SIZE_X) / ATLAS_SIZE_X;
    float v = float(image_id / ATLAS_SIZE_Y) / ATLAS_SIZE_Y;

    ImVec2 padding = ImGui::GetStyle().WindowPadding;
    ImVec2 window_size = ImGui::GetWindowSize();

    float size = m_vertical ? window_size.x-padding.x*2 : window_size.y-padding.y*2;
    if(!m_ui_texture->flags.bLoaded) m_ui_texture->Load();
    IDirect3DBaseTexture9* lpTexture = m_ui_texture->surface_get();

    ImGui::Image(lpTexture, ImVec2(size, size),
    ImVec2(u, v), ImVec2(u + 1.0/ATLAS_SIZE_X, v + 1.0/ATLAS_SIZE_Y),
    ImVec4(1,1,1,1), selected ? ImGui::GetStyleColorVec4(ImGuiCol_CheckMark) : ImVec4(0,0,0,0));

    if(tooltip && ImGui::IsItemHovered())
    	ImGui::SetTooltip("%s", tooltip);

    if(lpTexture)
        lpTexture->Release();

    if(!m_vertical)
        ImGui::SameLine();

    return ImGui::IsItemClicked();
}

void IM_TopBar::Separator()
{
	if(m_vertical)
    	ImGui::Separator();
    else
    	ImGui::SameLine(0, 5);
}

void IM_TopBar::OnAdd()
{
    m_ui_texture = Device.Resources->_CreateTexture("ui\\ui_editor_icons");
}

void IM_TopBar::OnRemove()
{
//    Device.Resources->_DeleteTexture(m_ui_texture);
}

void IM_TopBar::Render()
{
    if(!ImGui::Begin("Top bar", NULL, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoScrollbar))
        return;

    ImVec2 size = ImGui::GetWindowSize();
    m_vertical = size.y>size.x;
/*
    // undo/redo
    if(Button(5, "Undo"))
    	ExecCommand(COMMAND_UNDO);
    if(Button(6, "Redo"))
    	ExecCommand(COMMAND_REDO);
*/
    Separator();

    // action buttons
    if(Button(0, "Select", Tools->GetAction() == etaSelect))
        Tools->SetAction(etaSelect);
    if(Button(1, "Add", Tools->GetAction() == etaAdd))
        Tools->SetAction(etaAdd);
    if(Button(2, "Move", Tools->GetAction() == etaMove))
        Tools->SetAction(etaMove);
    if(Button(3, "Rotate", Tools->GetAction() == etaRotate))
        Tools->SetAction(etaRotate);
    if(Button(4, "Scale", Tools->GetAction() == etaScale))
        Tools->SetAction(etaScale);

    Separator();

    // axis buttons
    if(Button(8, "Restrict to X", Tools->GetAxis() == etAxisX))
        Tools->SetAxis(etAxisX);
    if(Button(9, "Restrict to Y", Tools->GetAxis() == etAxisY))
        Tools->SetAxis(etAxisY);
    if(Button(10, "Restrict to Z", Tools->GetAxis() == etAxisZ))
        Tools->SetAxis(etAxisZ);
    if(Button(11, "Restrict to ZX", Tools->GetAxis() == etAxisZX))
        Tools->SetAxis(etAxisZX);

    if(Button(41, "Parent CS toggle", Tools->GetSettings(etfCSParent)))
        ExecCommand(COMMAND_SET_SETTINGS, etfCSParent, !Tools->GetSettings(etfCSParent));
    if(Button(40, "Non-uniform scale", Tools->GetSettings(etfNUScale)))
        ExecCommand(COMMAND_SET_SETTINGS, etfNUScale, !Tools->GetSettings(etfNUScale));

    Separator();

    // snap buttons
    if(Button(16, "Snap to grid", Tools->GetSettings(etfGSnap)))
        ExecCommand(COMMAND_SET_SETTINGS, etfGSnap, !Tools->GetSettings(etfGSnap));
    if(Button(17, "Snap to objects", Tools->GetSettings(etfOSnap)))
    	ExecCommand(COMMAND_SET_SETTINGS, etfOSnap, !Tools->GetSettings(etfOSnap));
    if(Button(18, "Moving snap", Tools->GetSettings(etfMTSnap)))
    	ExecCommand(COMMAND_SET_SETTINGS, etfMTSnap, !Tools->GetSettings(etfMTSnap));
    if(Button(19, "Normal alignment", Tools->GetSettings(etfNormalAlign)))
    	ExecCommand(COMMAND_SET_SETTINGS, etfNormalAlign, !Tools->GetSettings(etfNormalAlign));
    if(Button(20, "Snap to vertex", Tools->GetSettings(etfVSnap)))
    	ExecCommand(COMMAND_SET_SETTINGS, etfVSnap, !Tools->GetSettings(etfVSnap));
    if(Button(21, "Angle snap", Tools->GetSettings(etfASnap)))
    	ExecCommand(COMMAND_SET_SETTINGS, etfASnap, !Tools->GetSettings(etfASnap));
    if(Button(22, "Moving snap", Tools->GetSettings(etfMSnap)))
    	ExecCommand(COMMAND_SET_SETTINGS, etfMSnap, !Tools->GetSettings(etfMSnap));

    Separator();

    // focus buttons
    if(Button(42, "Focus on whole scene"))
    	ExecCommand(COMMAND_ZOOM_EXTENTS, FALSE);
    if(Button(43, "Focus on selected"))
    	ExecCommand(COMMAND_ZOOM_EXTENTS, TRUE);

    Separator();

    // view buttons
    if(Button(24, "Front view"))
        Device.m_Camera.ViewFront();
    if(Button(25, "Back view"))
        Device.m_Camera.ViewBack();
    if(Button(26, "Left view"))
        Device.m_Camera.ViewLeft();
    if(Button(27, "Right view"))
        Device.m_Camera.ViewRight();
    if(Button(28, "Top view"))
        Device.m_Camera.ViewTop();
    if(Button(29, "Bottom view"))
        Device.m_Camera.ViewBottom();
    if(Button(30, "Reset view"))
        Device.m_Camera.ViewReset();

    Separator();

    // camera mode buttons
    if(Button(32, "PlaneMove", Device.m_Camera.GetStyle() == csPlaneMove))
    	Device.m_Camera.SetStyle(csPlaneMove);
    if(Button(33, "3DArcBall", Device.m_Camera.GetStyle() == cs3DArcBall))
    	Device.m_Camera.SetStyle(cs3DArcBall);
	if(Button(34, "FreeFly", Device.m_Camera.GetStyle() == csFreeFly))
    	Device.m_Camera.SetStyle(csFreeFly);


    ImGui::End();
}

IM_TopBar imTopBar;
