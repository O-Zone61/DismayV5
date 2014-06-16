#ifndef DISMAY_CCLIENTENTLIST
#define DISMAY_CCLIENTENTLIST

#include <icliententitylist.h>
#include <cbase.h>

class CClientEntityList
{
public:
	virtual IClientNetworkable* CClientEntityList::GetClientNetworkable(int) = 0;
	virtual IClientNetworkable* CClientEntityList::GetClientNetworkableFromHandle(CBaseHandle) = 0;
	virtual IClientUnknown* CClientEntityList::GetClientUnknownFromHandle(CBaseHandle) = 0;
	virtual IClientEntity* CClientEntityList::GetClientEntity(int) = 0;
	virtual IClientEntity* CClientEntityList::GetClientEntityFromHandle(CBaseHandle) = 0;
	virtual int CClientEntityList::NumberOfEntities(bool) = 0;
	virtual int CClientEntityList::GetHighestEntityIndex(void) = 0;
	virtual void CClientEntityList::SetMaxEntities(int) = 0;
	virtual int CClientEntityList::GetMaxEntities(void) = 0;
};
#endif