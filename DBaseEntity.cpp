#include "DBaseEntity.h"
#include "Garry/dismay_ccliententitylist.h"
#include "Garry/dismay_cengineclient.h"
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
int C_BaseEntity::GetTeam()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_iTeam);
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
bool IsPlayer(C_BaseEntity* a)
{
	if(!a->IsValid()) return false;
	player_info_s inf;
	int entindex;

	entindex = a->EntIndex();

	if(!dismay->m_pEngineClient->GetPlayerInfo(entindex, &inf))
		return false;
	return true;
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
int C_BaseEntity::GetFlags()
{
	if(!this->IsValid()) return 0;
	return getmember(int, this, m_nFlags);
};