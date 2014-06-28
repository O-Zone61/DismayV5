#include "DBaseEntity.h"
#include "DLua.h"
#include <fstream>
#include "Garry/dismay_cinput.h"
#include "Garry/dismay_cengineclient.h"
#include "Garry/dismay_ccliententitylist.h"
#include "Garry/dismay_cmatsystemsurface.h"
#include "DBaseEntity.h"
#include "DDismay.h"
#include "ClientClass.h"

#define FUNC(name) int name(lua_State* L)

inline Color GetColor(lua_State* L, int stack)
{
	lua_pushvalue(L, stack);
	lua_getfield(L, -1, "r");
	int r = (int)lua_tonumber(L, -1);
	lua_pushvalue(L, stack);
	lua_getfield(L, -1, "g");
	int g = (int)lua_tonumber(L, -1);
	lua_getfield(L, -1, "b");
	lua_pushvalue(L, stack);
	int b = (int)lua_tonumber(L, -1);
	lua_getfield(L, stack, "a");
	int a = (int)lua_tonumber(L, -1);
	return Color(r, g, b, a);
}

FUNC(Angle__Vector)
{
	QAngle ang = GetAngle(L, 1);
	Vector ret; 
	AngleVectors(ang, &ret);
	lua_pop(L, 1);
	PushVector(L, ret);
	return 1;
}

FUNC(bit__bor)
{
	lua_pushnumber(L, (lua_Number)((unsigned int)lua_tonumber(L, 1) | (unsigned int)lua_tonumber(L, 2)));
	return 1;
}
FUNC(bit__band)
{
	lua_pushnumber(L, (lua_Number)((unsigned int)lua_tonumber(L, 1) & (unsigned int)lua_tonumber(L, 2)));
	return 1;
}

FUNC(CUserCmd__ClearButtons)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c) 
	{
		c->buttons = 0;
	}
	return 0;
}
FUNC(CUserCmd__SetSideMove)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		c->sidemove = (short)lua_tonumber(L, 2);
	return 0;
}
FUNC(CUserCmd__GetSideMove)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		lua_pushnumber(L, (double)c->sidemove);
	else
		lua_pushnumber(L, 0);
	return 1;
}
FUNC(CUserCmd__SetForwardMove)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		c->forwardmove = (short)lua_tonumber(L, 2);
	return 0;
}
FUNC(CUserCmd__GetForwardMove)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		lua_pushnumber(L, (double)c->forwardmove);
	else
		lua_pushnumber(L, 0);
	return 1;
}
FUNC(CUserCmd__GetButtons)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c) 
	{
		lua_pushnumber(L, c->buttons);
	}
	else
		lua_pushnumber(L, 0);
	return 1;
}
FUNC(Vector__ToScreen)
{
	Vector world = GetVector(L, 1);
	Vector screen;
	dismay->WorldToScreen(world, screen);
	PushVector(L, screen);
	return 1;
}
FUNC(CUserCmd__SetButtons)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c) 
		c->buttons = (int)lua_tonumber(L, 2);
	return 0;
}
FUNC(CUserCmd__GetCommandNumber)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c) 
	{
		lua_pushnumber(L, c->command_number);
	}
	else
		lua_pushnumber(L, 0);
	return 1;
}
FUNC(CUserCmd__SetCommandNumber)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c) 
	{
		c->command_number = (int)lua_tonumber(L, 2);
	}
	else
		lua_pushnumber(L, 0);
	return 0;
}
FUNC(CUserCmd__SetViewAngles)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c) 
		c->viewangles = GetAngle(L, 2);
	return 0;
}
FUNC(CUserCmd__GetViewAngles)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		PushAngle(L, c->viewangles);
	else
		PushAngle(L, QAngle());
	return 1;
}
FUNC(CUserCmd__GetMouseX)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		lua_pushnumber(L, (double)c->mousedx);
	else
		lua_pushnumber(L, 0);
	return 1;
}
FUNC(CUserCmd__SetMouseX)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		c->mousedx = (short)lua_tonumber(L, 2);
	return 0;
}
FUNC(CUserCmd__GetMouseY)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		lua_pushnumber(L, (double)c->mousedy);
	else
		lua_pushnumber(L, 0);
	return 1;
}
FUNC(CUserCmd__SetMouseY)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		c->mousedy = (short)lua_tonumber(L, 2);
	return 0;
}
FUNC(CUserCmd__KeyDown)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
	{
		lua_pushboolean(L, (c->buttons & (int)lua_tonumber(L, 2)) == (int)lua_tonumber(L, 2));
	}
	else
		lua_pushboolean(L, false);
	return 1;
}
FUNC(CUserCmd__RemoveKey)
{
	CUserCmd* c = GetCUserCmd(L, 1);
	if(c)
		if((c->buttons & (int)lua_tonumber(L, 2)) == (int)lua_tonumber(L, 2))
			c->buttons -= (int)lua_tonumber(L, 2);
	return 0;
}
FUNC(Entity__SetFlags)
{
	C_BaseEntity* ent = GetEntity(L, 1);
	if(!ent->IsValid()) return 0;
	*ent->GetFlagPtr() = (int)lua_tonumber(L, 1);
	return 0;
}
FUNC(Entity__AddFlags)
{
	C_BaseEntity* ent = GetEntity(L, 1);
	if(!ent->IsValid()) return 0;
	*ent->GetFlagPtr() |= (int)lua_tonumber(L, 1);
	return 0;
}
FUNC(Entity__RemoveFlags)
{
	C_BaseEntity* ent = GetEntity(L, 1);
	if(!ent->IsValid()) return 0;
	*ent->GetFlagPtr() &= ~(int)lua_tonumber(L, 1);
	return 0;
}
FUNC(player__GetAll)
{
	lua_newtable(L);
	for(int i = 1; i <= dismay->m_pEngineClient->GetMaxClients();i++)
	{
		if(dismay->m_pClientEntityList->GetClientEntity(i)->IsPlayer())
		{
			PushEntity(L, dismay->m_pClientEntityList->GetClientEntity(i));
			lua_rawseti(L, -2, i);
		}
	}
	return 1;
}

char* GetFileText02(const char* pszFileLoc) {
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
FUNC(Entity__GetVar)
{
	IClientEntity* ent	= GetEntity(L, 1);
	const char*	varname	= lua_tostring(L, 2);
	RecvProp* prop = GetRecvProp(varname);
	if(prop)
	{
		if(prop->GetType() == RECV_VECTOR)
			PushVector(L, getmember(Vector, ent, prop->GetOffset()));
		else if(prop->GetType() == RECV_STRING)
			lua_pushstring(L, getmember(char*, ent, prop->GetOffset()));
		else if(prop->GetType() == RECV_FLOAT)
			lua_pushnumber(L, (lua_Number)getmember(float, ent, prop->GetOffset()));
		else if(prop->GetType() == RECV_INT)
			lua_pushnumber(L, (lua_Number)getmember(int, ent, prop->GetOffset()));
		return 1;
	}
	return 0;
}

FUNC(surface__DrawOutlinedRect)
{
	dismay->m_pSurface->DrawOutlinedRect((int)lua_tonumber(L, 1), (int)lua_tonumber(L, 2), (int)lua_tonumber(L, 3), (int)lua_tonumber(L, 4));
	return 0;
}

FUNC(surface__DrawRect)
{
	dismay->DrawRect((int)lua_tonumber(L, 1), (int)lua_tonumber(L, 2), (int)lua_tonumber(L, 3), (int)lua_tonumber(L, 4));
	return 0;
}

FUNC(IsInGame)
{
	lua_pushboolean(L, dismay->m_pEngineClient->IsInGame());
	return 1;
}

FUNC(surface__SetDrawColor)
{
	int r, g, b, a;
	if(lua_istable(L, 1))
	{
		Color col = GetColor(L, 1);
		r = col.r();
		g = col.g();
		b = col.b();
		a = col.a();
	}
	else
	{
		r = (int)lua_tonumber(L, 1);
		g = (int)lua_tonumber(L, 2);
		b = (int)lua_tonumber(L, 3);
		a = (int)lua_tonumber(L, 4);
	}
	dismay->m_pSurface->DrawSetColor(r, g, b, a);
	return 0;
}

FUNC(surface__DrawLine)
{
	MessageBox(0, "a", "a", 0);
	dismay->DrawLine((int)lua_tonumber(L, 1), (int)lua_tonumber(L, 2), (int)lua_tonumber(L, 3), (int)lua_tonumber(L, 4));
	
	MessageBox(0, "b", "b", 0);
	return 0;
}

FUNC(Entity__Nick)
{
	IClientEntity* ent = GetEntity(L, 1);
	lua_pushstring(L, ent->Nick());
	return 1;
}
FUNC(Entity__IsDormant)
{
	IClientEntity* ent = GetEntity(L, 1);
	lua_pushboolean(L, ent->IsDormant());
	return 1;
}
FUNC(Entity__OBBMins)
{
	IClientEntity* ent = GetEntity(L, 1);
	PushVector(L, ent->OBBMins());
	return 1;
}
FUNC(Entity__OBBMaxs)
{
	IClientEntity* ent = GetEntity(L, 1);
	PushVector(L, ent->OBBMaxs());
	return 1;
}
FUNC(ScrW)
{
	int w, h;
	dismay->m_pEngineClient->GetScreenSize(w, h);
	lua_pushnumber(L, (lua_Number)w);
	return 1;
}
FUNC(ScrH)
{
	int w, h;
	dismay->m_pEngineClient->GetScreenSize(w, h);
	lua_pushnumber(L, (lua_Number)h);
	return 1;
}
FUNC(Entity__IsOnGround)
{
	IClientEntity* ent = GetEntity(L, 1);
	lua_pushboolean(L, (ent->GetFlags() & 1) == 1);
	return 1;
}
FUNC(__tc)
{
	MessageBox(0, lua_tostring(L, -1), lua_tostring(L, -1), 0);
	return 0;
}
FUNC(LocalPlayer)
{
	PushEntity(L, dismay->m_pClientEntityList->GetClientEntity(dismay->m_pEngineClient->GetLocalPlayer()));
	return 1;
}
FUNC(include)
{
	char tmp[512];
	sprintf(tmp, "C:\\dismay\\%s", lua_tostring(L, 1));
	char* x = GetFileText02(tmp);
	dismay->m_pDLua->RunString(x);
	delete[] x;
	return 0;
}


DLua::DLua()
{
	m_luaState = luaL_newstate();

	luaL_openlibs(m_luaState);
	lua_State* L = m_luaState;
	lua_pushglobaltable(L);
	lua_pushcfunction(L, print);
	lua_setfield(L, -2, "print");
	lua_pop(L, 1);
	
	lua_pushglobaltable(L);
	lua_pushcfunction(L, __tc);
	lua_setfield(L, -2, "_tc");
	lua_pushcfunction(L, LocalPlayer);
	lua_setfield(L, -2, "LocalPlayer");
	lua_pop(L, 1);
	
	lua_pushglobaltable(L);
	lua_newtable(L);
	lua_pushcfunction(L, bit__bor);
	lua_setfield(L, -2, "bor");
	lua_pushcfunction(L, bit__band);
	lua_setfield(L, -2, "band");
	lua_setfield(L, -2, "bit");
	lua_newtable(L);
	lua_pushcfunction(L, surface__DrawLine);
	lua_setfield(L, -2, "DrawLine");
	lua_pushcfunction(L, surface__SetDrawColor);
	lua_setfield(L, -2, "SetDrawColor");
	lua_pushcfunction(L, surface__DrawOutlinedRect);
	lua_setfield(L, -2, "DrawOutlinedRect");
	lua_pushcfunction(L, surface__DrawRect);
	lua_setfield(L, -2, "DrawRect");
	lua_setfield(L, -2, "surface");
	lua_pushcfunction(L, IsInGame);
	lua_setfield(L, -2, "IsInGame");
	lua_pushcfunction(L, ScrW);
	lua_setfield(L, -2, "ScrW");
	lua_pushcfunction(L, ScrH);
	lua_setfield(L, -2, "ScrH");
	lua_pop(L, 1);
	
	luaL_newmetatable(m_luaState, "Entity");
	lua_pushcclosure(m_luaState, Entity__SetFlags, 0);
	lua_setfield(L, -2, "SetFlags");
	lua_pushcclosure(m_luaState, Entity__GetVar, 0);
	lua_setfield(L, -2, "GetVar");
	lua_pushcclosure(m_luaState, Entity__AddFlags, 0);
	lua_setfield(L, -2, "AddFlags");
	lua_pushcclosure(m_luaState, Entity__RemoveFlags, 0);
	lua_setfield(L, -2, "RemoveFlags");
	lua_pushcclosure(m_luaState, Entity__IsOnGround, 0);
	lua_setfield(L, -2, "IsOnGround");
	lua_pushcclosure(m_luaState, Entity__IsOnGround, 0);
	lua_setfield(L, -2, "OnGround");
	lua_pushcclosure(m_luaState, Entity__Nick, 0);
	lua_setfield(L, -2, "Nick");
	lua_pushcclosure(m_luaState, Entity__IsDormant, 0);
	lua_setfield(L, -2, "IsDormant");
	lua_pushcclosure(m_luaState, Entity__OBBMins, 0);
	lua_setfield(L, -2, "OBBMins");
	lua_pushcclosure(m_luaState, Entity__OBBMaxs, 0);
	lua_setfield(L, -2, "OBBMaxs");
	lua_pushvalue(m_luaState, -1);
	lua_setfield(m_luaState, -2, "__index");
	lua_pop(m_luaState, 1);

	luaL_newmetatable(m_luaState, "CUserCmd");
	lua_pushcclosure(m_luaState, CUserCmd__ClearButtons, 0);
	lua_setfield(m_luaState, -2, "ClearButtons");
	lua_pushcclosure(m_luaState, CUserCmd__GetButtons, 0);
	lua_setfield(m_luaState, -2, "GetButtons");
	lua_pushcclosure(m_luaState, CUserCmd__SetButtons, 0);
	lua_setfield(m_luaState, -2, "SetButtons");
	lua_pushcclosure(m_luaState, CUserCmd__SetViewAngles, 0);
	lua_setfield(m_luaState, -2, "SetViewAngles");
	lua_pushcclosure(m_luaState, CUserCmd__GetViewAngles, 0);
	lua_setfield(m_luaState, -2, "GetViewAngles");
	lua_pushcclosure(m_luaState, CUserCmd__SetCommandNumber, 0);
	lua_setfield(m_luaState, -2, "SetCommandNumber");
	lua_pushcclosure(m_luaState, CUserCmd__GetCommandNumber, 0);
	lua_setfield(m_luaState, -2, "GetCommandNumber");
	lua_pushcclosure(m_luaState, CUserCmd__SetSideMove, 0);
	lua_setfield(m_luaState, -2, "SetSideMove");
	lua_pushcclosure(m_luaState, CUserCmd__GetSideMove, 0);
	lua_setfield(m_luaState, -2, "GetSideMove");
	lua_pushcclosure(m_luaState, CUserCmd__SetForwardMove, 0);
	lua_setfield(m_luaState, -2, "SetForwardMove");
	lua_pushcclosure(m_luaState, CUserCmd__GetForwardMove, 0);
	lua_setfield(m_luaState, -2, "GetForwardMove");
	lua_pushcclosure(m_luaState, CUserCmd__SetMouseX, 0);
	lua_setfield(m_luaState, -2, "SetMouseX");
	lua_pushcclosure(m_luaState, CUserCmd__GetMouseX, 0);
	lua_setfield(m_luaState, -2, "GetMouseX");
	lua_pushcclosure(m_luaState, CUserCmd__SetMouseY, 0);
	lua_setfield(m_luaState, -2, "SetMouseY");
	lua_pushcclosure(m_luaState, CUserCmd__GetMouseY, 0);
	lua_setfield(m_luaState, -2, "GetMouseY");
	lua_pushcclosure(m_luaState, CUserCmd__KeyDown, 0);
	lua_setfield(m_luaState, -2, "KeyDown");
	lua_pushcclosure(m_luaState, CUserCmd__RemoveKey, 0);
	lua_setfield(m_luaState, -2, "RemoveKey");
	lua_pushvalue(m_luaState, -1);
	lua_setfield(m_luaState, -2, "__index");
	
	lua_pushglobaltable(L);
	lua_pushcfunction(L, include);
	lua_setfield(m_luaState, -2, "include");
	
	lua_pop(L, 2);
	
	
	luaL_newmetatable(L, "Angle");
	lua_pushcfunction(L, Angle__Vector);
	lua_setfield(L, -2, "Vector");
	lua_pushvalue(L, -1);
	lua_setfield(m_luaState, -2, "__index");
	lua_pop(L, 1);
	
	luaL_newmetatable(L, "Vector");
	lua_pushcfunction(L, Vector__ToScreen);
	lua_setfield(L, -2, "ToScreen");
	lua_pushvalue(L, -1);
	lua_setfield(m_luaState, -2, "__index");
	lua_pop(L, 1);

	char* file = dismay->FetchFileFromWeb(4);
	RunString(file);
	delete[] file;


	lua_getglobal(L, "player");
	lua_pushcfunction(L, player__GetAll);
	lua_setfield(L, -2, "GetAll");
	lua_pop(L, 1);

	lua_pushcfunction(L, Error);
	lua_pushglobaltable(L);
	lua_getfield(L, -1, "hook");
	lua_getfield(L, -1, "Call");
	lua_pushstring(L, "Startup");
	lua_pcall(L, 1, 0, -3);
	lua_pop(L, 3);
}



