#include "Garry/dismay_ccliententitylist.h"
#include "DBaseEntity.h"
#include "DDismay.h"
#include "DVector.h"

extern DDismay* dismay;

int C_BaseEntity::EntIndex()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_iEntIndex);
};
int C_BaseEntity::Health()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_iHealth);
};
int C_BaseEntity::GetAmmo()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_iAmmo);
};
int C_BaseEntity::GetTickCount()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_nTickBase);
};
int C_BaseEntity::GetTeam()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_iTeam);
};
int* C_BaseEntity::GetTickCountPtr()
{
	if(!this->IsValid()) return 0;
	return makeptr(int, this, m_nTickBase);
};
bool C_BaseEntity::IsTyping()
{
	if(!this->IsValid()) return false;
	return getmember(bool, this, m_bIsTyping);
};
bool C_BaseEntity::Alive()
{
	if(!this->IsValid()) return false;
	return getmember(bool, this, m_bLifeState);
};
bool C_BaseEntity::IsPlayer()
{
	if(!this->IsValid()) return false;
	player_info_s inf;
	int entindex;

	entindex = this->EntIndex();

	if(!dismay->m_pEngineClient->GetPlayerInfo(entindex, &inf))
		return false;
	return true;
};
bool C_BaseEntity::IsDormant()
{
	if(!this->IsValid()) return true;
	IClientNetworkable* a = makeptr(IClientNetworkable, this, 0x8);
	typedef bool (__thiscall* IsDormantFn)(IClientNetworkable*); 

	return CallVirtual(IsDormantFn, a, 8, a);
};
bool C_BaseEntity::IsValid()
{
	return this != 0;
};
DVector C_BaseEntity::GetOrigin()
{
	if(!this->IsValid()) return DVector(-1000, -1000, -1000);
	return getmember(DVector, this, m_vecOrigin);
};
DVector C_BaseEntity::GetPredOrigin()
{
	if(!this->IsValid()) return DVector(-1000, -1000, -1000);
	return getmember(DVector, this, m_vecAbsOrigin);
};
DVector C_BaseEntity::GetVelocity()
{
	if(!this->IsValid()) return DVector(-1000, -1000, -1000);
	return DVector(getmember(float, this, m_flVelocityX), getmember(float, this, m_flVelocityY), getmember(float, this, m_flVelocityZ));
};
C_BaseEntity* C_BaseEntity::GetGroundEntity()
{
	if(!this->IsValid()) return 0;
	return getmember(C_BaseEntity*, this, m_hGroundEntity);
};
int* C_BaseEntity::GetFlagPtr()
{
	if(!this->IsValid()) return 0;
	return makeptr(int, this, m_nFlags);
};
int C_BaseEntity::GetFlags()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_nFlags);
};