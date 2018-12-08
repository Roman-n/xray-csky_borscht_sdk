#include "stdafx.h"
#include "../xrEngine/Environment.h"
#include "../xrServerEntities/LevelGameDef.h"
#include "../xrServerEntities/ShapeData.h"
#include "GamePersistent.h"
#include "controls/imgui_ext.h"
#include "embedded_editor.h"
#include "embedded_editor_helper.h"

Fvector convert(const Fvector& v);

namespace {

struct EnvModEditor : public Editor {
    static Editor* create() { return nullptr; }

    EnvModEditor(int index)
        : Editor(Editors::EnvModEdit)
        , m_index(index)
        , m_obj(GamePersistent().Environment().Modifiers[index])
    {
        updateTitle();
    }

    const int m_index;
    std::string m_title;
    bool m_changed = false;
    CEnvModifier& m_obj;

    bool draw() override
    {
        bool show = true;
        ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        ImguiWnd wnd(m_title.c_str(), &show);
        if (!show)
            return false;
        if (wnd.Collapsed)
            return true;

        if (ImGui::SliderFloat("##view_dist", &m_obj.far_plane, 0.001f, 10000.0f, "%.3f", 3.0f))
            m_changed = true;
        ImGui::SameLine();
        bool b = m_obj.use_flags.test(eViewDist);
        if (ImGui::Checkbox("view_dist##ena", &b)) {
            m_changed = true;
            m_obj.use_flags.set(eViewDist, b);
        }

        if (ImGui::ColorEdit3("##fog_color", (float*)&m_obj.fog_color))
            m_changed = true;
        ImGui::SameLine();
        b = m_obj.use_flags.test(eFogColor);
        if (ImGui::Checkbox("fog_color##ena", &b)) {
            m_changed = true;
            m_obj.use_flags.set(eFogColor, b);
        }

        if (ImGui::SliderFloat("##fog_density", &m_obj.fog_density, 0.0f, 10.0f))
            m_changed = true;
        ImGui::SameLine();
        b = m_obj.use_flags.test(eFogDensity);
        if (ImGui::Checkbox("fog_density##ena", &b)) {
            m_changed = true;
            m_obj.use_flags.set(eFogDensity, b);
        }

        if (ImGui::ColorEdit3("##ambient", (float*)&m_obj.ambient))
            m_changed = true;
		ImGui::SameLine();
		b = m_obj.use_flags.test(eAmbientColor);
		if (ImGui::Checkbox("ambient##ena", &b)) {
			m_changed = true;
			m_obj.use_flags.set(eAmbientColor, b);
		}

        Fvector temp;
        temp = convert(m_obj.sky_color);
		if (ImGui::ColorEdit3("##sky_color", (float*)&temp)) {
			m_changed = true;
			m_obj.sky_color = convert(temp);
		}
		ImGui::SameLine();
		b = m_obj.use_flags.test(eSkyColor);
		if (ImGui::Checkbox("sky_color##ena", &b)) {
			m_changed = true;
			m_obj.use_flags.set(eSkyColor, b);
		}

        if (ImGui::ColorEdit3("##hemi_color", (float*)&m_obj.hemi_color))
            m_changed = true;
		ImGui::SameLine();
		b = m_obj.use_flags.test(eHemiColor);
		if (ImGui::Checkbox("hemi_color##ena", &b)) {
			m_changed = true;
			m_obj.use_flags.set(eHemiColor, b);
		}

        return true;
    }

    void updateTitle()
    {
        m_title = (m_changed ? "*" : "")
            + (m_obj.shape_type == CShapeData::cfNone ? "NightVison" : ("Env Mod" + std::to_string(m_index)))
            + u8"###EnvMod" + std::to_string(m_index);
    }
};

EditorRegistrator regEdit(Editors::EnvModEdit, &EnvModEditor::create);

struct EnvModListModel : public Editor {
    static Editor* create() { return new EnvModListModel(); }

    EnvModListModel()
        : Editor(Editors::PpList)
        , m_modifiers(GamePersistent().Environment().Modifiers)
    {
    }

    xr_vector<CEnvModifier>& m_modifiers;

    std::vector<std::string> m_names;
    int m_cur = -1;

    bool draw() override
    {
        bool show = true;
        ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        ImguiWnd wnd(u8"Env Mods", &show);
        if (!show)
            return false;
        if (wnd.Collapsed)
            return true;

        updateNames();
        if (ImGui_ListBox(
                "", &m_cur,
                [](void* data, int idx, const char** out_text) -> bool {
                    auto names = (std::vector<std::string>*)data;
                    *out_text = (*names)[idx].c_str();
                    return true;
                },
                &m_names, m_names.size(), ImVec2(-1.0f, -1.0f))) {
            if (!editorExists([=](Editor* e) {
                    if (e->type() != Editors::EnvModEdit)
                        return false;
                    EnvModEditor* eme = (EnvModEditor*)e;
                    return eme->m_index == m_cur;
                }))
                showEditor(new EnvModEditor(m_cur));
        }
        return true;
    }

    void updateNames()
    {
        m_names.resize(m_modifiers.size());
        for (size_t i = 0; i != m_modifiers.size(); i++) {
            const auto& el = m_modifiers[i];
            std::string name
                = el.shape_type == CShapeData::cfNone ? "Nightvision" : std::string("Env Mod ") + std::to_string(i);
            m_names[i] = name;
        }
    }
};

EditorRegistrator regList(Editors::EnvModList, &EnvModListModel::create);
}
