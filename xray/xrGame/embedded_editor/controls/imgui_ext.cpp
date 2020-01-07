#include "stdafx.h"
#include "imgui_ext.h"
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

bool ImGui_ListBox(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data,
    int items_count, const ImVec2& size_arg)
{
    if (!ImGui::ListBoxHeader(label, size_arg))
        return false;

    // Assume all items have even height (= 1 line of text). If you need items of different or variable sizes you can
    // create a custom version of ListBox() in your code without using the clipper.
    bool value_changed = false;
    ImGuiListClipper clipper(items_count, ImGui::GetTextLineHeightWithSpacing()); // We know exactly our line height
                                                                                  // here so we pass it as a minor
                                                                                  // optimization, but generally you
                                                                                  // don't need to.
    while (clipper.Step())
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
            const bool item_selected = (i == *current_item);
            const char* item_text;
            if (!items_getter(data, i, &item_text))
                item_text = "*Unknown item*";

            ImGui::PushID(i);
            if (ImGui::Selectable(item_text, item_selected)) {
                *current_item = i;
                value_changed = true;
            }
            ImGui::PopID();
        }
    ImGui::ListBoxFooter();
    return value_changed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// from https://www.strchr.com/natural_sorting
////////////////////////////////////////////////////////////////////////////////////////////////////

int count_digits(const char* s)
{
    const char* p = s;
    while (isdigit(*p))
        p++;
    return (int)(p - s);
}

int compare_naturally(const void* a_ptr, const void* b_ptr)
{
    const char* a = (const char*)a_ptr;
    const char* b = (const char*)b_ptr;

    for (;;) {
        if (isdigit(*a) && isdigit(*b)) {
            int a_count = count_digits(a);
            int diff = a_count - count_digits(b);
            if (diff)
                return diff;
            diff = memcmp(a, b, a_count);
            if (diff)
                return diff;
            a += a_count;
            b += a_count;
        }
        if (*a != *b)
            return *a - *b;
        if (*a == '\0')
            return 0;
        a++, b++;
    }
}

namespace ImGui {

bool Plot2(const char* label, const PlotSource* data, int dataCount, float currentTime, float totalTime,
    ImVec2 graphSize, ChangedData* changes)
{
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);

    const ImVec2 label_size = CalcTextSize(label, NULL, true);
    graphSize = CalcItemSize(graphSize, CalcItemWidth(), label_size.y + (style.FramePadding.y * 2));
    const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(graphSize.x, graphSize.y));
    const ImRect inner_bb(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding);
    const ImRect total_bb(
        frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0));
    ItemSize(total_bb, style.FramePadding.y);
    if (!ItemAdd(total_bb, id, &frame_bb))
        return false;
    const bool hovered = ItemHoverable(inner_bb, id);
    if (hovered) {
        if (g.IO.MouseClicked[0]) {
            SetActiveID(id, window);
            FocusWindow(window);
        }
        if (g.IO.MouseReleased[0]) {
            ClearActiveID();
        }
    }

    bool changed = false;
    if (g.ActiveId == id) {
        if (g.IO.MouseClicked[0]) {
            changes->sourceIndex = -1;
            changes->keyIndex = (size_t)-1;
            for (int i = 0; i != dataCount; i++) {
                const auto& el = data[i];
                if (!el.visible)
                    continue;

                const float inv_scale = (el.scaleMin == el.scaleMax) ? 0.0f : (1.0f / (el.scaleMax - el.scaleMin));

                for (int j = 0; j != el.keys.size(); j++) {
                    const auto& key = el.keys[j];
                    auto coor = key;
                    coor.x = ImSaturate(coor.x / totalTime);
                    coor.y = 1.0f - ImSaturate((coor.y - el.scaleMin) * inv_scale);
                    coor = ImLerp(inner_bb.Min, inner_bb.Max, coor);

                    if (ImLengthSqr(g.IO.MousePos - coor) < 25.0f) {
                        changes->sourceIndex = i;
                        changes->keyIndex = j;
                    }
                }
            }
        }
        if (g.IO.MouseDown[0] && changes->sourceIndex != -1) {
            const auto& el = data[changes->sourceIndex];
            auto key = el.keys[changes->keyIndex];
            if (g.IO.MouseDownDuration[0] == 0.0f)
                changes->oldPos = key;
            ImVec2 invScale { totalTime / (inner_bb.Max.x - inner_bb.Min.x),
                -1.0f * (el.scaleMax - el.scaleMin) / (inner_bb.Max.y - inner_bb.Min.y) };
            if (g.IO.KeyCtrl)
                invScale.x = 0.0f;
            if (g.IO.KeyShift)
                invScale.y = 0.0f;
            auto delta = GetMouseDragDelta(0, 0.0f);
            changes->newPos = changes->oldPos + ImMul(delta, invScale);

            changed = true;
        }
    }

    RenderFrame(frame_bb.Min, frame_bb.Max, GetColorU32(ImGuiCol_FrameBg), true, style.FrameRounding);

    for (int i = 0; i != dataCount; i++) {
        const auto& el = data[i];
        if (!el.visible)
            continue;
        int count = el.samples.size();
        if (count <= 0)
            continue;

        int res_w = ImMin((int)graphSize.x, count) - 1;
        int item_count = count - 1;

        // Tooltip on hover
        int v_hovered = -1;
        if (hovered) {
            const float t
                = ImClamp((g.IO.MousePos.x - inner_bb.Min.x) / (inner_bb.Max.x - inner_bb.Min.x), 0.0f, 0.9999f);
            const int v_idx = (int)(t * item_count);
            IM_ASSERT(v_idx >= 0 && v_idx < count);

            const float v0 = el.samples[v_idx % count];
            const float v1 = el.samples[(v_idx + 1) % count];
            SetTooltip("%d: %8.4g\n%d: %8.4g", v_idx, v0, v_idx + 1, v1);

            v_hovered = v_idx;
        }

        const float t_step = 1.0f / (float)res_w;
        const float inv_scale = (el.scaleMin == el.scaleMax) ? 0.0f : (1.0f / (el.scaleMax - el.scaleMin));

        float v0 = el.samples[0];
        float t0 = 0.0f;
        // Point in the normalized space of our target rectangle
        ImVec2 tp0 = ImVec2(t0, 1.0f - ImSaturate((v0 - el.scaleMin) * inv_scale));

        const ImU32 col_base = el.color;
        const ImU32 col_hovered = GetColorU32(ImGuiCol_PlotLinesHovered);

        for (int n = 0; n < res_w; n++) {
            const float t1 = t0 + t_step;
            const int v1_idx = (int)(t0 * item_count + 0.5f);
            IM_ASSERT(v1_idx >= 0 && v1_idx < count);
            const float v1 = el.samples[(v1_idx + 1) % count];
            const ImVec2 tp1 = ImVec2(t1, 1.0f - ImSaturate((v1 - el.scaleMin) * inv_scale));

            // NB: Draw calls are merged together by the DrawList system. Still, we should render our batch are
            // lower level to save a bit of CPU.
            ImVec2 pos0 = ImLerp(inner_bb.Min, inner_bb.Max, tp0);
            ImVec2 pos1 = ImLerp(inner_bb.Min, inner_bb.Max, tp1);
            window->DrawList->AddLine(pos0, pos1, v_hovered == v1_idx ? col_hovered : col_base, 2.0f);
            t0 = t1;
            tp0 = tp1;
        }

        for (int j = 0; j != el.keys.size(); j++) {
            const auto& key = el.keys[j];
            auto coor = key;
            coor.x = ImSaturate(coor.x / totalTime);
            coor.y = 1.0f - ImSaturate((coor.y - el.scaleMin) * inv_scale);
            coor = ImLerp(inner_bb.Min, inner_bb.Max, coor);
            if (i == changes->sourceIndex && j == changes->keyIndex)
                window->DrawList->AddCircleFilled(coor, 5.0f, col_base);
            else
                window->DrawList->AddCircle(coor, 5.0f, col_base);
        }
    }

    // полоса текущего времени
    ImVec2 pos0 = ImLerp(inner_bb.Min, inner_bb.Max, ImVec2(currentTime / totalTime, 0.0f));
    ImVec2 pos1 = ImLerp(inner_bb.Min, inner_bb.Max, ImVec2(currentTime / totalTime, 1.0f));
    window->DrawList->AddLine(pos0, pos1, IM_COL32(0, 255, 0, 255), 1.0f);

    if (label_size.x > 0.0f)
        RenderText(ImVec2(frame_bb.Max.x + style.ItemInnerSpacing.x, inner_bb.Min.y), label);

    return changed;
}
}

bool ImGui_ColoredCheckBox(const char* label, bool* v, ImU32 color)
{
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    bool result = ImGui::Checkbox(label, v);
    ImGui::PopStyleColor();
    return result;
}
