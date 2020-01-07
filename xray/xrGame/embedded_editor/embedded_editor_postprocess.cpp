#include "stdafx.h"
#include "../Actor.h"
#include "../ActorEffector.h"
#include "../PostprocessAnimator.h"
#include "controls/imgui_ext.h"
#include "embedded_editor.h"
#include "embedded_editor_helper.h"

namespace {

class CEditablePostprocessAnimator : public CPostprocessAnimator
{
public:
    CEditablePostprocessAnimator()
        : CPostprocessAnimator(10000, true)
    {
        bFreeOnRemove = false;
    }
    ~CEditablePostprocessAnimator()
    {
        if (playing())
            stop();
    }
    void play()
    {
        if (!playing()) {
            m_bStop = false;
            m_factor = 1.0f;
            fLifeTime = 100000.0f;
            g_actor->Cameras().AddPPEffector(this);
            m_position = 0.0f;
        }
        m_pause = false;
    }
    void pause() { m_pause = !m_pause; }
    void stop()
    {
        Stop(1.0f);
        m_position = 0.0f;
        g_actor->Cameras().RemovePPEffector(this);
    }
    float position() const { return m_position; }
    void setPosition(float pos)
    {
        if (!playing()) {
            play();
            pause();
        }
        m_position = pos;
    }
    bool playing() const { return g_actor->Cameras().GetPPEffector(this); }

    CEnvelope* envelope(int i) const
    {
        switch (i) {
        case 0:
        case 1:
        case 2:
            return m_Params[pp_base_color]->envelope(i);
        case 3:
        case 4:
        case 5:
            return m_Params[pp_add_color]->envelope(i - 3);
        case 6:
        case 7:
        case 8:
            return m_Params[pp_gray_color]->envelope(i - 6);
        case 9:
            return m_Params[pp_gray_value]->envelope(0);
        case 10:
            return m_Params[pp_blur]->envelope(0);
        case 11:
            return m_Params[pp_dual_h]->envelope(0);
        case 12:
            return m_Params[pp_dual_v]->envelope(0);
        case 13:
            return m_Params[pp_noise_i]->envelope(0);
        case 14:
            return m_Params[pp_noise_g]->envelope(0);
        case 15:
            return m_Params[pp_noise_f]->envelope(0);
        case 16:
            return m_Params[pp_fish_eye]->envelope(0);
        case 17:
            return m_Params[pp_vignette_radius]->envelope(0);
        case 18:
            return m_Params[pp_vignette_softness]->envelope(0);
        }
        return nullptr;
    }

    BOOL Process(SPPInfo& PPInfo) override
    {
        if (m_bCyclic)
            fLifeTime = 100000;

        CEffectorPP::Process(PPInfo);

        if (!m_pause)
            m_position += Device.fTimeDelta;
        if (m_bCyclic && m_position > f_length)
            m_position = 0.0f;

        Update(m_position);

        VERIFY(_valid(m_factor));
        VERIFY(_valid(m_factor_speed));
        VERIFY(_valid(m_dest_factor));
        if (m_bStop)
            m_factor -= Device.fTimeDelta * m_factor_speed;
        else
            m_factor += m_factor_speed * Device.fTimeDelta * (m_dest_factor - m_factor);
        clamp(m_factor, 0.0001f, 1.0f);
        VERIFY(_valid(m_factor));
        VERIFY(_valid(m_factor_speed));

        m_EffectorParams.color_base += pp_identity.color_base;
        m_EffectorParams.color_gray += pp_identity.color_gray;
        m_EffectorParams.color_add += pp_identity.color_add;
        if (0 == m_Params[pp_noise_i]->get_keys_count()) {
            m_EffectorParams.noise.intensity = pp_identity.noise.intensity;
        }
        if (0 == m_Params[pp_noise_g]->get_keys_count()) {
            m_EffectorParams.noise.grain = pp_identity.noise.grain;
        }
        if (0 == m_Params[pp_noise_f]->get_keys_count()) {
            m_EffectorParams.noise.fps = pp_identity.noise.fps;
        } else
            m_EffectorParams.noise.fps *= 100.0f;

        PPInfo.lerp(pp_identity, m_EffectorParams, m_factor);

        if (PPInfo.noise.grain <= 0.0f) {
            R_ASSERT3(0, "noise.grain cant be zero! see postprocess", *m_Name);
        }

        if (fsimilar(m_factor, 0.0001f, EPS_S))
            return FALSE;

        return TRUE;
    }

private:
    float m_position = 0.0f;
    bool m_pause = false;
};

struct PostprocessEditor : public Editor {
    static Editor* create() { return nullptr; }

    PostprocessEditor(const std::string& name)
        : Editor(Editors::PpEdit)
        , m_name(name)
        , m_anim(xr_new<CEditablePostprocessAnimator>())
    {
        updateTitle();
        m_anim->Load(m_name.c_str());
        m_data.resize(ENVELOPE_COUNT);
        for (int i = 0; i != ENVELOPE_COUNT; i++)
            m_data[i] = m_anim->envelope(i);

        float step = m_anim->GetLength() / SAMPLE_COUNT;
        m_plotData.reserve(ENVELOPE_COUNT);
        m_plotData.push_back({ u8"Base Color: Red", getSamples(m_data[0], SAMPLE_COUNT, step), IM_COL32(255, 0, 0, 255),
            0.0f, 1.0f, getKeys(m_data[0]), true });
        m_plotData.push_back({ u8"Base Color: Green", getSamples(m_data[1], SAMPLE_COUNT, step),
            IM_COL32(0, 255, 0, 255), 0.0f, 1.0f, getKeys(m_data[1]), true });
        m_plotData.push_back({ u8"Base Color: Blue", getSamples(m_data[2], SAMPLE_COUNT, step),
            IM_COL32(0, 0, 255, 255), 0.0f, 1.0f, getKeys(m_data[2]), true });

        m_plotData.push_back({ u8"Add Color: Red", getSamples(m_data[3], SAMPLE_COUNT, step), IM_COL32(255, 0, 0, 255),
            -1.0f, 1.0f, getKeys(m_data[3]), true });
        m_plotData.push_back({ u8"Add Color: Green", getSamples(m_data[4], SAMPLE_COUNT, step),
            IM_COL32(0, 255, 0, 255), -1.0f, 1.0f, getKeys(m_data[4]), true });
        m_plotData.push_back({ u8"Add Color: Blue", getSamples(m_data[5], SAMPLE_COUNT, step), IM_COL32(0, 0, 255, 255),
            -1.0f, 1.0f, getKeys(m_data[5]), true });

        m_plotData.push_back({ u8"Gray Color: Red", getSamples(m_data[6], SAMPLE_COUNT, step), IM_COL32(255, 0, 0, 255),
            0.0f, 1.0f, getKeys(m_data[6]), true });
        m_plotData.push_back({ u8"Gray Color: Green", getSamples(m_data[7], SAMPLE_COUNT, step),
            IM_COL32(0, 255, 0, 255), 0.0f, 1.0f, getKeys(m_data[7]), true });
        m_plotData.push_back({ u8"Gray Color: Blue", getSamples(m_data[8], SAMPLE_COUNT, step),
            IM_COL32(0, 0, 255, 255), 0.0f, 1.0f, getKeys(m_data[8]), true });
        m_plotData.push_back({ u8"Gray Value", getSamples(m_data[9], SAMPLE_COUNT, step),
            ImGui::GetColorU32(ImGuiCol_PlotLines), 0.0f, 2.0f, getKeys(m_data[9]), true });

        m_plotData.push_back({ u8"Blur", getSamples(m_data[10], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f), 0.0f, 0.2f, getKeys(m_data[10]), true });
        m_plotData.push_back({ u8"Duality H", getSamples(m_data[11], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(2 / 7.0f, 0.6f, 0.6f), 0.0f, 0.05f, getKeys(m_data[11]), true });
        m_plotData.push_back({ u8"Duality V", getSamples(m_data[12], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(3 / 7.0f, 0.6f, 0.6f), 0.0f, 0.05f, getKeys(m_data[12]), true });

        m_plotData.push_back({ u8"Noise Intensity", getSamples(m_data[13], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(4 / 7.0f, 0.6f, 0.6f), 0.0f, 2.0f, getKeys(m_data[13]), true });
        m_plotData.push_back({ u8"Noise Granularity", getSamples(m_data[14], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(5 / 7.0f, 0.6f, 0.6f), 0.0f, 5.0f, getKeys(m_data[14]), true });
        m_plotData.push_back({ u8"Noise Frequency", getSamples(m_data[15], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(6 / 7.0f, 0.6f, 0.6f), 0.0f, 40.0f, getKeys(m_data[15]), true });

        m_plotData.push_back({ u8"Fish Eye Intensity", getSamples(m_data[16], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(1.5f / 7.0f, 0.6f, 0.6f), -5.0f, 5.0f, getKeys(m_data[16]), true });
        m_plotData.push_back({ u8"Vignette Radius", getSamples(m_data[17], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(2.5f / 7.0f, 0.6f, 0.6f), 0.0f, 1.0f, getKeys(m_data[17]), true });
        m_plotData.push_back({ u8"Vignette Softness", getSamples(m_data[18], SAMPLE_COUNT, step),
            (ImU32)ImColor::HSV(3.5 / 7.0f, 0.6f, 0.6f), 0.0f, 1.0f, getKeys(m_data[18]), true });
    }

    std::vector<float> getSamples(CEnvelope* e, int count, float step)
    {
        std::vector<float> result(count);
        for (int i = 0; i != count; i++)
            result[i] = e->Evaluate(i * step);
        return result;
    }

    std::vector<ImVec2> getKeys(CEnvelope* e)
    {
        std::vector<ImVec2> result;
        result.reserve(e->keys.size());
        for (auto* key : e->keys)
            result.emplace_back(key->time, key->value);
        return result;
    }

    void setChanged(bool value)
    {
        if (value == m_changed)
            return;
        m_changed = value;
        updateTitle();
    }

    void updateTitle() { m_title = (m_changed ? "*" : "") + m_name + u8"###" + m_name; }

    const std::string m_name;
    std::string m_title;
    std::unique_ptr<CEditablePostprocessAnimator> m_anim;
    const int SAMPLE_COUNT = 100;
    const int ENVELOPE_COUNT = 19;
    std::vector<CEnvelope*> m_data;
    std::vector<ImGui::PlotSource> m_plotData;
    bool m_changed = false;
    ImGui::ChangedData m_changes { -1, (size_t)-1 };

    bool draw() override
    {
        bool show = true;
        ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        ImguiWnd wnd(m_title.c_str(), &show);
        if (!show)
            return false;
        if (wnd.Collapsed)
            return true;

        ImGui::Columns(2);

        int newSourceSelected = -1;
        int newKeySelected = -1;
        for (size_t i = 0, count = m_plotData.size(); i != count; i++) {
            auto& el = m_plotData[i];
            ImGui::PushID(el.name);
            ImGui::PushStyleColor(ImGuiCol_Text, el.color);
            ImGui::Checkbox("##Visible", &el.visible);
            ImGui::SameLine();
            bool b = ImGui::TreeNodeEx(el.name, m_changes.sourceIndex == 0 ? ImGuiTreeNodeFlags_Selected : 0);
            if (ImGui::IsItemClicked())
                newSourceSelected = i;
            ImGui::PopStyleColor();
            if (b) {
                for (int iKey = 0; iKey != el.keys.size(); iKey++) {
                    ImGui::TreeNodeEx((void*)(intptr_t)iKey,
                        ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen
                            | (m_changes.keyIndex == 0 ? ImGuiTreeNodeFlags_Selected : 0),
                        "Key %d", iKey);
                    if (ImGui::IsItemClicked())
                        newKeySelected = iKey + (i << 16);
                }
                if (ImGui::Button(u8"+")) {
                    CEnvelope* e = m_data[i];
                    newKeySelected = e->InsertKey(m_anim->position(), el.scaleMax);
                    newSourceSelected = i;
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        if (newSourceSelected != -1 && newSourceSelected != m_changes.sourceIndex) {
            m_changes.sourceIndex = newSourceSelected;
            m_changes.keyIndex = -1;
        }
        if (newKeySelected != -1) {
            m_changes.keyIndex = newKeySelected & 0xFFFF;
            m_changes.sourceIndex = newSourceSelected >> 16;
        }

        ImGui::NextColumn();
        ImGui::PushItemWidth(-1.0f);
        if (ImGui::Plot2(
                "##empty", &m_plotData[0], 19, m_anim->position(), m_anim->GetLength(), ImVec2(-1, -50), &m_changes)) {
            CEnvelope* e = m_data[m_changes.sourceIndex];
            auto key = e->keys[m_changes.keyIndex];
            key->time = m_changes.newPos.x;
            key->value = m_changes.newPos.y;

            float step = m_anim->GetLength() / SAMPLE_COUNT;
            m_plotData[m_changes.sourceIndex].samples = getSamples(e, SAMPLE_COUNT, step);
            m_plotData[m_changes.sourceIndex].keys = getKeys(e);
        }
        if (ImGui::BeginPopupContextItem("menu")) {
			if (ImGui::MenuItem("Add Key")) {

			}
			ImGui::EndPopup();
        }

        float position = m_anim->position();
        char buf[32];
        sprintf(buf, "%%.3f/%.3f", m_anim->GetLength());
        if (ImGui::SliderFloat("", &position, 0.0f, m_anim->GetLength(), buf))
            m_anim->setPosition(position);
        ImGui::PopItemWidth();

        // ImGui::NextColumn();
        // if (m_changes.sourceIndex != -1) {
        //    ImGui::PushItemWidth(-1.0f);
        //    ImGui::Text("--- Envelope ---");
        //    CEnvelope* e = m_data[m_changes.sourceIndex];
        //    ImGui::Text("Behavior0");
        //    ImGui::Combo("##behavior0", &e->behavior[0], "RESET\0CONSTANT\0REPEAT\0OSCILLATE\0OFFSET\0LINEAR\0");
        //    ImGui::Text("Behavior1");
        //    ImGui::Combo("##behavior1", &e->behavior[1], "RESET\0CONSTANT\0REPEAT\0OSCILLATE\0OFFSET\0LINEAR\0");
        //    if (m_changes.keyIndex != -1) {
        //        ImGui::Spacing();
        //        ImGui::Text("------ Key -----");
        //        auto key = e->keys[m_changes.keyIndex];
        //        bool changedKey = false;
        //        ImGui::Text("Value");
        //        if (ImGui::DragFloat("##Value", &key->value, 0.05f))
        //            changedKey = true;
        //        ImGui::Text("Time");
        //        if (ImGui::DragFloat("##Time", &key->time, 0.05f))
        //            changedKey = true;
        //        ImGui::Text("Shape");
        //        int shape = key->shape;
        //        if (ImGui::Combo("##Shape", &shape, "TCB\0HERM\0BEZI\0LINE\0STEP\0BEZ2\0")) {
        //            key->shape = shape;
        //            changedKey = true;
        //        }
        //        switch (shape) {
        //        case SHAPE_TCB:
        //            ImGui::Text("Tension");
        //            if (ImGui::DragFloat("##Tension", &key->tension, 0.05f))
        //                changedKey = true;
        //            ImGui::Text("Continuity");
        //            if (ImGui::DragFloat("##Continuity", &key->continuity, 0.05f))
        //                changedKey = true;
        //            ImGui::Text("Bias");
        //            if (ImGui::DragFloat("##Bias", &key->bias, 0.05f))
        //                changedKey = true;
        //            break;
        //        case SHAPE_HERM:
        //        case SHAPE_BEZI:
        //            ImGui::Text("Param 0");
        //            if (ImGui::DragFloat("##Param0", &key->param[0], 0.05f))
        //                changedKey = true;
        //            ImGui::Text("Param 1");
        //            if (ImGui::DragFloat("##Param1", &key->param[1], 0.05f))
        //                changedKey = true;
        //            break;
        //        case SHAPE_BEZ2:
        //            ImGui::Text("Param 0");
        //            if (ImGui::DragFloat("##Param0", &key->param[0], 0.05f))
        //                changedKey = true;
        //            ImGui::Text("Param 1");
        //            if (ImGui::DragFloat("##Param1", &key->param[1], 0.05f))
        //                changedKey = true;
        //            ImGui::Text("Param 2");
        //            if (ImGui::DragFloat("##Param2", &key->param[2], 0.05f))
        //                changedKey = true;
        //            ImGui::Text("Param 3");
        //            if (ImGui::DragFloat("##Param3", &key->param[3], 0.05f))
        //                changedKey = true;
        //            break;
        //        }
        //        ImGui::PopItemWidth();
        //        if (changedKey) {
        //            float step = m_anim->GetLength() / SAMPLE_COUNT;
        //            m_plotData[m_changes.sourceIndex].samples = getSamples(e, SAMPLE_COUNT, step);
        //            m_plotData[m_changes.sourceIndex].keys = getKeys(e);
        //        }
        //    }
        //}
        ImGui::Columns(1);

        if (ImGui::Button(u8"Play"))
            m_anim->play();
        ImGui::SameLine();
        if (ImGui::Button(u8"Pause"))
            m_anim->pause();
        ImGui::SameLine();
        if (ImGui::Button(u8"Stop"))
            m_anim->stop();
		if (ImGui::Button(u8"Save"))
		{
			string_path path;
			FS.update_path(path, "$game_anims$", m_name.c_str());
			m_anim->Save(path);
			m_changed = false;
		}

        return true;
    }
};

EditorRegistrator regPpEdit(Editors::PpEdit, &PostprocessEditor::create);

struct PpListModel : public Editor {
    static Editor* create() { return new PpListModel(); }

    PpListModel()
        : Editor(Editors::PpList)
    {
        xr_vector<LPSTR>* list = FS.file_list_open("$game_anims$", "", FS_ListFiles);
        if (!list)
            return;
        m_files.resize(list->size());
        auto e = std::copy_if(
            list->begin(), list->end(), m_files.begin(), [](auto x) { return strstr(x, ".ppe") != nullptr; });
        m_files.resize(e - m_files.begin());
        std::sort(
            m_files.begin(), m_files.end(), [](auto a, auto b) { return compare_naturally(a.c_str(), b.c_str()) < 0; });
        FS.file_list_close(list);
    }

    std::vector<std::string> m_files;
    int m_cur = -1;

    bool draw() override
    {
        bool show = true;
        ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_FirstUseEver);
        ImguiWnd wnd(u8"Постпроцессы", &show);
        if (!show)
            return false;
        if (wnd.Collapsed)
            return true;

        if (ImGui_ListBox(
                "", &m_cur,
                [](void* data, int idx, const char** out_text) -> bool {
                    auto files = (xr_vector<std::string>*)data;
                    *out_text = (*files)[idx].c_str();
                    return true;
                },
                &m_files, m_files.size(), ImVec2(-1.0f, -1.0f))) {
            auto name = m_files[m_cur];
            if (!editorExists([name](Editor* e) {
                    if (e->type() != Editors::PpEdit)
                        return false;
                    PostprocessEditor* ppe = (PostprocessEditor*)e;
                    return ppe->m_name == name;
                }))
                showEditor(new PostprocessEditor(name));
        }
        return true;
    }
};

EditorRegistrator reg(Editors::PpList, &PpListModel::create);
}
