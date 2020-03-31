#ifndef AnimationPathH
#define AnimationPathH

#include "../../../Layers/xrRender/FVF.h"

class COMotion;

ECORE_API class CAnimationPath
{
    struct AnmKey
    {
        Fvector pos;
        float time;

        void set(Fvector& P, float t) { pos = P; time = t; }
    };

    xr_vector<AnmKey>   m_anm_keys;
    xr_vector<FVF::L>   m_anm_path;

    public:
    CAnimationPath()
        : m_anm_path(NULL)
    { }
    CAnimationPath(COMotion* mot)
        : m_anm_path(NULL)
    { Build(mot); }

    void Clear();
    void Build(COMotion* mot);

    void Render();
};

#endif
