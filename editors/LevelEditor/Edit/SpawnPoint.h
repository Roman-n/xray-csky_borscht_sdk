//----------------------------------------------------
// file: rpoint.h
//----------------------------------------------------

#ifndef SpawnPointH
#define SpawnPointH

#define SPAWNPOINT_VERSION   			0x0018

#include "../../xrServerEntities/LevelGameDef.h"
#include "../../xrServerEntities/xrServer_Objects_abstract.h"
#include "CustomObject.h"

// refs
class CSE_Visual;
class CSE_Motion;
class CObjectAnimator;
class ISE_Abstract;
class CEnvModifier;
class IParticleCustom;

class CSpawnPoint : public CCustomObject
{
	typedef CCustomObject inherited;

    friend class    SceneBuilder;
public:                           
    class CLE_Visual
    {
    public:
        static xr_map<xr_string, xr_string> replaced_visuals;

    	CSE_Visual*		source;
        IRenderVisual*	visual;
        void 			OnChangeVisual			();
        void			StopAllAnimations		();
        void 			PlayAnimation			();
        void 			PlayAnimationFirstFrame	();
        void 			PlayAnimationLastFrame	();
        void 			PauseAnimation			();
    public:
						CLE_Visual		(CSE_Visual* src);
        virtual			~CLE_Visual		();
    };
    class CLE_Motion
    {
    public:
    	CSE_Motion*		source;
        CObjectAnimator*animator;
        void 			OnChangeMotion	();
        void 			PlayMotion		();
    public:
						CLE_Motion		(CSE_Motion* src);
        virtual			~CLE_Motion		();
    };
	struct SSpawnData: public ISE_AbstractLEOwner
	{
		CLASS_ID		m_ClassID;
        shared_str 		m_Profile;
		ISE_Abstract*	m_Data;
		CLE_Visual*		m_Visual;
        Flags8			m_flags;
		xr_vector<CLE_Visual*> m_VisualHelpers;
		IParticleCustom*m_IdleParticles; // for anomalies

        CLE_Motion*		m_Motion;
        CSpawnPoint*	m_owner;
        enum{ eSDTypeRespawn = (1<<0),};
        SSpawnData	(CSpawnPoint* o)
        {
			m_ClassID	= 0;
			m_Data		= 0;
            m_Visual	= 0;
            m_Motion	= 0;
			m_owner		= o;
			m_flags.zero();
			m_IdleParticles = 0;
        }
        ~SSpawnData	()
        {
        	Destroy	();
        }
        void			Create			(LPCSTR entity_ref);
        void			Destroy			();
        bool			Valid			(){return m_Data;}

        bool		    LoadStream		(IReader&);
        void		    SaveStream		(IWriter&);
        bool		    LoadLTX			(CInifile& ini, LPCSTR sect_name);
        void		    SaveLTX			(CInifile& ini, LPCSTR sect_name);

		bool 			ExportGame		(SExportStreams* F, CSpawnPoint* owner);

		void			FillProp		(LPCSTR pref, PropItemVec& values);

		void    		Render			(bool bSelected, const Fmatrix& parent,int priority, bool strictB2F);
		void    		OnFrame			();
		void __stdcall	OnAnimControlClick		(ButtonValue* value, bool& bModif, bool& bSafe);
		void __stdcall  OnParticleControlClick	(ButtonValue* value, bool& bModif, bool& bSafe);
        
		virtual void get_bone_xform				(LPCSTR name, Fmatrix& xform);
	};

	SSpawnData    	m_SpawnData;
	CCustomObject*	m_AttachedObject;

    EPointType		m_Type;
    shared_str		m_rpProfile;
    union{
    	struct{
		    u8					m_RP_TeamID;
		    u8					m_RP_Type;
			GameTypeChooser     m_GameType;
        };
        struct{
        	float	m_EM_Radius;
            float 	m_EM_Power;
            float	m_EM_ViewDist;
            u32		m_EM_FogColor;
            float	m_EM_FogDensity;
            u32		m_EM_AmbientColor;
            u32		m_EM_SkyColor;
            u32		m_EM_HemiColor;
            Flags16	m_EM_Flags;

            u8		m_EM_ShapeType;
            CEnvModifier* m_EM_Ptr;
        };
    };

    shared_str		SectionToEditor			(shared_str);
    shared_str		EditorToSection			(shared_str);
	void __stdcall	OnProfileChange			(PropValue* prop);
	void __stdcall	OnRPointTypeChange		(PropValue* prop);
    
	void __stdcall	OnEnvModFlagChange		(PropValue* prop);
	void __stdcall	OnFillChooseItems		(ChooseValue*);
    void __stdcall	OnFillRespawnItemProfile(ChooseValue*);
    bool 			OnAppendObject			(CCustomObject* object);
protected:
    virtual void 	SetPosition		(const Fvector& pos);
    virtual void 	SetRotation		(const Fvector& rot);
    virtual void 	SetScale		(const Fvector& scale);
public:
	                CSpawnPoint    	(LPVOID data, LPCSTR name);
    void            Construct   	(LPVOID data);
    virtual         ~CSpawnPoint   	();
    virtual bool	CanAttach		() {return true;}
    
	bool 			RefCompare		(LPCSTR ref);
    virtual LPCSTR	RefName			();

    bool			CreateSpawnData	(LPCSTR entity_ref);
    virtual bool	IsRender		();
	virtual void    Render      	( int priority, bool strictB2F );
	virtual bool    RayPick     	( float& distance,	const Fvector& start,	const Fvector& direction, SRayPickInfo* pinf = NULL );
    virtual bool 	FrustumPick		( const CFrustum& frustum );
	virtual bool    GetBox      	(Fbox& box);

	virtual void 	OnFrame			();
	virtual void	OnUpdateTransform();

	virtual void 	Select			(int  flag);

	virtual bool 	LoadStream		(IReader&);
	virtual bool 	LoadLTX			(CInifile& ini, LPCSTR sect_name);
	virtual void 	SaveStream		 (IWriter&);
	virtual void 	SaveLTX			(CInifile& ini, LPCSTR sect_name);

    virtual bool	ExportGame		(SExportStreams* data);

	virtual void	FillProp		(LPCSTR pref, PropItemVec& values);

    bool			AttachObject	(CCustomObject* obj);
    void			DetachObject	();
    
    virtual bool	OnChooseQuery	(LPCSTR specific);
};

#endif /*_INCDEF_Glow_H_*/

