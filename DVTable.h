#ifndef DVTable__
#define DVTable__

typedef unsigned long DWORD;

class DVTable
{
public:
	DVTable(DWORD* ptr);
	~DVTable();

	bool ReplaceWithOld();
	bool ReplaceWithNew();

	bool Hook(int index, void* func);
	bool HookOld(int index, void* func);
	
	DWORD* GetOld(int index);
	
	int m_iSize;
	DWORD* m_pNewVTable;
	DWORD* m_pOldVTable;
	DWORD* m_pHookedVTable;
};

#endif // DVTable__