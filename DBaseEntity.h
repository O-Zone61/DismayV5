#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#include "DVector.h"
#include "DDismay.h"
#include "Forward.h"

extern DDismay* dismay;
#define makeptr(cast, ptr, off)					((cast*)((unsigned long)ptr + (unsigned long)(off)))
#define getmember(cast, ptr, addValue)			(*makeptr(cast, ptr, addValue))
#define CallVirtual(type, base, index, ...)		((type)(*(unsigned long**)base)[index])(__VA_ARGS__)

class IClientNetworkable;

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
#define CalcView			334
#define SetViewAngles		404
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
	int		EntIndex()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iEntIndex);
		};
	int		Health()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iHealth);
		};
	int		GetAmmo()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iAmmo);
		};
	int		GetTickCount()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_nTickBase);
		};
	int		GetTeam()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iTeam);
		};
	int*	GetTickCountPtr()
		{
			if(!this->IsValid()) return 0;
			return makeptr(int, this, m_nTickBase);
		};
	bool	IsTyping()
		{
			if(!this->IsValid()) return false;
			return getmember(bool, this, m_bIsTyping);
		};
	bool	Alive()
		{
			if(!this->IsValid()) return false;
			return getmember(bool, this, m_bLifeState);
		};
	bool IsPlayer()
		{
			if(!this->IsValid()) return false;
			player_info_s inf;
			int entindex;

			entindex = this->EntIndex();

			if(!dismay->m_pEngineClient->GetPlayerInfo(entindex, &inf))
				return false;
			return true;
		};
	unsigned char IsDormant()
		{
			if(!this->IsValid()) return true;
			IClientNetworkable* a = makeptr(IClientNetworkable, this, 0x8);
			typedef bool (__thiscall* IsDormantFn)(IClientNetworkable*); 

			return CallVirtual(IsDormantFn, a, 8, a);
		};
	bool IsValid()
		{
			if(!this)
				return false;
			return true;
		};
	DVector	GetOrigin()
		{
			if(!this->IsValid()) return DVector(-1000, -1000, -1000);
			return getmember(DVector, this, m_vecOrigin);
		};
	DVector	GetPredOrigin()
		{
			if(!this->IsValid()) return DVector(-1000, -1000, -1000);
			return getmember(DVector, this, m_vecAbsOrigin);
		};
	DVector GetVelocity()
		{
			if(!this->IsValid()) return DVector(-1000, -1000, -1000);
			return DVector(getmember(float, this, m_flVelocityX), getmember(float, this, m_flVelocityY), getmember(float, this, m_flVelocityZ));
		};
	C_BaseEntity* GetGroundEntity()
		{
			if(!this->IsValid()) return 0;
			return getmember(C_BaseEntity*, this, m_hGroundEntity);
		};
	int* GetFlagPtr()
		{
			if(!this->IsValid()) return 0;
			return makeptr(int, this, m_nFlags);
		};
	int GetFlags()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_nFlags);
		};
};

#endif // C_BASEENTITY_H