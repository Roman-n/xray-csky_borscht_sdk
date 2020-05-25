#include "stdafx.h"
#include "../../Include/xrRender/IEditDetailsMask.h"
#include "embedded_editor.h"
#include "embedded_editor_helper.h"

namespace {
struct DetailsEditor : public Editor {
    static Editor* create() { return new DetailsEditor(); }

    DetailsEditor()
        : Editor(Editors::Details)
    {
    }

    void refresh()
    {
        m_mode = ::Render->editDetailsMask()->mode();
        m_changed = ::Render->editDetailsMask()->changed();
        m_useMask = ::Render->editDetailsMask()->useMask();
    }

    void setMode(MaskEditModes mode) { ::Render->editDetailsMask()->setMode(mode); }

    void setUseMask(bool useMask) { ::Render->editDetailsMask()->setUseMask(useMask); }

    void save() { ::Render->editDetailsMask()->save(); }

    MaskEditModes m_mode = MaskEditModes::None;
    bool m_changed = false;
    bool m_useMask = false;

    bool draw() override
    {
        refresh();
        bool show = true;
        ImguiWnd wnd(m_changed ? u8"Details*###Details" : u8"Details###Details", &show);
        if (!show)
            return false;
        if (wnd.Collapsed)
            return true;

        bool b = m_useMask;
        if (ImGui::Checkbox(u8"использовать маску", &b))
            setUseMask(b);
        b = m_mode == MaskEditModes::ClearByCamera;
        if (ImGui::Checkbox(u8"Протаптывать дорожки", &b))
            setMode(b ? MaskEditModes::ClearByCamera : MaskEditModes::None);
        b = m_mode == MaskEditModes::FillByCamera;
        if (ImGui::Checkbox(u8"Затаптывать дорожки", &b))
            setMode(b ? MaskEditModes::FillByCamera : MaskEditModes::None);

        if (ImGui::Button(u8"Save"))
            save();

        return true;
    }
};

EditorRegistrator simulationRegister(Editors::Details, &DetailsEditor::create);

}
