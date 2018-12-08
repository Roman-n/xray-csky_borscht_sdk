#pragma once

struct ImVec2;

/// Создать список заданного размера
bool ImGui_ListBox(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data,
    int items_count, const ImVec2& size_arg); // = ImVec2(0, 0)

int compare_naturally(const void* a_ptr, const void* b_ptr);
