#include "stdafx.h"
#pragma hdrstop

#include "AnimationPath.h"
#include "motion.h"
#include "envelope.h"
#include "device.h"
#include "D3DUtils.h"

#pragma package(smart_init)

void CAnimationPath::Clear()
{
	m_anm_path.clear();
    m_anm_keys.clear();
}

void CAnimationPath::Build(COMotion* Motion)
{
    Clear();

    float fps 				= Motion->FPS();
    float min_t				= (float)Motion->FrameStart()/fps;
    float max_t				= (float)Motion->FrameEnd()/fps;

    Fvector 				T,r;
    u32 clr					= 0xffffffff;
    for (float t=min_t; (t<max_t)||fsimilar(t,max_t,EPS_L); t+=1/30.f){
        Motion->_Evaluate(t,T,r);

        FVF::L vtx;
        vtx.set(T, clr);
        m_anm_path.push_back(vtx);
    }

    CEnvelope* E 			= Motion->Envelope	();
    m_anm_keys.reserve      (E->keys.size());
    for (KeyIt k_it=E->keys.begin(); k_it!=E->keys.end(); k_it++){
        Motion->_Evaluate	((*k_it)->time,T,r);
        
        AnmKey key;
        key.set(T, (*k_it)->time);
        m_anm_keys.push_back(key);
    }
}

void CAnimationPath::Render()
{
	// may be more optimized using vertex buffer
	if(!m_anm_path.empty())
    {
		ref_geom geom;
    	geom.create				(FVF::F_L, RCache.Vertex.Buffer(),RCache.Index.Buffer());

        u32 v_offset;
        void* p = RCache.Vertex.Lock(m_anm_path.size(), geom->vb_stride, v_offset);
        Memory.mem_copy			(p, &*m_anm_path.begin(), m_anm_path.size()*sizeof(FVF::L));
        RCache.Vertex.Unlock	(m_anm_path.size(), geom->vb_stride);

    	Device.SetShader		(Device.m_WireShader);
    	RCache.set_xform_world	(Fidentity);
    	RCache.set_Geometry		(geom);
    	RCache.Render			(D3DPT_LINESTRIP, v_offset, m_anm_path.size()-1);

    	geom.destroy();
    }
    xr_vector<AnmKey>::iterator it, end;
    for(it = m_anm_keys.begin(), end = m_anm_keys.end(); it != end; it++) {
        if (Device.m_Camera.GetPosition().distance_to_sqr((*it).pos)<50.f*50.f) {
            DU_impl.DrawCross	((*it).pos,0.1f,0.1f,0.1f, 0.1f,0.1f,0.1f, 0xffffffff,false);
            DU_impl.OutText		((*it).pos,AnsiString().sprintf("K: %3.3f",(*it).time).c_str(),0xffffffff,0x00000000);
        }
    }
}
