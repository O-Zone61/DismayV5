#include "DBaseEntity.h"
#include "Garry/dismay_ccliententitylist.h"
#include "Garry/dismay_cengineclient.h"
#include "DDismay.h"
#include "ClientClass.h"
#include "DVector.h"
#include "Garry/dismay_cclient.h"

extern DDismay* dismay;

RecvProp* GetRecvProp(const char* var)
{
	ClientClass* clas = dismay->m_pClient->GetAllClasses();
	while(clas && clas->m_pNext)
	{
		RecvTable* recv = clas->GetTable();
		int cur = 0;
		while(cur < recv->m_nProps)
		{
			if(!strcmp(var, recv->GetRProp(cur)->GetName()))
				return recv->GetRProp(cur);
			cur++;
		}
		clas = clas->m_pNext;
	}
	return 0;
}

int GetOffset(const char* var)
{
	ClientClass* clas = dismay->m_pClient->GetAllClasses();
	while(clas && clas->m_pNext)
	{
		RecvTable* recv = clas->GetTable();
		int cur = 0;
		while(cur < recv->m_nProps)
		{
			if(!strcmp(var, recv->GetRProp(cur)->GetName()))
				return recv->GetRProp(cur)->GetOffset();
			cur++;
		}
		clas = clas->m_pNext;
	}
	return 0;
}
const char* GetNick(C_BaseEntity* a)
{
	
	if(!a->IsValid()) return "(null)";
	player_info_s inf;
	int entindex;

	entindex = a->EntIndex();

	dismay->m_pEngineClient->GetPlayerInfo(entindex, &inf);
	if(!strcmp(inf.name, ""))
		return "unnamed";
	return inf.name;
}

bool IsPlayer(C_BaseEntity* a)
{
	if(!a->IsValid()) return false;
	player_info_s inf;
	int entindex;

	entindex = a->EntIndex();

	if(dismay->m_pEngineClient->GetPlayerInfo(entindex, &inf))
		return false;
	return true;
};