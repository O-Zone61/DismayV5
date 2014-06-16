#include <Windows.h>
#include <iostream>
#include "DDismay.h"

extern DDismay* dismay = 0;

DWORD WINAPI Startup(LPVOID)
{
	dismay = new DDismay();
	dismay->SetConColor(FG_RED);
	printf("%s\n%s", "*.*.*.*.*  *.*.*.*.*", "*.*.*.*");
	dismay->ResetConColor();
	dismay->SetConColor(FG_RED|FG_INTENSE);
	printf("%s", "Dismay");
	dismay->ResetConColor();
	dismay->SetConColor(FG_RED);
	printf("%s\n%s\n", "*.*.*.*", "*.*.*.*.*  *.*.*.*.*");
	dismay->ResetConColor();
	return dismay->main();
}

BOOL WINAPI DllMain(HMODULE this_mod, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON","w",stdout);
		freopen("CON", "r", stdin);
		//int ip = 177000966;
		//char tmp[16];
		//sprintf(tmp, "%p", ip);
		//MessageBox(0, tmp, tmp, MB_OK);

		CreateThread(NULL, NULL, &Startup, NULL, NULL, NULL);
	}
	else if(dwReason == DLL_PROCESS_DETACH)
	{
		printf("%s\n", "DLL Detached - Killing\n\nThis has been Dismay v5. Thanks for your usage.\n");
		Sleep(1000);
	}
	return 1;
}