//---------------------------------------------------------------------------
#ifndef ESceneWayToolsH
#define ESceneWayToolsH

#include "ESceneCustomOTools.h"

class ESceneWayTool: public ESceneCustomOTool
{
	typedef ESceneCustomOTool inherited;
protected:
    // controls
    virtual void 		CreateControls			();
	virtual void 		RemoveControls			();
public:
						ESceneWayTool			():ESceneCustomOTool(OBJCLASS_WAY){;}
	// definition
    IC LPCSTR			ClassName				(){return "way";}
    IC LPCSTR			ClassDesc				(){return "Way";}
    IC int				RenderPriority			(){return 1;}

	int					RaySelectPoint			(int flag, float& distance, const Fvector& start, const Fvector& direction, BOOL bDistanceOnly);
	int					FrustumSelectPoint		(int flag, const CFrustum& frustum);
	void				SelectPoints			(bool flag);

    virtual void		Clear					(bool bSpecific=false){inherited::Clear(bSpecific);}
    // IO
    virtual bool   		IsNeedSave				(){return inherited::IsNeedSave();}
    virtual bool   		LoadStream            		(IReader&);
    virtual bool   		LoadLTX            		(CInifile&);
    virtual void   		SaveStream            	(IWriter&);
    virtual void   		SaveLTX            		(CInifile&);
    virtual bool		LoadSelection      		(IReader&);
    virtual void		SaveSelection      		(IWriter&);

    virtual void    	OnActivate  			();

    virtual CCustomObject* CreateObject			(LPVOID data, LPCSTR name);
};
//---------------------------------------------------------------------------
#endif
