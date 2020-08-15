#include "stdafx.h"
#include "utils.h"

void Detach(vecFace* S, vecVertex& vertices)
{
	map_v2v			verts;
	verts.clear		();
	
	// Collect vertices
	for (vecFaceIt F=S->begin(); F!=S->end(); ++F)
	{
		for (int i=0; i<3; ++i) 
		{
			Vertex*		V=(*F)->v[i];
			Vertex*		VC;
			map_v2v_it	W=verts.find(V);	// iterator
			
			if (W==verts.end()) 
			{	// where is no such-vertex
				VC = V->CreateCopy_NOADJ( vertices );	// make copy
				verts.insert(mk_pair(V, VC));
			} else 
			{
				// such vertex(key) already exists - update its adjacency
				VC = W->second;
			}
			VC->prep_add		(*F);
			V->prep_remove		(*F);
			(*F)->v[i]=VC;
		}
	}
	// vertices are already registered in container
	// so we doesn't need "vers" for this time
	verts.clear	();
}
