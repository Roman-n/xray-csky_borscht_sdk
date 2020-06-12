#include	"stdafx.h"
#include	"ETools.h"

#pragma warning(disable:4267)

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  fdwReason, 
					  LPVOID lpReserved
					  )
{ 
	switch(fdwReason) {
		case DLL_PROCESS_ATTACH:
			//Debug._initialize	(false);
			//Core._initialize	("XRayEditorTools",0,FALSE);
			//FPU::m64r	();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			//Core._destroy();
			break;
	}
	return TRUE;
}

namespace ETOOLS{
	ETOOLS_API bool  __stdcall TestRayTriA(const Fvector& C, const Fvector& D, Fvector** p, float& u, float& v, float& range, bool bCull)
	{
		Fvector edge1, edge2, tvec, pvec, qvec;
		float det,inv_det;
		// find vectors for two edges sharing vert0
		edge1.sub(*p[1], *p[0]);
		edge2.sub(*p[2], *p[0]);
		// begin calculating determinant - also used to calculate U parameter
		pvec.crossproduct(D, edge2);
		// if determinant is near zero, ray lies in plane of triangle
		det = edge1.dotproduct(pvec);
		if (bCull){						// define TEST_CULL if culling is desired
			if (det < EPS)  return false;
			tvec.sub(C, *p[0]);							// calculate distance from vert0 to ray origin
			u = tvec.dotproduct(pvec);			// calculate U parameter and test bounds
			if (u < 0.0 || u > det) return false;
			qvec.crossproduct(tvec, edge1);				// prepare to test V parameter
			v = D.dotproduct(qvec);			// calculate V parameter and test bounds
			if (v < 0.0 || u + v > det) return false;
			range = edge2.dotproduct(qvec);		// calculate t, scale parameters, ray intersects triangle
			inv_det = 1.0f / det;
			range *= inv_det;
			u *= inv_det;
			v *= inv_det;
		}else{											// the non-culling branch
			if (det > -EPS && det < EPS) return false;
			inv_det = 1.0f / det;
			tvec.sub(C, *p[0]);							// calculate distance from vert0 to ray origin
			u = tvec.dotproduct(pvec)*inv_det;	// calculate U parameter and test bounds
			if (u < 0.0f || u > 1.0f)    return false;
			qvec.crossproduct(tvec, edge1);				// prepare to test V parameter
			v = D.dotproduct(qvec)*inv_det;	// calculate V parameter and test bounds
			if (v < 0.0f || u + v > 1.0f) return false;
			range = edge2.dotproduct(qvec)*inv_det;// calculate t, ray intersects triangle
		}
		return true;
	}
	//-- Ray-Triangle : 1st level of indirection --------------------------------
	ETOOLS_API bool  __stdcall TestRayTriB(const Fvector& C, const Fvector& D, Fvector* p, float& u, float& v, float& range, bool bCull)
	{
		Fvector edge1, edge2, tvec, pvec, qvec;
		float det,inv_det;
		// find vectors for two edges sharing vert0
		edge1.sub(p[1], p[0]);
		edge2.sub(p[2], p[0]);
		// begin calculating determinant - also used to calculate U parameter
		pvec.crossproduct(D, edge2);
		// if determinant is near zero, ray lies in plane of triangle
		det = edge1.dotproduct(pvec);
		if (bCull){						// define TEST_CULL if culling is desired
			if (det < EPS)  return false;
			tvec.sub(C, p[0]);							// calculate distance from vert0 to ray origin
			u = tvec.dotproduct(pvec);			// calculate U parameter and test bounds
			if (u < 0.0f || u > det) return false;
			qvec.crossproduct(tvec, edge1);				// prepare to test V parameter
			v = D.dotproduct(qvec);			// calculate V parameter and test bounds
			if (v < 0.0f || u + v > det) return false;
			range = edge2.dotproduct(qvec);		// calculate t, scale parameters, ray intersects triangle
			inv_det = 1.0f / det;
			range *= inv_det;
			u *= inv_det;
			v *= inv_det;
		}else{											// the non-culling branch
			if (det > -EPS && det < EPS) return false;
			inv_det = 1.0f / det;
			tvec.sub(C, p[0]);							// calculate distance from vert0 to ray origin
			u = tvec.dotproduct(pvec)*inv_det;	// calculate U parameter and test bounds
			if (u < 0.0f || u > 1.0f)    return false;
			qvec.crossproduct(tvec, edge1);				// prepare to test V parameter
			v = D.dotproduct(qvec)*inv_det;	// calculate V parameter and test bounds
			if (v < 0.0f || u + v > 1.0f) return false;
			range = edge2.dotproduct(qvec)*inv_det;// calculate t, ray intersects triangle
		}
		return true;
	}
	//-- Ray-Triangle(always return range) : 1st level of indirection --------------------------------
	ETOOLS_API bool  __stdcall TestRayTri2(const Fvector& C, const Fvector& D, Fvector* p, float& range)
	{
		Fvector edge1, edge2, tvec, pvec, qvec;
		float det,inv_det,u,v;

		// find vectors for two edges sharing vert0
		edge1.sub(p[1], p[0]);
		edge2.sub(p[2], p[0]);
		// begin calculating determinant - also used to calculate U parameter
		pvec.crossproduct(D, edge2);
		// if determinant is near zero, ray lies in plane of triangle
		det = edge1.dotproduct(pvec);

		if (_abs(det) < EPS_S)		{ range=-1; return false; }
		inv_det = 1.0f / det;
		tvec.sub(C, p[0]);					// calculate distance from vert0 to ray origin
		u = tvec.dotproduct(pvec)*inv_det;	// calculate U parameter and test bounds
		qvec.crossproduct(tvec, edge1);		// prepare to test V parameter
		range = edge2.dotproduct(qvec)*inv_det;// calculate t, ray intersects plane
		if (u < 0.0f || u > 1.0f)		return false;
		v = D.dotproduct(qvec)*inv_det;		// calculate V parameter and test bounds
		if (v < 0.0f || u + v > 1.0f) return false;
		return true;
	}

	ETOOLS_API Collector*				 __stdcall create_collector		()
	{
		return							xr_new<Collector>	();
	}
	ETOOLS_API void						 __stdcall destroy_collector		(Collector*& M)
	{
		xr_delete						(M);
	}
	ETOOLS_API void						 __stdcall collector_add_face_d	(Collector* CL, const Fvector& v0, const Fvector& v1, const Fvector& v2, u32 dummy)
	{
		CL->add_face					(v0,v1,v2,{dummy});
	}
	ETOOLS_API void						 __stdcall collector_add_face_pd	(Collector* CL, const Fvector& v0, const Fvector& v1, const Fvector& v2, u32 dummy, float eps)
	{
		CL->add_face_packed(v0, v1, v2, { dummy }, eps);
	}

	ETOOLS_API CollectorPacked*		__stdcall create_collectorp		(const Fbox &bb, int apx_vertices, int apx_faces)
	{
		return							xr_new<CollectorPacked>	(bb, apx_vertices, apx_faces);
	}
	ETOOLS_API void						 __stdcall destroy_collectorp		(CollectorPacked*& M)
	{
		xr_delete						(M);
	}
	//ETOOLS_API void						 __stdcall collectorp_add_face_d	(CDB::CollectorPacked_Game* CL, const Fvector& v0, const Fvector& v1, const Fvector& v2, u32 dummy)
	//{
	//	CL->add_face(v0, v1, v2, { dummy }, u32(-1));
	//}

	Collider	COL;

	ETOOLS_API Collider*		__stdcall get_collider	(){return &COL;}

	ETOOLS_API Model*			 __stdcall create_model_clp(CollectorPacked* CL)
	{
		return				create_model(CL->getV(), CL->getVS(), CL->getT(), CL->getTS());
	}

	ETOOLS_API Model*		 __stdcall create_model_cl	(Collector* CL)
	{
		return				create_model(CL->getV(), CL->getVS(), CL->getT(), CL->getTS());
	}
	ETOOLS_API Model*		 __stdcall create_model	(Fvector* V, int Vcnt, Tri* T, int Tcnt)
	{
		Model* M			= xr_new<Model> ();
		M->build			(V, Vcnt, T, Tcnt);
		return M;
	}
	ETOOLS_API void			 __stdcall destroy_model	(Model*& M)
	{
		xr_delete			(M);
	}
	ETOOLS_API Result*	 __stdcall r_begin	()	{	return COL.r_begin();		};
	ETOOLS_API Result*	 __stdcall r_end	()	{	return COL.r_end();			};
	ETOOLS_API int	 __stdcall r_count			()	{	return COL.r_count();		};
	ETOOLS_API void  __stdcall ray_options	(u32 flags)
	{
		COL.ray_options(flags);
	}
	ETOOLS_API void	 __stdcall ray_query	(const Model *m_def, const Fvector& r_start,  const Fvector& r_dir, float r_range)
	{
		COL.ray_query(m_def,r_start,r_dir,r_range);
	}
	ETOOLS_API void	 __stdcall ray_query_m	(const Fmatrix& inv_parent, const Model *m_def, const Fvector& r_start,  const Fvector& r_dir, float r_range)
	{
    	// transform
        Fvector S,D;
	    inv_parent.transform_tiny	(S,r_start);
    	inv_parent.transform_dir	(D,r_dir);
		ray_query					(m_def,S,D,r_range);
	}
	ETOOLS_API void  __stdcall box_options	(u32 flags)
	{
		COL.box_options(flags);
	}
	ETOOLS_API void	 __stdcall box_query	(const Model *m_def, const Fvector& b_center, const Fvector& b_dim)
	{
		COL.box_query(m_def,b_center,b_dim);
	}
	ETOOLS_API void	 __stdcall box_query_m	(const Fmatrix& inv_parent, const Model *m_def, const Fbox& src)
	{
    	Fbox dest;
		dest.xform(src,inv_parent);
        Fvector c,d;
        dest.getcenter(c);
        dest.getradius(d);
    	box_query(m_def,c,d);
	}
}

