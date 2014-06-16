#include "DVector.h"
#include "DDismay.h"
#include "IClientFriends.h"
#include "DBaseEntity.h"
#include "checksum_md5.h"
#include <fstream>
#include "dismay_inetchannel.h"
#include "dismay_vpanel.h"
#include "CSteamID.h"
#include <string>
#include "Garry/dismay_cbaseluainterface.h"
#include "Garry/dismay_cluainterface.h"
#include "Garry/dismay_cluashared.h"
#include "Garry/dismay_cengineclient.h"
#include "Garry/dismay_cpanelwrapper.h"
#include "Garry/dismay_ccliententitylist.h"
#include "DEngineRender.h"
#include "DVTable.h"


#define DEG2RAD(x) ((float)x / 57.2957795f)
#define RAD2DEG(x) ((float)x * 57.2957795f)


extern DDismay* dismay;

#define lua (L->luabase)

template<class _type>
_type Get(lua_State* L, int stack)
{
	return (_type)L->luabase->GetUserdata(stack)->data;
}

char* GetFileText(const char* pszFileLoc) {
	std::ifstream input;
	input.open(pszFileLoc, std::ios::in);
	std::string fileContents;
	std::string line;
	if(input.is_open()){
		while(std::getline(input, line)){
			fileContents += line + std::string("\n");
		}
		input.close();
		
		char* tmp = new char[fileContents.length() + 1];
		std::strcpy(tmp, fileContents.c_str());

		return tmp;
	}
	return "";
}

struct lua_State
{
	unsigned char			_ignore_this_common_lua_header_[69];
	CBaseLuaInterface*		luabase;
};

template <class T>
T GET(lua_State* L, int stackpos) {
	return T(*reinterpret_cast<T*>(((UserData*)L->luabase->GetUserdata(stackpos))->data));
}
#define VSTDLIB_INTERFACE extern "C" __declspec( dllexport )
VSTDLIB_INTERFACE void	RandomSeed( int iSeed );
VSTDLIB_INTERFACE float	RandomFloat( float flMinVal = 0.0f, float flMaxVal = 1.0f );
VSTDLIB_INTERFACE float	RandomFloatExp( float flMinVal = 0.0f, float flMaxVal = 1.0f, float flExponent = 1.0f );
VSTDLIB_INTERFACE int	RandomInt( int iMinVal, int iMaxVal );
VSTDLIB_INTERFACE float	RandomGaussianFloat( float flMean = 0.0f, float flStdDev = 1.0f );

int SendMsg(lua_State* L)
{
	const char* str = lua->GetString(2, 0);
	lua->PushBool(dismay->m_pClientFriends->SendMsgToFriend(dismay->m_pClientFriends->GetFriendByIndex((int32)lua->GetNumber(1),
		k_EFriendFlagImmediate), k_EChatEntryTypeChatMsg, str, strlen(str)));
	return 1;
}
int GetFriendCount(lua_State* L)
{
	lua->PushNumber(dismay->m_pClientFriends->GetFriendCount(k_EFriendFlagImmediate));
	return 1;
}
int GetFriendName(lua_State* L)
{
	lua->PushString(dismay->m_pClientFriends->GetFriendPersonaName(dismay->m_pClientFriends->GetFriendByIndex((int32)lua->GetNumber(1), k_EFriendFlagImmediate)), 0);
	return 1;
}
int InviteFriendToRoom(lua_State* L)
{
	IClientFriends* m = dismay->m_pClientFriends;
	lua->PushBool(m->InviteUserToChatRoom(m->GetChatRoomByIndex((int32)lua->GetNumber(2)), m->GetFriendByIndex((int32)lua->GetNumber(1), k_EFriendFlagImmediate)));
	return 1;
}
int GetRoomCount(lua_State* L)
{
	IClientFriends* m = dismay->m_pClientFriends;
	lua->PushNumber((double)m->GetChatRoomCount());
	return 1;
}
int GetRoomName(lua_State* L)
{
	IClientFriends* m = dismay->m_pClientFriends;
	lua->PushString(m->GetChatRoomName(m->GetChatRoomByIndex((int32)lua->GetNumber(1))), 0);
	return 1;
}

int CreateRoom(lua_State* L)
{
	IClientFriends* m = dismay->m_pClientFriends;
	m->CreateChatRoom(k_EChatRoomTypeFriend, 0, lua->GetString(1, 0), k_ELobbyTypePrivate, CSteamID(), CSteamID(), CSteamID(), 0, 0, 0); 
	return 0;
}


int SetCommandNumber(lua_State* L)
{
	dismay->m_iForceNumber = (int)lua->GetNumber(1);
	return 0;
}

int SetIGN(lua_State* L)
{
	strcpy(dismay->m_szName, lua->GetString(1, 0));
	typedef void (__thiscall* n)(ConVar*, const char*);
	((n)dismay->m_pvtNameConvar->m_pNewVTable[SETVALUE])(dismay->m_pNameConvar, dismay->m_szName);
	return 0;
}

int RequestFile(lua_State* L)
{
	((INetChannel*)dismay->m_pEngineClient->GetNetChannelInfo())->RequestFile(lua->GetString(1, 0));
	return 0;
}

int Repaint(lua_State* L)
{
	if(dismay->m_pDraw)
	{
		dismay->m_pPanel->Repaint(dismay->m_pDraw);
		dismay->m_pPanel->PaintTraverse(dismay->m_pDraw, true, true);
	}
	return 0;
}

int GetPred(lua_State* L)
{
	int iNum			= (int)lua->GetNumber(1);
	unsigned int uiSeed = MD5_PseudoRandom(iNum) & 0x7FFFFFFF;
	QAngle angAim(GET<QAngle>(L, 2));
	Vector vecSpread(GET<Vector>(L, 3));

	RandomSeed((uiSeed & 255));

    float x = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
    float y = RandomFloat(-0.5, 0.5) + RandomFloat(-0.5, 0.5);
	  
    Vector forward, right, up;

    AngleVectors(angAim, &forward, &right, &up);
	Vector spreaded = forward + (x * vecSpread.x * right) + (y * vecSpread.y * up);

	CBaseLuaInterface* l = L->luabase;
	l->PushSpecial(0);
	l->GetField(-1, "Vector");
	l->PushNumber((double)spreaded.x);
	l->PushNumber((double)spreaded.y);
	l->PushNumber((double)spreaded.z);
	l->Call(3, 1);

	char t[256];
	sprintf(t, "1: Angle(%f, %f, %f)\n2: Vector(%f, %f, %f)\n3: Vector(%f, %f, %f)\n4: Vector(%f, %f, %f)", angAim.p, angAim.y, angAim.r, forward.x, forward.y, forward.z, right.x, right.y,right.z, up.x,up.y,up.z);

	return 2;
}

int SetSteamName(lua_State* L)
{
	dismay->m_pClientFriends->SetPersonaName(lua->GetString(1, 0));
	return 0;
}

int SetTickCount(lua_State* L)
{
	int ind = *(int*)lua->GetUserdata(1)->data;
	IClientEntity* ply = dismay->m_pClientEntityList->GetClientEntityFromHandle(ind);
	*ply->GetTickCountPtr() = (int)lua->GetNumber(2);
	return 0;
}

int GetTickCount(lua_State* L)
{
	IClientEntity* ply;
	int ind = *(int*)lua->GetUserdata(1)->data;
	ply = dismay->m_pClientEntityList->GetClientEntityFromHandle(ind);
	lua->PushNumber(ply->GetTickCount());
	return 1;
}

int IsDormant(lua_State* L)
{
	int ind = *(int*)lua->GetUserdata(1)->data;
	IClientEntity* ply = dismay->m_pClientEntityList->GetClientEntityFromHandle(ind);
	lua->PushBool((bool)ply->IsDormant());
	return 1;
}

int GetCmdSendState(lua_State* L)
{
	bool a = dismay->m_bSendCmds;
	lua->PushBool(a);
	return 1;
}

int GetCmdRepState(lua_State* L)
{
	bool a = dismay->m_bRepCmds;
	lua->PushBool(a);
	return 1;
}

int SetCmdRepState(lua_State* L)
{
	dismay->m_bRepCmds = lua->GetBool(1);
	return 0;
}

int SetCmdSendState(lua_State* L)
{
	dismay->m_bSendCmds = lua->GetBool(1);
	return 0;
}

int Labort(lua_State* L)
{
	abort();
	return 0;
}


int RunMenu(lua_State* L)
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	CLuaInterface* cl = dismay->m_pLua->GetLuaInterface(2);
	if(!cl)
	{
		lua->PushBool(false);
		return 1;
	}
	((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(cl, "", "", lua->GetString(1, 0), true, true);
	lua->PushBool(true);
	return 1;
}

int RunDismay(lua_State* L)
{
	dismay->m_pDLua->RunString((char*)lua->GetString(1, 0));
	return 0;
}

int RunClient(lua_State* L)
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	CLuaInterface* cl = dismay->m_pLua->GetLuaInterface(0);
	if(!cl)
	{
		lua->PushBool(false);
		return 1;
	}
	((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(cl, "", "", lua->GetString(1, 0), true, true);
	lua->PushBool(true);
	return 1;
}

int OpenMenu(lua_State* L)
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	CLuaInterface* cl = dismay->m_pLua->GetLuaInterface(2);
	if(!cl)
	{
		lua->PushBool(false);
		return 1;
	}
	char* run = GetFileText(lua->GetString(1, 0));
	((RunStringFn)dismay->m_pvtLuaMInt->GetOld(RUNSTRING))(cl, "", "", run, true, true);
	delete[] run;
	lua->PushBool(true);
	return 1;
}

int Paint(lua_State* L)
{
	dismay->m_pEngineRender->Render(0);
	return 0;
}

int _tc(lua_State* L)
{
	MessageBox(0, lua->GetString(1, 0), lua->GetString(2, 0), MB_OK);
	return 0;
}

int OpenClient(lua_State* L)
{
	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	CLuaInterface* cl = dismay->m_pLua->GetLuaInterface(0);
	if(!cl)
	{
		lua->PushBool(false);
		return 1;
	}
	char* run = GetFileText(lua->GetString(1, 0));
	((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(cl, "", "", run, true, true);
	delete[] run;
	lua->PushBool(true);
	return 1;
}

int Menu__index(lua_State* L);

int Menu__newindex(lua_State* L)
{
	if(!strcmp(lua->GetString(2, 0), "m_fnCallback")) 
	{
		lua->GetMetaTable(1);
		lua->Push(3);
		lua->SetField(-1, "m_fnCallback");
		lua->Pop(1);
	}
	return 0;
}

int CreateMenuItem(lua_State* L)
{
	const char* tmp = lua->GetString(1, 0);
	char* n = new char[128];
	strcpy(n, tmp);

	UserData* ud = (UserData*)lua->NewUserdata(sizeof(UserData));
	int ref = (int)lua->ReferenceCreate();
	ud->data = new DMenuItem(n, ref);
	lua->ReferencePush(ref);
	lua->CreateTable();
	lua->PushCFunction(Menu__index);
	lua->SetField(-2, "__index");
	lua->PushCFunction(Menu__newindex);
	lua->SetField(-2, "__newindex");
	lua->Push(2);
	lua->SetField(-2, "m_fnCallback");
	lua->SetMetaTable(-2);


	dismay->m_pEngineRender->RegisterItem((DMenuItem*)ud->data);

	return 1;
}

int SetItemActive(lua_State* L)
{
	UserData* item = lua->GetUserdata(1);
	if(item->data)
	{
		((DMenuItem*)item->data)->m_bActive = lua->GetBool(2);
		lua->PushBool(true);
		
	}
	else lua->PushBool(false);
	return 1;
}

int SetItemName(lua_State* L)
{
	UserData* item = lua->GetUserdata(1);
	if(item->data)
	{
		const char* str = lua->GetString(2, 0);
		char* r = new char[strlen(str)];
		DMenuItem* l = (DMenuItem*)item->data;
		strcpy((char*)l->m_szName, str);
		l->m_bDeleteString = 0;
		lua->PushBool(true);
	}
	else lua->PushBool(false);
	return 1;
}

int SetItemCallback(lua_State* L)
{
	UserData* item = lua->GetUserdata(1);
	if(item->data)
	{
		lua->Push(1);
		lua->GetCFunction(2);
		lua->SetField(-2, "m_fnCallback");
		lua->PushBool(true);
	}
	else lua->PushBool(false);
	return 1;
}

int LoadWebScriptClient(lua_State* L)
{
	int iName = (int)lua->GetNumber(1);
	if(iName == 0 || iName == 2)
		return 0;

	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	CLuaInterface* cl = dismay->m_pLua->GetLuaInterface(0);
	if(!cl || !strcmp(lua->GetString(2, 0), ""))
	{
		lua->PushBool(false);
		return 1;
	}
	unsigned int bytes = 40000;
	if(lua->GetBool(3))
		bytes = (unsigned int)lua->GetNumber(3);
	((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(cl, "", "", dismay->FetchFileFromWeb(iName, lua->GetString(2,0), bytes), true, true);
	lua->PushBool(true);
	return 1;
}
int LoadWebScriptMenu(lua_State* L)
{
	int iName = (int)lua->GetNumber(1);
	if(iName == 0 || iName == 2)
		return 0;

	typedef void* (__thiscall* RunStringFn)(CLuaInterface*, const char*, const char*, const char*, bool, bool);

	CLuaInterface* cl = dismay->m_pLua->GetLuaInterface(2);
	if(!cl || !strcmp(lua->GetString(2, 0), ""))
	{
		lua->PushBool(false);
		return 1;
	}
	((RunStringFn)dismay->m_pvtLuaCInt->GetOld(RUNSTRING))(cl, "", "", dismay->FetchFileFromWeb(iName, lua->GetString(2,0)), true, true);
	lua->PushBool(true);
	return 1;
}

int RemoveMenuItem(lua_State* L)
{
	UserData* item = lua->GetUserdata(1);
	if(item->data)
	{
		dismay->m_pEngineRender->UnregisterItem((DMenuItem*)item->data);
		delete[] item->data;
		item->data = 0;
		lua->PushBool(true);
	}
	else lua->PushBool(false);
	return 1;
}

int Menu__index(lua_State* L)
{
	char* string = (char*)lua->GetString(2, 0);
	if(!strcmp(string, "SetActive"))
		lua->PushCFunction(SetItemActive);
	else if(!strcmp(string, "SetCallback"))
		lua->PushCFunction(SetItemCallback);
	else if(!strcmp(string, "SetName"))
		lua->PushCFunction(SetItemName);
	else if(!strcmp(string, "Delete"))
		lua->PushCFunction(RemoveMenuItem);
	else if(!strcmp(string, "m_fnCallback"))
	{
		lua->Push(1);
		lua->GetMetaTable(-1);
		lua->GetField(-1, "m_fnCallback");
		int iRef = (int)lua->ReferenceCreate();
		lua->Pop(3);
		lua->ReferencePush(iRef);
		lua->ReferenceFree(iRef);
	}
	else lua->PushNil();
	return 1;
}