#include "stdafx.h"
#include "embedded_editor_ae.h"
#include "../../Include/xrRender/Kinematics.h"
#include "../../Include/xrRender/KinematicsAnimated.h"
#include "../../Include/xrRender/RenderVisual.h"
#include "../../xrServerEntities/xrServer_Objects_ALife.h"
#include "../Level.h"
#include "../ai_space.h"
#include "../alife_simulator.h"
#include "../game_level_cross_table.h"
#include "../level_graph.h"
#include "../script_object.h"
#include "controls/imgui_ext.h"
#include "embedded_editor_helper.h"
#include <Commdlg.h>

static CSE_ALifeDynamicObjectVisual* sobj = nullptr;
static CObject* obj = nullptr;
static xr_set<u16> opened_motions;
static xr_vector<xr_vector<shared_str>> animations;
static u16 selected_bone = -1;

void ShowAnimated(IKinematicsAnimated* v);
void ShowKinematics(IKinematics* v);
void ShowMainWindow(bool& show);
void ShowMotionWindow(u16 motion);
void refresh_animations();
void showBoneProps();

void ShowAeWindow(bool& show)
{
    ShowMainWindow(show);
    for (auto& el : opened_motions) {
        ShowMotionWindow(el);
    }
    if (selected_bone != -1)
        showBoneProps();
}

void ShowAnimated(IKinematicsAnimated* ka)
{
    if (ImGui::CollapsingHeader("Animations")) {
        u16 count = ka->LL_MotionsSlotCount();
        for (u16 i = 0; i != count; i++) {
            const shared_motions& el = ka->LL_MotionsSlot(i);
            char buf[100];
            strcpy(buf, el.id().c_str());
            ImGui::InputText("", buf, 100);
            ImGui::SameLine();
            sprintf(buf, "...##anim%u", i);
            if (ImGui::Button(buf))
                opened_motions.insert(i);
            ImGui::SameLine();
            sprintf(buf, "X##anim%u", i);
            ImGui::Button(buf);
        }
        ImGui::Button("+");
    }
}

static u16 new_selected_node = -1;
void drawBone(u16 bone, IKinematics* k)
{
    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick
        | ((bone == selected_bone) ? ImGuiTreeNodeFlags_Selected : 0);

    const auto& data = k->LL_GetData(bone);
    if (data.children.empty()) {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
        ImGui::TreeNodeEx(
            (void*)(intptr_t)bone, nodeFlags, "%s (faces: %lu)", data.name.data(), data.child_faces.size());
        if (ImGui::IsItemClicked())
            new_selected_node = bone;
    } else {
        bool open = ImGui::TreeNodeEx(
            (void*)(intptr_t)bone, nodeFlags, "%s (faces: %lu)", data.name.data(), data.child_faces.size());
        if (ImGui::IsItemClicked())
            new_selected_node = bone;
        if (open) {
            for (const auto* child : data.children)
                drawBone(child->GetSelfID(), k);
            ImGui::TreePop();
        }
    }
}

void ShowKinematics(IKinematics* k)
{
    ImGui::Spacing();
    char buf[100];
    sprintf(buf, "Bones: %d", k->LL_BoneCount());
    if (ImGui::CollapsingHeader(buf)) {
        CInifile* ini = k->LL_UserData();
        u16 root = k->LL_GetBoneRoot();
        drawBone(root, k);
        selected_bone = new_selected_node;
    }
}

void ShowMainWindow(bool& show)
{
    ImguiWnd wnd("AE", &show);
    if (wnd.Collapsed)
        return;
    if (!sobj) {
        Fvector p;
        p.mad(Device.vCameraPosition, Device.vCameraDirection, 2.0f);
        u32 lvid = ai().level_graph().vertex_id(p);
        sobj = (CSE_ALifeDynamicObjectVisual*)(const_cast<CALifeSimulator&>(ai().alife()))
                   .spawn_item("script_object", p, lvid, ai().cross_table().vertex(lvid).game_vertex_id(), u16(-1));
        sobj->visual()->set_visual("dynamics\\barrels\\milk_can_01", true);
        return;
    }
    if (!obj) {
        obj = Level().Objects.net_Find(sobj->ID);
        if (obj)
            refresh_animations();
        return;
    }
    if (ImGui::Button("set stalker")) {
        obj->cNameVisual_set("characters\\neutral\\novice_petrukha");
        IKinematicsAnimated* ka = obj->Visual()->dcast_PKinematicsAnimated();
        if (ka) {
            refresh_animations();
            ka->PlayCycle("$editor");
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("set can")) {
        obj->cNameVisual_set("dynamics\\barrels\\milk_can_01");
    }
    ImGui::SameLine();
    if (ImGui::Button("set 16K20")) {
        obj->cNameVisual_set("16K20_cleaned");
    }
    ImGui::Text("visual");
    ImGui::SameLine();
    char buf[400];
    strcpy(buf, obj->cNameVisual().c_str());
    ImGui::InputText("##visual", buf, 400);
    ImGui::SameLine();
    if (ImGui::Button("...##choose_visual")) {
    }
    IKinematics* k = obj->Visual()->dcast_PKinematics();
    if (k)
        ShowKinematics(k);
    IKinematicsAnimated* ka = obj->Visual()->dcast_PKinematicsAnimated();
    if (ka)
        ShowAnimated(ka);
}

void ShowMotionWindow(u16 motion)
{
    char buf[400];
    IKinematicsAnimated* ka = obj->Visual()->dcast_PKinematicsAnimated();
    if (ka) {
        u16 count = ka->LL_MotionsSlotCount();
        if (motion >= count)
            sprintf(buf, "Motion [%d] - not available###Motion%d", motion, motion);
        else {
            const shared_motions& el = ka->LL_MotionsSlot(motion);
            sprintf(buf, "Motion [%d] %s###Motion%d", motion, el.id().c_str(), motion);
        }
    } else {
        sprintf(buf, "Motion [%d] - not available###Motion%d", motion, motion);
    }
    bool opened = true;
    ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    ImguiWnd wnd(buf, &opened);
    if (!opened)
        opened_motions.erase(motion);
    if (wnd.Collapsed)
        return;

    if (!ka)
        return;
    u16 count = ka->LL_MotionsSlotCount();
    if (motion >= count)
        return;
    static int cur = -1;
    if (ImGui_ListBox(
            "", &cur,
            [](void* data, int idx, const char** out_text) -> bool {
                xr_vector<shared_str>* anims = (xr_vector<shared_str>*)data;
                *out_text = (*anims)[idx].c_str();
                return true;
            },
            &animations[motion], animations[motion].size(), ImVec2(-1.0f, -1.0f))) {
        IKinematicsAnimated* ka = obj->Visual()->dcast_PKinematicsAnimated();
        if (ka)
            ka->PlayCycle(MotionID(motion, cur));
    }
}

void refresh_animations()
{
    animations.clear();
    IKinematicsAnimated* ka = obj->Visual()->dcast_PKinematicsAnimated();
    if (!ka)
        return;
    u16 count = ka->LL_MotionsSlotCount();
    animations.resize(count);
    for (u16 i = 0; i != count; i++) {
        shared_motions el = ka->LL_MotionsSlot(i);
        animations[i].resize(el.motion_map()->size());
        for (const auto& el : *(el.motion_map()))
            animations[i][el.second] = el.first;
    }
}

void showBoneProps()
{
    bool show = true;
    ImguiWnd wnd("Bone", &show);
    if (wnd.Collapsed)
        return;
    if (!obj)
        return;
    IKinematics* k = obj->Visual()->dcast_PKinematics();
    if (!k)
        return;
    if (k->LL_BoneCount() <= selected_bone)
        return;
    auto& data = k->LL_GetData(selected_bone);
    ImGui::Text("%s", data.name.data());
    ImGui::Separator();
    ImGui::Text("Scale");
    bool changed = false;
    if (ImGui::DragFloat("x##scale", &data.bind_transform.i.x, 0.01f))
        changed = true;
    if (ImGui::DragFloat("y##scale", &data.bind_transform.j.y, 0.01f))
        changed = true;
    if (ImGui::DragFloat("z##scale", &data.bind_transform.k.z, 0.01f))
        changed = true;
    if (changed)
        k->LL_GetData(k->LL_GetBoneRoot()).CalculateM2B(Fidentity);
}
