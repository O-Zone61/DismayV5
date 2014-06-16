//#define DISMAY_DEBUG

#include <WinSock2.h>
#include "DBaseEntity.h"
#include "DDismay.h"
#include "DFuncs.h"
#include <string>
#include "IClientUser.h"
#include "IClientEngine.h"
#include "DGame.h"
#include <IPHlpApi.h>
#include "Garry/dismay_csigscan.h"
#ifdef GARRYSMOD
class DLua;
#include "dismay_cvgui.h"
#include "Garry/dismay_cengineclient.h"
#include "Garry/dismay_cclient.h"
#include "Garry/dismay_cluashared.h"
#include "Garry/dismay_cmatsystemsurface.h"
#include "Garry/dismay_cpanelwrapper.h"
#include "Garry/dismay_cinput.h"
#include "Garry/dismay_ccvar.h"
#include "Garry/dismay_ccliententitylist.h"
#endif
#ifdef CSS
#include "CSS/dismay_cclient.h"
#include "CSS/dismay_cmatsystemsurface.h"
#include "CSS/dismay_cengineclient.h"
#endif

extern DDismay* dismay;

DDismay::DDismay(void)
{
	m_iForceNumber		= -1;

	m_pSurface			= GetInterface<CMatSystemSurface*>	("vguimatsurface.dll",	"VGUI_Surface"	);
	m_pEngineClient		= GetInterface<CEngineClient*>		("engine.dll",			"VEngineClient"	);
	m_pClient			= GetInterface<CClient*>			("client.dll",			"VClient"		);
	m_pPanel			= GetInterface<CPanelWrapper*>		("vgui2.dll",			"VGUI_Panel"	);
	m_pCvar				= GetInterface<CCvar*>				("vstdlib.dll",			"VEngineCvar"	);
	m_pClientEntityList	= GetInterface<CClientEntityList*>	("client.dll",			"VClientEntityList");
	m_pPrediction		= GetInterface<CPrediction*>		("client.dll",			"VClientPrediction");
#ifdef GARRYSMOD
	m_pLua				= GetInterface<CLuaShared*>			("lua_shared.dll",		"LUASHARED"		);
#endif // GARRYSMOD
	m_pClientEngine		= GetInterface<IClientEngine*>		("steamclient.dll",		"CLIENTENGINE_INTERFACE_VERSION");
	m_pVGui				= GetInterface<CVGui*>				("vgui2.dll",			"VGUI_ivgui"	);
	m_pNameConvar		= m_pCvar->FindVar("name");
	m_pInput			= **(CInput***)((*(DWORD**)m_pClient)[14] + 0x02); // 14 = IN_ACTIVATEMOUSE
	
	HSteamPipe pipe		= m_pClientEngine->CreateSteamPipe();
	HSteamUser user		= m_pClientEngine->ConnectToGlobalUser(pipe);

	m_pClientUser		= m_pClientEngine->GetIClientUser(user, pipe, "CLIENTUSER_INTERFACE_VERSION001");
	m_pClientFriends	= m_pClientEngine->GetIClientFriends(user, pipe, "CLIENTFRIENDS_INTERFACE_VERSION001");
	MessageBox(0, "a", "a", MB_OK);
	m_pvtNameConvar		= new DVTable((DWORD*)m_pNameConvar);
	m_pvtSurface		= new DVTable((DWORD*)m_pSurface);
	m_pvtEngineClient	= new DVTable((DWORD*)m_pEngineClient);
	m_pvtClient			= new DVTable((DWORD*)m_pClient);
	m_pvtPanel			= new DVTable((DWORD*)m_pPanel);
	m_pvtInput			= new DVTable((DWORD*)m_pInput);
	m_pvtPrediction		= new DVTable((DWORD*)m_pPrediction);
#ifdef GARRYSMOD
	m_pvtLua			= new DVTable((DWORD*)m_pLua);
	m_pvtLuaMInt		= new DVTable((DWORD*)m_pLua->GetLuaInterface(2));
	m_pvtLuaCInt		= 0;
#endif // GARRYSMOD
	
	m_szName			= new char[128];
	ZeroMemory(m_szName, 128);
	m_bSendCmds			= true;
	m_bRepCmds			= false;
	m_iCurRepCmd		= 0;
#ifdef GARRYSMOD
	m_bClientRan		= 0;
	m_bMenuRan			= 0;
#endif // GARRYSMOD

	m_pEngineRender		= new DEngineRenderMenu();
	
    char data[4096ul];
    ZeroMemory(data, 4096ul);
    unsigned long  len = 4096ul;
    PIP_ADAPTER_INFO pinfo = (PIP_ADAPTER_INFO)data;
	unsigned int iTotalLen;
	MessageBox(0, "b", "b", MB_OK);

	DWORD ret = GetAdaptersInfo(pinfo, &len);
	if(ret != ERROR_SUCCESS)
		error("error #11");
	else
	{
		for(iTotalLen = 0;pinfo != 0 ;pinfo = pinfo->Next)
			if(pinfo->Type == MIB_IF_TYPE_ETHERNET)
				iTotalLen += pinfo->AddressLength * 2;
	}
	HW_PROFILE_INFO hwProfileInfo;

	if(GetCurrentHwProfile(&hwProfileInfo) == NULL)
		error("error #12");
	else
	{
		iTotalLen += strlen(hwProfileInfo.szHwProfileGuid);
	}
	
	MessageBox(0, "c", "c", MB_OK);
	m_szHWID = new char[iTotalLen];
	ZeroMemory(m_szHWID, iTotalLen);

	
	pinfo = (PIP_ADAPTER_INFO)data;


	for(iTotalLen = 0;pinfo != 0 ;pinfo = pinfo->Next)
		if(pinfo->Type == MIB_IF_TYPE_ETHERNET)
			for(unsigned int i = 0; i < pinfo->AddressLength; i++)
				sprintf(m_szHWID, "%s%02X", m_szHWID, pinfo->Address[i]);
	sprintf(m_szHWID, "%s%s", m_szHWID, hwProfileInfo.szHwProfileGuid);
	MessageBox(0, "d", "d", MB_OK);
}

CONSOLE_SCREEN_BUFFER_INFO csbi;

void DDismay::ConCommand(const char* str)
{
	dismay->m_pDLua->RunString(str);
	printf("\n");
}
bool DDismay::SetConColor(unsigned short color)
{
	HANDLE hstdin  = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD   index   = 0;

	// Remember how things were when we started
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	SetConsoleTextAttribute(hstdout, color);
	return true;
}

bool DDismay::ResetConColor()
{
	HANDLE hstdin  = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hstdin);
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
	return true;
}

void put__(PVOID address, int bytes, byte ch){
    DWORD d, ds;
    VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
    memset(address, ch, bytes);
	VirtualProtect(address,bytes,d,&ds);
}

bool DDismay::main(void)
{
	typedef void* (__fastcall PaintTraverseFn)(CPanelWrapper* pThis, void* _ECX, uint panel, bool a3, bool a4);
	m_pvtPanel->Hook(PAINTTRAVERSE, (PaintTraverseFn*)&PaintTraverse);
	m_pvtPanel->ReplaceWithNew();

	m_pvtEngineClient->Hook(20, (void*)&CSetViewAngles);
	m_pvtEngineClient->ReplaceWithNew();

	typedef void (__stdcall CreateMoveFn)(int seq, float frametime, bool bActive);
	m_pvtClient->Hook(CREATEMOVE, (CreateMoveFn*)&CreateMove);
	m_pvtClient->ReplaceWithNew();

	dismay->m_pvtInput->Hook(3, (void*)&CCreateMove);
	dismay->m_pvtInput->Hook(5, (void*)&CWriteUsercmd);
	dismay->m_pvtInput->Hook(8, (void*)&CGetUserCmd);
	dismay->m_pvtInput->ReplaceWithNew();
	
	old_setvalue = m_pvtNameConvar->GetOld(SETVALUE);
	m_pvtNameConvar->HookOld(SETVALUE, (void*)&NameSetValue);
	//m_pvtNameConvar->ReplaceWithNew();

#ifdef GARRYSMOD
	m_pDLua				= new DLua();
	DWORD result = SigScan::dwFindPattern((DWORD)GetModuleHandle("client.dll"), 0x99999999, (PBYTE)"\x8D\x4D\x00\xE8\x00\x00\x00\x00\x6A\x00\x8D\x4D\x00\xE8\x00\x00\x00\x00\x57\x8D\x4D\x00\xE8\x00\x00\x00\x00\x8B\x4D\x00\x8B\x55\x00\x51\x52\xE8\x00\x00\x00\x00\x56\xE8\x00\x00\x00\x00", "xx?x????x?xx?x????xxx?x????xx?xx?xxx????xx????");
	result += strlen("xx?x????x?xx?x????xxx?x????xx?xx?xx") * 0x01;

	put__((PVOID)result, 5, 0x90);

	typedef void* (__fastcall RunStringFn)(CLuaInterface*, void*, const char*, const char*, const char*, bool, bool);
	m_pvtLuaMInt->Hook(RUNSTRING, (RunStringFn*)&RunString);
	m_pvtLuaMInt->ReplaceWithNew();


	m_pvtLua->Hook(CREATELUAINTERFACE, (void*)&CreateInterface);
	m_pvtLua->Hook(DELETELUAINTERFACE, (void*)&DeleteInterface);

	m_pvtLua->ReplaceWithNew();

	//LoadMenu(dismay->m_pLua->GetLuaInterface(2));
#endif // GARRYSMOD
	std::string tmp;
	while(1)
	{
		char relp[512];
		dismay->SetConColor(FG_GREEN);
		printf("> ");
		dismay->ResetConColor();
		std::getline(std::cin, tmp);
		dismay->SetConColor(FG_BLUE|FG_INTENSE);
		printf("> ");
		dismay->ResetConColor();
		strcpy(relp, tmp.c_str());
		dismay->ConCommand(relp);
	}
	return 1;
}

char* DDismay::GetStringRegKey(HKEY hKey, char* strValueName, char* &strDefaultValue)
{
	return 0; // pls remove
}


char* DDismay::DecryptWebFile(char* &encrypted, char* key, int nTotalLength)
{
	for(int i = nTotalLength - 1; i >= 0; i--)
		encrypted[i] = encrypted[i] ^ key[i % strlen(key)];
	return encrypted;
}


char* DDismay::FetchFileFromWeb(int which, const char* key, unsigned int bytes)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		error("WSAStartup failed! (file downloader)\n");
		return 0;
	}

	SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	struct hostent* host = gethostbyname("meep.gentoocorp.org");
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port=htons(80);
	SockAddr.sin_family=AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0)
	{
		error("connect failed! (file downloader)\n");
		return 0;
	}
	char snd[256];
	sprintf(snd, 
		"GET /get2.php?file=%i&stmd=%llu&h=%s HTTP/1.0\r\n"
		"Host: meep.gentoocorp.org\r\n"
		"\r\n", which, m_pClientUser->GetSteamID().ConvertToUint64(), m_szHWID);
	send(Socket, snd, strlen(snd), 0);
	int nDataLength;
	int nTotalLength = 0;
	char* end = new char[bytes];
	ZeroMemory(end, bytes);
	while(nDataLength = recv(Socket, end + nTotalLength, bytes - nTotalLength, 0)){
		if(nDataLength == SOCKET_ERROR)
		{
			char stuf[128];
			sprintf(stuf, "Error occured getting files: %i\n", WSAGetLastError());
			error(stuf);
			break;
		}
		nTotalLength += nDataLength;
	}
	closesocket(Socket);
	WSACleanup();
	char* eend = (strstr(end, "____") + strlen("____"));
	int len = nTotalLength - ((int)eend - (int)end);
	char* nend = new char[len + 1];
	ZeroMemory(nend, len + 1);

	memcpy(nend, eend, len);
	delete[] end;
	if(!strcmp(key, ""))
		key = "\x01\x73\xD7\xB2\xC3\xA3\x2F\x6F\xD4";
	return DecryptWebFile(nend, (char*)key, len);
}

int DDismay::error(const char* message)
{
#ifdef DISMAY_DEBUG
	return MessageBox(0, message, "Error", MB_OK);
#else
	return ERROR_SUCCESS;
#endif
}

int nTotalLen = 40;

template <class _interface>
_interface DDismay::GetInterface(const char* module_name, const char* interface_name)
{
	typedef void* (*CreateInterfaceFn)(const char* pszInterface, int* pReturnCode);
	HMODULE module_ = GetModuleHandle(module_name);
	if(!module_)
	{
		dismay->SetConColor(FG_RED|FG_INTENSE);
		printf("Error getting %s (module %s not found)\n", interface_name, module_name);
		dismay->ResetConColor();
		return (_interface)0;
	}
	CreateInterfaceFn cfn = (CreateInterfaceFn)GetProcAddress(module_, "CreateInterface");
	if(!cfn)
	{
		dismay->SetConColor(FG_RED|FG_INTENSE);
		sprintf("Error getting %s (module %s's CreateInterfaceFn not found)\n", interface_name, module_name);
		dismay->ResetConColor();
		return (_interface)0;
	}
	void* ret;
	for(int i = 0;i < 1000;i++)
	{
		char tmp[256];
		if(i < 10)
			sprintf(tmp, "%s00%i", interface_name, i);
		else if(i < 100)
			sprintf(tmp, "%s0%i", interface_name, i);
		else
			sprintf(tmp, "%s%i", interface_name, i);
		ret = cfn(tmp, 0);
		if(ret != 0)
		{
			for(int i = strlen(tmp); i < nTotalLen; i++)
			{
				tmp[i] = ' ';
				tmp[i + 1] = '\x00';
			}
			dismay->SetConColor(FG_GREEN|FG_INTENSE);
			printf("%s0x%p\n", tmp, ret);
			dismay->ResetConColor();
			break;
		}
	}
	if(!ret)
	{
		dismay->SetConColor(FG_RED|FG_INTENSE);
		printf("Error getting %s\n", interface_name);
		dismay->ResetConColor();
		return (_interface)0;
	}
	return (_interface)ret;
};