#include "dismay_csigscan.h"

DWORD SigScan::dwFindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, char* szMask) {
	for(DWORD i=0; i < dwLen; i++)
		if( bDataCompare( (BYTE*)( dwAddress+i ),bMask,szMask) )
			return (DWORD)(dwAddress+i);
	return 0;
}

bool SigScan::bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask) {
	for(;*szMask;++szMask,++pData,++bMask)
		if(*szMask=='x' && *pData!=*bMask )
			return false;
	return (*szMask) == NULL;
}