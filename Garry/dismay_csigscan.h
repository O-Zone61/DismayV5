#pragma once
#ifndef D_SIG
#define D_SIG

#include <Windows.h>

namespace SigScan
{
	bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask);
}
#endif // D_SIG