#pragma once

#include <functional>
#include <imgui.h>

/// Создать список заданного размера
bool ImGui_ListBox(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data,
    int items_count, const ImVec2& size_arg); // = ImVec2(0, 0)

int compare_naturally(const void* a_ptr, const void* b_ptr);

namespace ImGui {
struct PlotSource {
	const char* name;
    std::vector<float> samples;
    ImU32 color;
    float scaleMin;
    float scaleMax;
    std::vector<ImVec2> keys;
    bool visible;
};

struct ChangedData {
    int sourceIndex;
    size_t keyIndex;
    ImVec2 oldPos;
    ImVec2 newPos;
};

/// Рисует график
bool Plot2(const char* label, const PlotSource* data, int dataCount, float currentTime, float totalTime,
    ImVec2 graphSize, ChangedData* changes);
}

/// Чекбокс с цветныи текстом
bool ImGui_ColoredCheckBox(const char* label, bool* value, ImU32 color);
