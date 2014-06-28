#include "DDismay.h"
#include "DGame.h"
#include <Windows.h>
#include "Garry/dismay_ccvar.h"
#include "CViewSetup.h"
#include "dismay_cprediction.h"
#include "DVTable.h"
#include "Garry/dismay_cluainterface.h"
#include "Garry/dismay_cluashared.h"
#include "Garry/dismay_cmatsystemsurface.h"

#define t_(x) MessageBox(0, x, x,0)

extern DDismay* dismay;
#define DISMAY_VERSION 8

bool RunStringOld(unsigned char state, const char* str)
{
	CLuaInterface* in = dismay->m_pLua->GetLuaInterface(state);

	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);
	if(state == 0)
		((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(in, "", "", str, true, true);
	else if(state == 2)
		((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(in, "", "", str, true, true);
	else
		return false;

	return true;
}

#define SETGFN(l, func, name) \
	l->PushSpecial(0); \
	l->PushCFunction(func); \
	l->SetField(-2, name); \
	l->Pop(1)

#define SETGINT(l, num, name) \
	l->PushSpecial(0); \
	l->PushNumber((double)num); \
	l->SetField(-2, name); \
	l->Pop(1)

#include "DLuaFuncs.h"

char* replaceChar(char* &r, char toreplace, char replacewith)
{
	for(unsigned int i = 0; i < strlen(r); i++)
	{
		if(r[i] == toreplace)
		{
			r[i] = replacewith;
		}
	}
	return r;
}

std::ofstream CreateDirAndFile(const char* fulldir)
{
	char b[512];

	for(unsigned int i = 0; i < strlen(fulldir); i++)
	{
		strcpy(b, fulldir);
		if(b[i] == '/')
		{
			b[i+1] = 0;
			CreateDirectory(b, 0);
		}
		else if(b[i] == 0)
		{
			break;
		}
	}
	std::ofstream newfile(fulldir);
	return newfile;
}

void StoreFile(const char* folder, const char* name, const char* data)
{
	CLuaInterface* l2 = dismay->m_pLua->GetLuaInterface(2);
	l2->PushSpecial(0);
	l2->GetField(-1, "g_ServerName");
	char* server = (char*)l2->GetString(-1, 0);
	l2->Pop(2);

	replaceChar(server, '\\', '_');
	replaceChar(server, '/', '_');
	replaceChar(server, '"', '_');
	replaceChar(server, ':', '_');
	replaceChar(server, '?', '_');
	replaceChar(server, '<', '_');
	replaceChar(server, '>', '_');
	replaceChar(server, '|', '_');
	replaceChar(server, '*', '_');

	char fulldir[512];
	sprintf(fulldir, "C:/dismay/%s/%s", server, folder, name);

	char b[512];

	for(unsigned int i = 0; i < strlen(fulldir); i++)
	{
		strcpy(b, fulldir);
		if(b[i] == '/' || b[i] == '\\')
		{
			b[i+1] = 0;
			CreateDirectory(b, 0);
		}
		else if(b[i] == 0)
		{
			break;
		}
	}
	std::ofstream newfile(fulldir);
	newfile << data << std::endl;
	newfile.close();
}
inline QAngle GetSpread(Vector spread, QAngle angAim, int seed)
{
	unsigned int uiSeed = MD5_PseudoRandom(seed) & 0x7FFFFFFF;

	RandomSeed((uiSeed & 255));

    float x = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
    float y = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	  
    Vector forward, right, up;

    AngleVectors(angAim, &forward, &right, &up);
	Vector spreaded = forward + (x * spread.x * right) + (y * spread.y * up);
	QAngle ret; 
	VectorAngles(spreaded, ret);
	return ret;
}
#undef lua_register
#define lua_register(x, name, fn) SETGFN(pThis, fn, name)
// to do: remove this
bool LoadClient(CLuaInterface* pThis)
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	if(!pThis) return 0;
	lua_getglobal(dismay->m_pDLua->m_luaState, "NoClient");
	if(lua_toboolean(dismay->m_pDLua->m_luaState, -1))
	{
		lua_pop(dismay->m_pDLua->m_luaState, 1);
		return 0;
	}
		lua_pop(dismay->m_pDLua->m_luaState, 1);
	SETGINT(pThis, DISMAY_VERSION, "rversion");

	lua_register(L, "SetCommandNumber", SetCommandNumber);
	lua_register(L, "SetCmdSendState", SetCmdSendState);
	lua_register(L, "GetCmdSendState", GetCmdSendState);
	lua_register(L, "GetCmdRepState", GetCmdRepState);
	lua_register(L, "SetCmdRepState", SetCmdRepState);
	lua_register(L, "LoadWebScript", LoadWebScriptClient);
	lua_register(L, "GetTickCount", GetTickCount);
	lua_register(L, "SetTickCount", SetTickCount);
	lua_register(L, "SetSteamName", SetSteamName);
	lua_register(L, "RequestFile", RequestFile);
	lua_register(L, "OpenClient", OpenClient);
	lua_register(L, "PredSpread", GetPred);
	lua_register(L, "IsDormant", IsDormant);
	lua_register(L, "RunClient", RunClient);
	lua_register(L, "OpenMenu", OpenMenu);
	lua_register(L, "RunMenu", RunMenu);
	lua_register(L, "Repaint", Repaint);
	lua_register(L, "SetIGN", SetIGN);
	lua_register(L, "_tc", _tc);

	dismay->m_bClientRan = 1;
	const char* client = dismay->FetchFileFromWeb(0);

	RunStringOld(0, client);

	//((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(pThis, "", "", client, true, true);
	delete[] client;
	//((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(pThis, "\x01", "\x01", GetFileText("C:\\dismay\\dismay.lua"), true, true);
	const char* code = GetFileText("C:\\dismay\\dismay.lua");
	RunStringOld(0, code);
	if(strcmp(code, ""))
		delete[] code;
	return 1;	
}

bool LoadMenu(CLuaInterface* pThis) 
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);
	
	if(!pThis) return 0;
	dismay->m_bMenuRan = 1;

	SETGINT(pThis, DISMAY_VERSION, "rversion");


	SETGFN(pThis, Labort, "abort");
	SETGFN(pThis, CreateMenuItem, "CreateMenuItem");
	SETGFN(pThis, RemoveMenuItem, "RemoveMenuItem");
	SETGFN(pThis, SetItemActive, "SetItemActive");
	SETGFN(pThis, SetItemCallback, "SetItemCallback");
	SETGFN(pThis, LoadWebScriptMenu, "LoadWebScript");
	SETGFN(pThis, SetSteamName, "SetSteamName");
	lua_register(L, "SetItemName", SetItemName);
	lua_register(L, "OpenClient", OpenClient);
	lua_register(L, "RunDismay", RunDismay);
	lua_register(L, "RunClient", RunClient);
	lua_register(L, "OpenMenu", OpenMenu);
	lua_register(L, "RunMenu", RunMenu);
	lua_register(L, "SetIGN", SetIGN);
	lua_register(L, "Paint", Paint);
	lua_register(L, "SendMsg", SendMsg);
	lua_register(L, "GetFriendCount", GetFriendCount);
	lua_register(L, "GetFriendName", GetFriendName);
	lua_register(L, "InviteFriendToRoom", InviteFriendToRoom);
	lua_register(L, "GetRoomName", GetRoomName);
	lua_register(L, "GetRoomCount", GetRoomCount);
	lua_register(L, "CreateRoom", CreateRoom);


	char* menu = dismay->FetchFileFromWeb(2);
	RunStringOld(2, menu);


	//((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(pThis, "", "", menu, true, true);
	delete[] menu;
	//((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(pThis, "\x01", "\x01", GetFileText("C:\\dismay\\dismay_menu.lua"), true, true);
	const char* code = GetFileText("C:\\dismay\\dismay_menu.lua");
	RunStringOld(2, code);
	if(strcmp(code, ""))
		delete[] code;
	return 1;
}
#undef lua_register
void* __fastcall RunString(CLuaInterface* pThis, unsigned long _EDX, const char* folder, const char* name, const char* stringtorun, bool bSomething1, bool bSomething2)
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	pThis->PushSpecial(0);
	pThis->GetField(-1, "CLIENT");
	bool bClient = pThis->GetBool(-1);
	pThis->GetField(-2, "SERVER");
	bool bServer = pThis->GetBool(-1);
	pThis->GetField(-3, "MENU_DLL");
	bool bMenu = pThis->GetBool(-1);
	pThis->Pop(4);

	if(bClient && !bMenu && !bServer)
	{
		if(dismay->m_bStealFiles)
		{
			StoreFile((char*)folder, (char*)name, (char*)stringtorun);
		}
		if(!dismay->m_bClientRan)
		{
			LoadClient(pThis);
		}
		return ((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(pThis, folder, name, stringtorun, bSomething1, bSomething2);
	}
	if(bMenu)
	{
		if(!dismay->m_bMenuRan)
		{
			LoadMenu(pThis);
		}
		return ((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(pThis, folder, name, stringtorun, bSomething1, bSomething2);
	}
	return 0;
}
byte* __fastcall DeleteInterface(CLuaShared* pThis, void* _EDX, CLuaInterface* pToClose)
{
	if(pToClose == dismay->m_pLua->GetLuaInterface(0))
	{
		dismay->m_pvtLuaCInt->~DVTable();
		dismay->m_pvtLuaCInt = 0;
	}
	typedef byte* (__thiscall* DeleteInterfaceFn)(CLuaShared* pThis, CLuaInterface* pToClose);
	return ((DeleteInterfaceFn)dismay->m_pvtLua->GetOld(DELETELUAINTERFACE))(pThis, pToClose);
}

byte* __fastcall CreateInterface(CLuaShared* pThis, void* _EDX, unsigned char _interface, bool bSomething)
{
	typedef byte* (__thiscall* CreateInterfaceFn)(CLuaShared*, unsigned char, bool);
	auto ret = ((CreateInterfaceFn)dismay->m_pvtLua->GetOld(CREATELUAINTERFACE))(pThis, _interface, bSomething);

	if(_interface == 0)
	{
		dismay->m_bClientRan = 0;
		dismay->m_pvtLuaCInt = new DVTable((DWORD*)pThis->GetLuaInterface(0));
		dismay->m_pvtLuaCInt->Hook(RUNSTRING, (void*)&RunString);
		dismay->m_pvtLuaCInt->ReplaceWithNew();

	}
	return ret;
}

#define a(msg) dismay->error(msg)

CUserCmd* __fastcall CGetUserCmd(CInput* pThis, void*, int seq)
{
	//MessageBox(0, tmp, tmp, 0);
	auto ret = pThis->HGetUserCmd(seq);
	char tmp[16];
	sprintf(tmp, "%i %p", seq, ret);
	if(IsBadCodePtr((FARPROC)ret))
		MessageBox(0, tmp, tmp, 0);
	return ret;
}

bool __fastcall CWriteUsercmd(CInput* pThis, void*, bf_write* write, int from, int to, bool isnew)
{
	//t_("pre_writeusercmd");
	typedef bool (__thiscall* CEncUcmdBufFn)(CInput*, bf_write*, int, int, bool);
	int number = dismay->m_iForceNumber;
	CUserCmd* old_cmd = pThis->HGetUserCmd(from);
	CUserCmd* cmd = pThis->HGetUserCmd(to);
	if(number != -1)
	{
	
		old_cmd->command_number = number - 1;
		cmd->command_number	= number;

	}
	old_cmd->command_number = cmd->command_number - 1;
	cmd->FixSeed();
	pThis->HSetUserCmd(to, cmd);
	auto ret = ((CEncUcmdBufFn)dismay->m_pvtInput->GetOld(5))(pThis, write, from, to, isnew);
	//t_("post_writeusercmd");
	return ret;
}

void* __fastcall CSetViewAngles(CEngineClient* ths, void*, QAngle& ang)
{
	//t_("pre_setjewangles");
	QAngle dun = ang;
	lua_State* L = dismay->m_pDLua->m_luaState;
	lua_pushcfunction(L, Error);
	lua_pushglobaltable(L);
	lua_getfield(L, -1, "hook");
	lua_getfield(L, -1, "Call");
	lua_pushstring(L, "CalcViewAngle");
	lua_pcall(L, 1, 1, -3);
	if(!GetAngle(L).IsShit())
		dun =  GetAngle(L);
	lua_pop(L, 4);

	auto ret =  ((void* (__thiscall*)(CEngineClient*, QAngle&))dismay->m_pvtEngineClient->GetOld(dismay->m_nSetViewAngles))(ths, dun);
	//t_("post_setjewangles");
	return ret;
}

void __fastcall CCreateMove(CInput* pThis, void*, int seq, float frametime, bool bActive)
{
	//t_("pre_createmove");
	typedef void (__thiscall* CCreateMoveFn)(CInput*, int, float, bool);
	((CCreateMoveFn)dismay->m_pvtInput->GetOld(3))(pThis, seq, frametime, bActive);
	
	lua_State* L = dismay->m_pDLua->m_luaState;
	lua_pushcfunction(L, Error);
	lua_getglobal(L, "hook");
	lua_getfield(L, -1, "Call");
	lua_pushstring(L, "CreateMove");
	PushCUserCmd(L, pThis->HGetUserCmd(seq));
	int ret = lua_pcall(L, 2, 0, -5);
	if(ret != 0)
	{
		lua_pop(L, 1);
	}
	lua_pop(L, 2);

	pThis->HSetUserCmd(seq, pThis->HGetUserCmd(seq));
	//t_("post_createmove");

}
void __stdcall CreateMove(int seq, float frametime, bool bActive)
{
	//t_("pre_createmoveinput");
	CInput* pInput = dismay->m_pInput;

	void* cebp = 0;
	__asm mov cebp, ebp

	if(cebp)
	{
		DWORD* retnAddr = (DWORD*)(*(char**)cebp + 0x4);
		if(dismay->m_bRepCmds && dismay->m_iCurRepCmd < 21)
		{
			*retnAddr		-= 0x5;
			dismay->m_iCurRepCmd++;
		}
		else
		{
			dismay->m_iCurRepCmd = 0;
		}
	}
	else dismay->error("no ebp");
	typedef void (__stdcall CreateMove_t)(int, float, bool bActive);
	CreateMove_t* CreateMove_O = (CreateMove_t*)(dismay->m_pvtClient->GetOld(CREATEMOVE));
	byte* bSendPacket = (*(byte**)cebp - 0x1);
	*bSendPacket = dismay->m_bSendCmds;
	CreateMove_O(seq, frametime, bActive);
	//t_("post_createmoveinput");
}
void* __fastcall PaintTraverse(CPanelWrapper* pThis, void* _ECX, uint panel, bool a3, bool a4)
{
	typedef void* (__thiscall* PaintTraverse_t)(CPanelWrapper*, uint, bool, bool);
	//if(GetAsyncKeyState(VK_INSERT))
	//	MessageBox(0, pThis->GetName(panel), pThis->GetName(panel), MB_OK);
	auto ret = ((PaintTraverse_t)((dismay->m_pvtPanel->GetOld(dismay->m_nPaintTraverse))))(pThis, panel, a3, a4);
	
	if(dismay->m_nAppID == 4000 && !strcmp(pThis->GetName(panel), "HudGMOD"))
		dismay->m_pDraw = panel;

	
	//dismay->SetDrawColor(255,255,255);
	//dismay->m_pSurface->DrawFilledRect(0, 0, 500, 500);
	// test purposes
	char tmp[256];
	int x, y, w, h;
	pThis->GetPos(panel, x, y);
	pThis->GetSize(panel, w, h);
	sprintf(tmp, "%s x%i y%i w%i h%i", pThis->GetName(panel), x, y, w, h);
	//if(pThis->IsFullyVisible(panel))
	//	MessageBox(0, tmp, tmp, 0);
	lua_State* L = dismay->m_pDLua->m_luaState;
	if(dismay->m_nAppID != 4000 && !strcmp(pThis->GetName(panel), "FocusOverlayPanel"))
	{
		lua_pushcfunction(L, Error);
		lua_pushglobaltable(L);
		lua_getfield(L, -1, "hook");
		lua_getfield(L, -1, "Call");
		lua_pushstring(L, "DrawOverlay");
		dismay->SetDrawColor(255,255,255,255);
	//	MessageBox(0, "a", "a", 0);
		lua_pcall(L, 1, 0, -3);
		lua_pop(L, 3);
		//dismay->SetDrawColor(0, 0, 0,255);
		//MessageBox(0, "b", "b", 0);
		//dismay->DrawLine(0, 0, 100, 100);
		//MessageBox(0, "b", "b", 0);
		dismay->m_pEngineRender->Render(panel);
	}

	return ret;
}


DWORD* old_setvalue = 0;
bool bSet = false;

void __fastcall NameSetValue(ConVar* pConVar, void*, const char* pszNewValue)
{
	const char* r = pszNewValue;
	typedef void (__thiscall* o_hc)(ConVar*, const char*);
	if(pConVar == dismay->m_pNameConvar && strcmp(dismay->m_szName,""))
	{
		r = dismay->m_szName;
	}
	MessageBox(0, "a", "a", 0);
	bSet = !bSet;
	if(bSet)
		((o_hc)dismay->m_pvtNameConvar->GetOld(10))(pConVar, r);
	MessageBox(0, "b", "b", 0);
	//((o_hc)old_setvalue)(pConVar, r);
}