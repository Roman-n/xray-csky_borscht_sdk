#pragma once

#include "Sound.h"

class SoundRender_NoSound : public CSound_manager_interface
{
    bool _initialize(int stage) override { return true; }
    void _clear() override { }

protected:
    void _create_data(ref_sound_data& S, LPCSTR fName, esound_type sound_type, int game_type) override { }
    void _destroy_data(ref_sound_data& S) override { }

public:
    void _restart() override { }
    BOOL i_locked() override { return FALSE; }
    void create(ref_sound& S, LPCSTR fName, esound_type sound_type, int game_type) override { }
    void attach_tail(ref_sound& S, LPCSTR fName) override { }
    void clone(ref_sound& S, const ref_sound& from, esound_type sound_type, int game_type) override { }
    void destroy(ref_sound& S) override { }
    void stop_emitters() override { }
    int pause_emitters(bool val) override { return 0; }

    void play(ref_sound& S, CObject* O, u32 flags = 0, float delay = 0.f) override { }
    void play_at_pos(ref_sound& S, CObject* O, const Fvector& pos, u32 flags = 0, float delay = 0.f) override { }
    void play_no_feedback(ref_sound& S, CObject* O, u32 flags = 0, float delay = 0.f, Fvector* pos = 0, float* vol = 0,
        float* freq = 0, Fvector2* range = 0) override
    {
    }
    void set_master_volume(float f = 1.f) override { }
    void set_geometry_env(IReader* I) override { }
    void set_geometry_som(IReader* I) override { }
    void set_geometry_occ(CDB::MODEL* M) override { }
    void set_handler(sound_event* E) override { }
    void update(const Fvector& P, const Fvector& D, const Fvector& N) override { }
    void statistic(CSound_stats* s0, CSound_stats_ext* s1) override { }
    float get_occlusion_to(const Fvector& hear_pt, const Fvector& snd_pt, float dispersion = 0.2f) override
    {
        return 0.0f;
    }
    void object_relcase(CObject* obj) override { }
    const Fvector& listener_position() override { return m_listener_position; }

private:
    Fvector m_listener_position;
};
