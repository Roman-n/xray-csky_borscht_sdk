#include "stdafx.h"
#pragma hdrstop

#include "ObjectAnimator.h"
#include "motion.h"

#ifdef _EDITOR
#include "AnimationPath.h"
#endif
 
bool motion_sort_pred	(COMotion* a, 	COMotion* b)	{	return a->name<b->name;}
bool motion_find_pred	(COMotion* a, 	shared_str b)	{	return a->name<b;}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CObjectAnimator::CObjectAnimator()
{
	bLoop			= false;
    m_Current		= 0;
    m_Speed			= 1.f;
	m_Name			= "";
#ifdef _EDITOR
	m_MotionPath	= NULL;
#endif
}

CObjectAnimator::~CObjectAnimator()
{	
	Clear				();
}

void CObjectAnimator::Clear()
{
	for(MotionIt m_it=m_Motions.begin(); m_it!=m_Motions.end(); m_it++)
		xr_delete		(*m_it);
	m_Motions.clear		();
    SetActiveMotion		(0);
}

void CObjectAnimator::SetActiveMotion(COMotion* mot)
{
	m_Current			= mot;
    if (m_Current) 		m_MParam.Set(m_Current);
	m_XFORM.identity	();

#ifdef _EDITOR
	if (m_Current) {
     	if (m_MotionPath)
        	m_MotionPath->Build(m_Current);
        else
        	m_MotionPath = xr_new<CAnimationPath>(m_Current);
    } else {
    	xr_delete(m_MotionPath);
    }
#endif
}

void CObjectAnimator::LoadMotions(LPCSTR fname)
{
	string_path			full_path;
	if (!FS.exist( full_path, "$level$", fname ))
		if (!FS.exist( full_path, "$game_anims$", fname )){
			#ifdef _EDITOR
			ELog.Msg(mtError, "Can't find motion file '%s'.", fname);
            return;
			#else
			Debug.fatal(DEBUG_INFO,"Can't find motion file '%s'.",fname);
			#endif
		}

    LPCSTR  ext			= strext(full_path);
    if (ext){
		Clear			();
    	if (0==xr_strcmp(ext,".anm")){
            COMotion* M	= xr_new<COMotion> ();
            if (M->LoadMotion(full_path)) m_Motions.push_back(M);
            else				FATAL("ERROR: Can't load motion. Incorrect file version.");
        }else if (0==xr_strcmp(ext,".anms")){
            IReader* F			= FS.r_open(full_path);
            u32 dwMCnt			= F->r_u32(); VERIFY(dwMCnt);
            for (u32 i=0; i<dwMCnt; i++){
                COMotion* M		= xr_new<COMotion> ();
                bool bRes		= M->Load(*F);
                if (!bRes)		FATAL("ERROR: Can't load motion. Incorrect file version.");
                m_Motions.push_back(M);
            }
            FS.r_close		(F);
        }
        std::sort(m_Motions.begin(),m_Motions.end(),motion_sort_pred);
    }
}

void CObjectAnimator::Load(const char * name)
{
	m_Name				= name;
	LoadMotions			(name); 
	SetActiveMotion		(0);
}

void CObjectAnimator::Update(float dt)
{
	if (m_Current){
		Fvector R,P;
		m_Current->_Evaluate(m_MParam.Frame(),P,R);
		m_MParam.Update	(dt,m_Speed,bLoop);
		m_XFORM.setXYZi	(R.x,R.y,R.z);
        m_XFORM.translate_over(P);
	}
}

COMotion* CObjectAnimator::Play(bool loop, LPCSTR name)
{
	if (name&&name[0]){
		MotionIt it = std::lower_bound(m_Motions.begin(),m_Motions.end(),name,motion_find_pred);
        if ((it!=m_Motions.end())&&(0==xr_strcmp((*it)->Name(),name))){
            bLoop 		= loop;
            SetActiveMotion(*it);
			m_MParam.Play	();
            return 		*it;
        }else{
        	#ifdef _EDITOR
            ELog.Msg(mtError, "OBJ ANIM::Cycle '%s' not found.", name);
            #else
            Debug.fatal	(DEBUG_INFO,"OBJ ANIM::Cycle '%s' not found.",name);
            #endif
            return NULL;
        }
    }else{
        if (!m_Motions.empty()){
            bLoop 		= loop;
            SetActiveMotion(m_Motions.front());
			m_MParam.Play	();
            return 		m_Motions.front();
        }else{
        	#ifdef _EDITOR
            ELog.Msg(mtError, "OBJ ANIM::Cycle '%s' not found.", name);
            #else
            Debug.fatal	(DEBUG_INFO,"OBJ ANIM::Cycle '%s' not found.",name);
            #endif
            return NULL;
        }
    }
}

void CObjectAnimator::Stop()
{
	SetActiveMotion		(0);
	m_MParam.Stop		();
}

float CObjectAnimator::GetLength		()
{
	if(!m_Current) return 0.0f;
	float res = m_Current->Length()/m_Current->FPS();
	return res; 
}

#ifdef _EDITOR
void CObjectAnimator::DrawPath()
{
	if(m_MotionPath)
    	m_MotionPath->Render();
}
#endif
