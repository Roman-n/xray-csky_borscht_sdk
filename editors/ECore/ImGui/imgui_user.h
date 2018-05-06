/* ImGui extensions */

namespace ImGui
{
    static inline bool CollapsingPanel(const char* label, bool* p_open, ImGuiTreeNodeFlags flags = 0)
    {
        if(*p_open)
            flags |= ImGuiTreeNodeFlags_DefaultOpen;

        return *p_open = CollapsingHeader(label, flags);
    }
}
