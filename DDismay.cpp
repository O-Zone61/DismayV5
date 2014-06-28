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
#include "ClientClass.h"
#ifdef LoadMenu // win32
#undef LoadMenu
#endif


extern DDismay* dismay;
typedef bool (__stdcall* CallbackFn)(DWORD address);

DWORD FindSig(DWORD addr, const char* szSig, const char* xSig, DWORD len, bool bTrack = false)
{
	size_t slen = strlen(xSig);
	unsigned int i = 0;
	for(i = 0; i < len; i++)
	{
		char* x = (char*)(addr + i);
		unsigned int d = 0;
		while(true)
		{
			if(bTrack)
				printf("%i = %02X \n", d + i, x[d]);
			if(xSig[d] == '\x00')
				return (DWORD)x;
			if(xSig[d] == 'x' && x[d] != szSig[d])
				break;
			d++;
		}
		if(bTrack)
			printf("\n");
	}
	return 0;
}

bool __stdcall PaintTraverseSig(DWORD addr)
{
	DWORD x;
	if((x = FindSig(addr, "\x8B\x10", "xx", 0x20)))
		if(FindSig(x, "\x5D\xC2\x0C\x00", "xxxx", 0x30))
			return true;
	return false;
}

bool __stdcall GetAppID(DWORD addr)
{
	DWORD deref = addr + sizeof(DWORD) + *(DWORD*)(addr + 1);
	if(!IsBadCodePtr((FARPROC)(deref)))
		if(FindSig(deref, "\x80\x3D\x00\x00\x00\x00\x00\x75\x00\xE8\x00\x00\x00\x00\x83\x78\x00\x00\x74\x00\xC6\x05\x00\x00\x00\x00", "xx????xx?x????xx??x?xx????", 0x5))
			return true;
	return false;
}

int FindSigInVTable(void* clas, const char* szSig, const char* xSig, DWORD len = 0x20, CallbackFn iffound = 0)
{
	size_t slen = strlen(xSig);
	unsigned int i = 0;
	DWORD* vtbl = *(DWORD**)clas;
	while(!IsBadCodePtr((FARPROC)(vtbl[i])))
	{
		DWORD addr = FindSig(vtbl[i], szSig, xSig, len);
		if(addr != 0)
			if(iffound != 0)
			{
				if(iffound(addr))
					return i;
			}
			else return i;
		i++;
	}
	return -1;
}



void ClassesToString(ClientClass* t)
{
	char c[512];
	sprintf(c, "C:/dismay/netvars/%i.txt", dismay->m_nAppID);
	std::ofstream file = CreateDirAndFile(c);
	if(!t) return;
	while(t && t->m_pNext)
	{
		file <<  t->m_pszName << std::endl;
		RecvTable* a = t->m_pRecvTable;
		int cur = 0;
		RecvProp* prop;
		while(cur < a->m_nProps)
		{
			prop = a->GetRProp(cur);
			file << "\t" << "(" << prop->GetTypeName() << ")";
			for(size_t size = strlen(prop->GetTypeName()); size < 10; size++)
			{
				file << " ";
			}
			file << prop->GetName();
			
			for(size_t size = strlen(prop->GetName()); size < 15; size++)
			{
				file << " ";
			}
			char tmp[32];
			sprintf(tmp, "0x%04X", prop->GetOffset());
			file << tmp << std::endl;
				// << "\t- " << prop->GetOffset() << "\r\n";
			cur++;
		}
		t = t->m_pNext;
	}
	file.close();
}

bool DDismay::SetDrawColor(int r, int g, int b, int a)
{
	typedef void* (__thiscall* OriginalFn)(CMatSystemSurface*, int, int, int, int);
	m_pSurface->DrawSetColor(r, g, b, a);
	//GetFunc<OriginalFn>(m_pSurface, m_nSetDrawColor)(m_pSurface, r, g, b, a);
	return true;
}

bool DDismay::WorldToScreen(Vector& world, Vector& screen)
{
	typedef int (__thiscall* OriginalFn)(CDebugOverlay*, Vector&, Vector&);
	return !GetFunc<OriginalFn>(m_pDebug, m_nScreenPosition)(m_pDebug, world, screen);
}

DDismay::DDismay(void)
{
	m_iForceNumber		= -1;

	while(!(m_pSurface=GetInterface<CMatSystemSurface*>("vguimatsurface.dll","VGUI_Surface"	)))
		Sleep(500);
	while(!(m_pEngineClient=GetInterface<CEngineClient*>("engine.dll","VEngineClient"	)))
		Sleep(500);
	
	m_nGetAppID			= FindSigInVTable(m_pEngineClient, "\xE9", "x", 0x5, &GetAppID);
	m_nIsInGame			= FindSigInVTable(m_pEngineClient, "\x33\xC0\x83\x3D\x00\x00\x00\x00\x06\x0F\x94\xC0\xC3", "xxxx????xxxxx", 0x2);
	m_nGetViewAngles	= FindSigInVTable(m_pEngineClient, "\xF3\x0F\x11\x00\xF3\x0F\x10\x05\x00\x00\x00\x00\xF3\x0F\x11\x40\x04\xF3\x0F\x10\x05\x00\x00\x00\x00\xF3\x0F\x11\x40\x08\x5D\xC2\x00\x00", "xxxxxxxx????xxxxxxxxx????xxxxxxx??", 0x13);
	m_nSetViewAngles	= m_nGetViewAngles + 1;
	m_nScreenPosition	= 10;

	m_nAppID			= GetFunc<int (__thiscall*)(CEngineClient*)>(m_pEngineClient, m_nGetAppID)(m_pEngineClient);
	m_pClient			= GetInterface<CClient*>			("client.dll",			"VClient"		);
	m_pPanel			= GetInterface<CPanelWrapper*>		("vgui2.dll",			"VGUI_Panel"	);
	m_nPaintTraverse	= 41; // todo: fix
	//m_nPaintTraverse	= FindSigInVTable(m_pPanel, "\x55\x8B\xEC\x8B\x01\x00\x00\x08\x00\x00\x00\x00\x00\x00", "xxxxx??x????xx", 0x2, &PaintTraverseSig);

	while(!(m_pCvar=GetInterface<CCvar*>("vstdlib.dll","VEngineCvar")))
		Sleep(500);
	while(!(m_pClientEntityList=GetInterface<CClientEntityList*>("client.dll","VClientEntityList")))
		Sleep(500);
	while(!(m_pPrediction=GetInterface<CPrediction*>("client.dll","VClientPrediction")))
		Sleep(500);
	if(m_nAppID == 4000)
		while(!(m_pLua=GetInterface<CLuaShared*>("lua_shared.dll","LUASHARED")))
			Sleep(500);

	while(!(m_pClientEngine=GetInterface<IClientEngine*>("steamclient.dll","CLIENTENGINE_INTERFACE_VERSION")))
		Sleep(500);
	m_pVGui				= GetInterface<CVGui*>				("vgui2.dll",			"VGUI_ivgui"	);
	m_pDebug			= GetInterface<CDebugOverlay*>		("engine.dll",			"VDebugOverlay");
	Sleep(5000);
	m_pNameConvar		= m_pCvar->FindVar("name");
	m_pInput			= **(CInput***)((*(DWORD**)m_pClient)[14] + 0x02); // 14 = IN_ACTIVATEMOUSE
	
	HSteamPipe pipe		= m_pClientEngine->CreateSteamPipe();
	HSteamUser user		= m_pClientEngine->ConnectToGlobalUser(pipe);

	m_pClientUser		= m_pClientEngine->GetIClientUser(user, pipe, "CLIENTUSER_INTERFACE_VERSION001");
	m_pClientFriends	= m_pClientEngine->GetIClientFriends(user, pipe, "CLIENTFRIENDS_INTERFACE_VERSION001");

	m_pvtNameConvar		= new DVTable((DWORD*)m_pNameConvar);
	m_pvtSurface		= new DVTable((DWORD*)m_pSurface);
	m_pvtEngineClient	= new DVTable((DWORD*)m_pEngineClient);
	m_pvtClient			= new DVTable((DWORD*)m_pClient);
	m_pvtPanel			= new DVTable((DWORD*)m_pPanel);
	m_pvtInput			= new DVTable((DWORD*)m_pInput);
	m_pvtPrediction		= new DVTable((DWORD*)m_pPrediction);
	
	m_nSetDrawColor		= 10;
	m_nDrawLine			= 15;
	m_nDrawFilledRect	= 12;
	if(m_nAppID == 4000)
	{
		m_pvtLua			= new DVTable((DWORD*)m_pLua);
		m_pvtLuaMInt		= new DVTable((DWORD*)m_pLua->GetLuaInterface(2));
		m_pvtLuaCInt		= 0;
	}
	
	m_szName			= new char[128];
	ZeroMemory(m_szName, 128);
	m_bSendCmds			= true;
	m_bRepCmds			= false;
	m_iCurRepCmd		= 0;
	m_bClientRan		= 0;
	m_bMenuRan			= 0;

	
    char data[4096ul];
    ZeroMemory(data, 4096ul);
    unsigned long  len = 4096ul;
    PIP_ADAPTER_INFO pinfo = (PIP_ADAPTER_INFO)data;
	unsigned int iTotalLen;

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
	
	m_szHWID = new char[iTotalLen];
	ZeroMemory(m_szHWID, iTotalLen);

	
	pinfo = (PIP_ADAPTER_INFO)data;


	for(iTotalLen = 0;pinfo != 0 ;pinfo = pinfo->Next)
		if(pinfo->Type == MIB_IF_TYPE_ETHERNET)
			for(unsigned int i = 0; i < pinfo->AddressLength; i++)
				sprintf(m_szHWID, "%s%02X", m_szHWID, pinfo->Address[i]);
	sprintf(m_szHWID, "%s%s", m_szHWID, hwProfileInfo.szHwProfileGuid);
	dismay->SetConColor(FG_BLUE|BG_RED|FG_INTENSE);
	printf("Playing app %i\n", m_nAppID);
	dismay->ResetConColor();
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

void DDismay::DrawRect(int x1, int y1, int x2, int y2)
{
	typedef void* (__thiscall* OriginalFn)(CMatSystemSurface*, int, int, int, int);
	m_pSurface->DrawFilledRect(x1, y1, x2, y2);
	//GetFunc<OriginalFn>(m_pSurface, m_nDrawFilledRect)(m_pSurface, x1, y1, x2, y2);
}

bool DDismay::DrawLine(int x1, int y1, int x2, int y2)
{
	typedef void* (__thiscall* OriginalFn)(CMatSystemSurface*, int, int, int, int);
	
	m_pSurface->DrawLine(x1, y1, x2, y2);
	//GetFunc<OriginalFn>(m_pSurface, m_nDrawLine)(m_pSurface, x1, y1, x2, y2);
	return true;
}

bool DDismay::DrawColoredText(ulong font,int x,int y,int r,int g,int b,int a,char  const* str)
{
	typedef void* (__cdecl* OriginalFn)(CMatSystemSurface*, ulong,int,int,int,int,int,int,char  const*, ...);
	//MessageBox(0, "b", "b", 0);
	GetFunc<OriginalFn>(m_pSurface, m_nAppID == 240 ? 162 : 164)(m_pSurface, font, x, y, r, g, b, a, "%s", str);
	
	//MessageBox(0, "a", "a", 0);
	return true;
}

HHOOK _hook;


LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_CHAR)
        {
			KBDLLHOOKSTRUCT kbdStruct;
            kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
        }
		else if(wParam == WM_KEYDOWN)
		{
		}
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

bool DDismay::HookWindows()
{
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
		return false;
	return true;
}

bool DDismay::UnhookWindows()
{
    UnhookWindowsHookEx(_hook);
}

bool DDismay::main(void)
{
	m_nTickBase		= GetOffset("m_nTickBase");
	m_fFlags		= GetOffset("m_fFlags");
	m_iEntIndex		= GetOffset("m_iEntIndex");
	m_iHealth		= GetOffset("m_iHealth");
	m_iAmmo			= GetOffset("m_iAmmo");
	m_iTeamNum		= GetOffset("m_iTeamNum");
	m_vecOrigin		= GetOffset("m_vecOrigin");
	m_lifeState		= GetOffset("m_lifeState");
	m_bIsTyping		= GetOffset("m_bIsTyping");
	m_vecVelocity	= GetOffset("m_vecVelocity[0]");
	m_collisionMins	= GetOffset("m_collisionMins");
	m_collisionMaxs	= GetOffset("m_collisionMaxs");
	m_pDLua				= new DLua();
	m_pEngineRender		= new DEngineRenderMenu();
	m_pvtPanel->Hook(m_nPaintTraverse, (void*)&PaintTraverse);
	m_pvtPanel->ReplaceWithNew();

	m_pvtEngineClient->Hook(m_nSetViewAngles, (void*)&CSetViewAngles);
	m_pvtEngineClient->ReplaceWithNew();

	m_pvtClient->Hook(CREATEMOVE, (void*)&CreateMove);
	m_pvtClient->ReplaceWithNew();

	dismay->m_pvtInput->Hook(3, (void*)&CCreateMove);
	dismay->m_pvtInput->Hook(5, (void*)&CWriteUsercmd);
	m_nCUserCmdSize = 0x40;
	if(m_nAppID == 4000)
		m_nCUserCmdSize = 0x15C;
	dismay->m_pvtInput->Hook(8, (void*)&CGetUserCmd);
	dismay->m_pvtInput->ReplaceWithNew();
	
	//old_setvalue = m_pvtNameConvar->GetOld(SETVALUE);
	//m_pvtNameConvar->Hook(SETVALUE, (void*)&NameSetValue);
	//m_pvtNameConvar->ReplaceWithNew();
	
	if(m_nAppID == 4000)
	{
		DWORD result = SigScan::dwFindPattern((DWORD)GetModuleHandle("client.dll"), 0xFFFFFFFF, (PBYTE)"\x8D\x4D\x00\xE8\x00\x00\x00\x00\x6A\x00\x8D\x4D\x00\xE8\x00\x00\x00\x00\x57\x8D\x4D\x00\xE8\x00\x00\x00\x00\x8B\x4D\x00\x8B\x55\x00\x51\x52\xE8\x00\x00\x00\x00\x56\xE8\x00\x00\x00\x00", "xx?x????x?xx?x????xxx?x????xx?xx?xxx????xx????");
		result += strlen("xx?x????x?xx?x????xxx?x????xx?xx?xx") * 0x01;

		put__((PVOID)result, 5, 0x90);

		typedef void* (__fastcall RunStringFn)(CLuaInterface*, void*, const char*, const char*, const char*, bool, bool);
		m_pvtLuaMInt->Hook(RUNSTRING, (RunStringFn*)&RunString);
		m_pvtLuaMInt->ReplaceWithNew();


		m_pvtLua->Hook(CREATELUAINTERFACE, (void*)&CreateInterface);
		m_pvtLua->Hook(DELETELUAINTERFACE, (void*)&DeleteInterface);

		m_pvtLua->ReplaceWithNew();
	}
	ClassesToString(m_pClient->GetAllClasses());
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

bool DDismay::ScreenTransform(const Vector& point, Vector& screen)
{
	const VMatrix& worldToScreen = m_pEngineClient->WorldToScreenMatrix();
	screen.x = worldToScreen[0][0] * point.x + worldToScreen[0][1] * point.y + worldToScreen[0][2] * point.z + worldToScreen[0][3];
	screen.x = worldToScreen[1][0] * point.x + worldToScreen[1][1] * point.y + worldToScreen[1][2] * point.z + worldToScreen[1][3];

	float w = worldToScreen[3][0] * point.x + worldToScreen[3][1] * point.y + worldToScreen[3][2] * point.z + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = FALSE;
	if(w < 0.001f)
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		FLOAT invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}
bool DDismay::WorldToScreen(const Vector &origin, Vector &screen)
{
	bool bRet = false;

	if(!ScreenTransform(origin, screen))
	{
		int width, height;
		m_pEngineClient->GetScreenSize(width, height);

		float fScreenX, fScreenY;
		fScreenX = width / 2;
		fScreenY = height / 2;
		
		fScreenX += 0.5f * screen.x * width + 0.5f;
		fScreenY -= 0.5f * screen.y * height + 0.5f;

		screen.x = fScreenX;
		screen.y = fScreenY;

		bRet = true;
	}

	return bRet;
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
	ZeroMemory(end, nTotalLength);
	realloc((void*) end, nTotalLength);
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