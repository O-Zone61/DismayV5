#include "DGame.h"
#include "DDismay.h"
#include "DVTable.h"
#include <string>

extern DDismay* dismay;

#define _tc(a) MessageBox(0, a, a, MB_OK)

#define getind(ptr, i) (getmem(*ptr, i))

#define getmem(vtbl, i) (*(DWORD*)((DWORD)vtbl + sizeof(DWORD) * i))

DVTable::DVTable(DWORD* ptr)
{
	m_pHookedVTable = ptr;
	int i = 0;
	for(i = 0;IsValidCodePtr(getind(ptr, i));i++)
	{
	}
	i++;
	DWORD* old_vtable = (DWORD*)*ptr;
	DWORD* new_vtable = new DWORD[i];
	for(int v = 0; v < i; v++)
	{
		new_vtable[v] = getind(ptr, v);
	}
	m_pNewVTable = new_vtable;
	m_pOldVTable = old_vtable;
	m_iSize = i;
}
DVTable::~DVTable()
{
	ReplaceWithOld();
	delete[] m_pNewVTable;
}

DWORD* DVTable::GetOld(int index)
{
	return (DWORD*)m_pOldVTable[index];
};

bool DVTable::Hook(int index, void* func)
{
	if(index >= m_iSize)
	{
		char err[32];
		sprintf(err, "index %i > size %i", index, m_iSize);
		dismay->error(err);
		return 0;
	}

	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)m_pNewVTable, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);

	m_pNewVTable[index] = (DWORD)func;

	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

	return 1;
}

bool DVTable::HookOld(int index, void* func)
{
	if(index >= m_iSize)
	{
		char err[32];
		sprintf(err, "index %i > size %i", index, m_iSize);
		dismay->error(err);
		return 0;
	}

	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)m_pOldVTable, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);

	m_pOldVTable[index] = (DWORD)func;

	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

	return 1;
}

bool DVTable::ReplaceWithNew()
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)m_pHookedVTable, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);

	m_pHookedVTable[0] = (DWORD)m_pNewVTable;

	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

	return 1;
}

bool DVTable::ReplaceWithOld()
{
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)m_pHookedVTable, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);

	m_pHookedVTable[0] = (DWORD)m_pOldVTable;

	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

	return 1;
}