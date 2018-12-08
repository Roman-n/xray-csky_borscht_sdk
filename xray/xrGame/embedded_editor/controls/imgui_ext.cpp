#include "stdafx.h"
#include "imgui_ext.h"
#include <imgui.h>

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
