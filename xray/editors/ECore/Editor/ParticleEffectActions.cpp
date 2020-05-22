//---------------------------------------------------------------------------
#include "stdafx.h"
#pragma hdrstop

#include "ParticleEffectActions.h"

_CreateEAction 	pCreateEAction=0;

#ifndef PARTICLE_EDITOR
void 	EParticleAction::FillProp	(PropItemVec& items, LPCSTR pref, u32 clr) { }
void EParticleAction::Load(IReader& F) { }
void EParticleAction::Save(IWriter& F) { }
void EParticleAction::Load2(CInifile& ini, const shared_str& sect) { }
void EParticleAction::Save2(CInifile& ini, const shared_str& sect) { }
void EParticleAction::Render(const Fmatrix& parent) { }
#endif