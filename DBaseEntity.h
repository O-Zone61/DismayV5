#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#include "DVector.h"
#include "Forward.h"

#define makeptr(cast, ptr, off)					((cast*)((unsigned long)ptr + (unsigned long)(off)))
#define getmember(cast, ptr, addValue)			(*makeptr(cast, ptr, addValue))
#define CallVirtual(type, base, index, ...)		((type)(*(unsigned long**)base)[index])(__VA_ARGS__)

#ifdef CSS
#define m_iAmmo				0x00
#define m_bIsTyping			0x00
#define m_vecMins			0x20
#define m_vecMaxs			0x2C
#define m_iEntIndex			0x4C
#define m_bLifeState		0x8F
#define m_iHealth			0x90
#define m_iTeam				0x98
#define m_vecAbsOrigin		0x25C
#define m_vecOrigin			0x28C
#define m_vecPredictedWorld	0x334
#endif

#define GARRYSMOD
#ifdef GARRYSMOD
#define CALCVIEW			334
#define SETVIEWANGLES		404
#define m_vecMins			0x20
#define m_vecMaxs			0x2C
#define m_iEntIndex			0x48 // 0x4C?
#define m_nRenderFX			0x54
#define m_nRenderMode		0x7C
#define m_bLifeState		0x8F
#define m_iHealth			0x90
#define m_iTeam				0x98
#define m_iPredictableID	0x9C
#define m_flVelocityX		0xF0
#define m_flVelocityY		0xF4
#define m_flVelocityZ		0xF8
#define m_nFlags			0x34C
#define m_bDormant			0x16A
//#define m_bDormant			0x17A // ????
//#define m_bDormant			0x172
#define m_vecAbsOrigin		0x25C
#define m_vecOrigin			0x28C
#define m_vecPredictedWorld	0x334
#define m_flFlags			0x34C
#define m_pszRealClassName	0x518
#define m_iSpeed			0xEE4
#define m_iFOV				0x1F7C
#define m_flMaxSpeed		0x2020
#define m_iOberserverMode	0x1FE4
#define m_entOberserver		0x1FE8
#define m_Hands				0x28D0
#define m_bIsTyping			0x28DA
//LocalPlayer() only
#define m_iAmmo				0x16D0
#define m_nTickBase			0x20A4
#define m_hGroundEntity		0x240
#endif // GARRYSMOD

class C_BaseEntity
{
public:
	inline int		EntIndex();
	inline int		Health();
	inline int		GetAmmo();
	inline int		GetTickCount();
	inline int		GetTeam();
	inline int*		GetTickCountPtr();
	inline bool		IsTyping();
	inline bool		Alive();
	inline bool		IsPlayer();
	inline bool		IsDormant();
	inline bool		IsValid();
	inline DVector	GetOrigin();
	inline DVector	GetPredOrigin();
	inline DVector	GetVelocity();
	inline C_BaseEntity* GetGroundEntity();
	inline int*		GetFlagPtr();
	inline int		GetFlags();
};

#endif // C_BASEENTITY_H