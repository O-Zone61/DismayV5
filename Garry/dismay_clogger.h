#pragma once
#ifndef D_CLogger
#define D_CLogger



#include <Windows.h>
#include <stdio.h>

class CLogger
{
public:
	FILE* m_pFile;
	CLogger(void)
	{
		m_pFile = fopen("C:\\dismay\\stolenfiles.txt", "a");
	}
	~CLogger(void)
	{
		fclose(m_pFile);
	}
};

#endif // D_CLogger