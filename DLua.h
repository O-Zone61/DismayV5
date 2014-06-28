#ifndef DLUA_H
#define DLUA_H
class DLua;

#define TYPE_CUSERCMD		20
#define TYPE_ENTITY			21

#define LUA_SUCCESS		0
#define LUA_YIELD		1
#define LUA_ERRRUN		2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM		4

#include "Forward.h"
#include "DDismay.h"
#include "Garry/dismay_cinput.h"
#include <Windows.h>
#include <string>
#include "DVector.h"
#include "Garry/dismay_cluainterface.h"
#include "Garry/dismay_cluashared.h"
#include "Garry/dismay_cbaseluainterface.h"
#include "lua.hpp"
extern DDismay* dismay;

typedef int(*lua_CFunction) (lua_State *L);
typedef double lua_Number;
typedef int lua_Integer;
#define LUA_TNONE               (-1)
#define LUA_TNIL                0
#define LUA_TBOOLEAN            1
#define LUA_TLIGHTUSERDATA      2
#define LUA_TNUMBER             3
#define LUA_TSTRING             4
#define LUA_TTABLE              5
#define LUA_TFUNCTION           6
#define LUA_TUSERDATA           7
#define LUA_TTHREAD             8
#define LUA_MULTRET     (-1)
/*

typedef int (__cdecl* CFunc)(lua_State* L);
__forceinline void* GetLuaFunc(const char* functoget)
{
	auto ret = (void*)GetProcAddress(GetModuleHandle("lua_shared.dll"), functoget);
	if(!ret) 
	{
		char t [32];
		sprintf(t, "%s is NULL", functoget);
		dismay->error(t);
	}
	return ret;
}
typedef struct lua_Debug {
  int _event;
  const char *name;        
  const char *namewhat;  
  const char *what;       
  const char *source;      
  int currentline;        
  int nups;               
  int linedefined;          
  int lastlinedefined;      
  char short_src[60];		
  int i_ci;
} lua_Debug;

static auto lua_tolstring		= ((const char* (*)(lua_State*, int, int))(GetLuaFunc("lua_tolstring")));
static auto luaL_loadbuffer		= ((int(*)(lua_State* L, const char* buf, size_t len, const char* chunkname))(GetLuaFunc("luaL_loadbuffer")));
static auto luaL_newstate		= ((lua_State* (*)(void))(GetLuaFunc("luaL_newstate")));
static auto luaL_openlibs		= ((void(*)(lua_State*))(GetLuaFunc("luaL_openlibs")));
static auto luaL_loadstring		= ((int(*)(lua_State*, const char*))(GetLuaFunc("luaL_loadstring")));
static auto lua_pcall			= ((int(*)(lua_State*, int, int, int))(GetLuaFunc("lua_pcall")));
static auto lua_settop			= ((void(*)(lua_State* L, int stack))(GetLuaFunc("lua_settop")));
static auto lua_getfield		= ((void(*)(lua_State* L, int stack, const char* name))(GetLuaFunc("lua_getfield")));
static auto lua_setfield		= ((void(*)(lua_State* L, int stack, const char* name))(GetLuaFunc("lua_setfield")));
static auto lua_pushvalue		= ((void(*)(lua_State* L, int))(GetLuaFunc("lua_pushvalue")));
static auto lua_pushcclosure	= ((void(*)(lua_State* L, lua_CFunction func, int null))(GetLuaFunc("lua_pushcclosure")));
static auto lua_tonumber		= ((double(*)(lua_State* L, int stack))(GetLuaFunc("lua_tonumber")));
static auto lua_touserdata		= (void* (*)(lua_State* L, int stack))GetLuaFunc("lua_touserdata");

static auto lua_pushnumber		= (void(*)(lua_State *L, lua_Number n))GetLuaFunc("lua_pushnumber");
static auto lua_gettop			= (int(*)(lua_State *L))GetLuaFunc("lua_gettop");
static auto lua_type			= (int(*) (lua_State *L, int index))GetLuaFunc("lua_type");
static auto lua_tointeger		= (lua_Integer(*) (lua_State *L, int index))GetLuaFunc("lua_tointeger");
static auto lua_pushlstring		= (void(*) (lua_State *L, const char *s, size_t len))GetLuaFunc("lua_pushlstring");
//static auto lua_rawgeti = (HEADER)GetLuaFunc("lua_rawgeti");
static auto luaL_error			= (int(*) (lua_State *L, const char *fmt, ...))GetLuaFunc("luaL_error");
static auto lua_call			= (void(*) (lua_State *L, int nargs, int nresults))GetLuaFunc("lua_call");
static auto lua_createtable		= (void(*) (lua_State *L, int narr, int nrec))GetLuaFunc("lua_createtable");
static auto lua_pushstring		= (void(*) (lua_State *L, const char *s))GetLuaFunc("lua_pushstring");
static auto lua_pushinteger		= (void(*)		(lua_State *L, int n))GetLuaFunc("lua_pushinteger");
static auto lua_pushboolean		= (void(*)(lua_State *L, bool b))GetLuaFunc("lua_pushboolean");
static auto lua_toboolean		= (bool(*) (lua_State *L, int index))GetLuaFunc("lua_toboolean");
static auto lua_pushnil			= (void(*) (lua_State* L))GetLuaFunc("lua_pushnil");
static auto lua_getinfo			= (int (*)(lua_State *L, const char *what, lua_Debug *ar))GetLuaFunc("lua_getinfo");
static auto lua_atpanic			= (lua_CFunction(*)(lua_State *L, lua_CFunction panicf))GetLuaFunc("lua_atpanic");
static auto lua_close			= (lua_State*(*)(lua_State *L))GetLuaFunc("lua_close");
static auto lua_typename		= (const char *(*)  (lua_State *L, int tp))GetLuaFunc("lua_typename");
static auto	lua_getstack		= (int(*)(lua_State *L, int level, lua_Debug *ar))GetLuaFunc("lua_getstack");
static auto luaL_newmetatable	= (int (*)(lua_State *L, const char *tname))GetLuaFunc("luaL_newmetatable");
static auto luaL_checkudata		= (void* (*) (lua_State *L, int index, const char *tname))GetLuaFunc("luaL_checkudata");
static auto lua_newuserdata		= (void* (*)(lua_State* L, size_t size))GetLuaFunc("lua_newuserdata");
static auto lua_setmetatable	= (int (*)(lua_State *L, int index))GetLuaFunc("lua_setmetatable");
static auto lua_rawseti			= (void (*)(lua_State *L, int index, int n))GetLuaFunc("lua_rawseti");
#define lua_pop(L,n)            lua_settop(L, -(n)-1)
#define lua_newtable(L)         lua_createtable(L, 0, 0)
#define lua_pushcfunction(L,f)  lua_pushcclosure(L, (f), 0)
#define lua_isfunction(L,n)     (lua_type(L, (n)) == LUA_TFUNCTION)
#define lua_istable(L,n)        (lua_type(L, (n)) == LUA_TTABLE)
#define lua_islightuserdata(L,n)        (lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L,n)          (lua_type(L, (n)) == LUA_TNIL)
#define lua_isboolean(L,n)      (lua_type(L, (n)) == LUA_TBOOLEAN)
#define lua_isthread(L,n)       (lua_type(L, (n)) == LUA_TTHREAD)
#define lua_isnone(L,n)         (lua_type(L, (n)) == LUA_TNONE)
#define lua_isnoneornil(L, n)   (lua_type(L, (n)) <= 0)
#define lua_pushliteral(L, s)   lua_pushlstring(L, s, (sizeof(s)/sizeof(char))-1)
#define lua_pushglobaltable(L)  lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS)
#define lua_tostring(L,i)       lua_tolstring(L, (i), NULL)
#define lua_setglobal(L,s)   lua_setfield(L, LUA_GLOBALSINDEX, s)
#define lua_getglobal(L,s)   lua_getfield(L, LUA_GLOBALSINDEX, s)
#define lua_register(L,n,f) (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))

*/
static lua_State* RunLuaOn(int state, const char* l, int rets = 0)
{
	int id = state;
	const char* code = l;
	CLuaInterface* clua = dismay->m_pLua->GetLuaInterface(id);
	if (!clua)
		return 0;

	lua_State* alt = clua->L;
	if (!alt)
		return 0;

	int error = luaL_loadstring(alt, code) || lua_pcall(alt, 0, rets, 0);
	if (error)
		return 0;

	return alt;
}

static bool PushVector(lua_State* L, Vector vec)
{
	lua_getglobal(L, "Vector");
	lua_pushnumber(L, (double)vec.x);
	lua_pushnumber(L, (double)vec.y);
	lua_pushnumber(L, (double)vec.z);
	lua_pcall(L, 3, 1, 0);
	return true;
}

static Vector GetVector(lua_State* L, int stack = -1)
{
	lua_getfield(L, stack, "x");
	float p = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, stack, "y");
	float y = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, stack, "z");
	float r = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return Vector(p, y, r);
}

static bool PushAngle(lua_State* L, QAngle ang)
{
	lua_getglobal(L, "Angle");
	lua_pushnumber(L, (double)ang.p);
	lua_pushnumber(L, (double)ang.y);
	lua_pushnumber(L, (double)ang.r);
	lua_pcall(L, 3, 1, 0);
	return true;
}

static QAngle GetAngle(lua_State* L, int stack = -1)
{
	lua_getfield(L, stack, "p");
	float p = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, stack, "y");
	float y = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_getfield(L, stack, "r");
	float r = (float)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return QAngle(p, y, r);
}

static bool PushEntity(lua_State* L, C_BaseEntity* ent)
{
	UserData* ud = (UserData*)lua_newuserdata(L, sizeof(UserData));
	ud->data = ent;
	ud->type = TYPE_ENTITY;
	lua_getfield(L, LUA_REGISTRYINDEX, "Entity");
	lua_setmetatable(L, -2);
	return true;
}

static C_BaseEntity* GetEntity(lua_State* L, int stack = -1)
{
	UserData* ud = (UserData*)lua_touserdata(L, stack);
	if(ud->type == TYPE_ENTITY)
		return (C_BaseEntity*)ud->data;
	return 0;
}

static bool PushCUserCmd(lua_State* L, CUserCmd* cmd)
{
	UserData* ud = (UserData*)lua_newuserdata(L, sizeof(UserData));
	ud->data = (void*)cmd;
	ud->type = TYPE_CUSERCMD;
	lua_getfield(L, LUA_REGISTRYINDEX, "CUserCmd");
	lua_setmetatable(L, -2);
	return true;
}

static CUserCmd* GetCUserCmd(lua_State* L, int stack = -1)
{
	UserData* ud = (UserData*)lua_touserdata(L, stack);
	if(ud->type == TYPE_CUSERCMD)
	{
		return (CUserCmd*)ud->data;
	}
	else return 0;
}


static int lua_runon(lua_State* L) {
	lua_State* x;
	if(x = RunLuaOn((int)lua_tonumber(L, 1), lua_tostring(L, 2), (int)lua_tonumber(L, 3)))
	{
		for(int i = 1; i <= lua_tonumber(L, 3); i++)
		{
			lua_newtable(L);
			lua_pushnumber(L, lua_type(x, i));
			lua_setfield(L, -2, "type");
			switch(lua_type(L, i))
			{
			case LUA_TNUMBER:
				lua_pushnumber(L, lua_tonumber(x, i));
				break;
			case LUA_TSTRING:
				lua_pushstring(L, lua_tostring(x, i));
				break;
			case LUA_TNIL:
				lua_pushnil(L);
				break;
			case LUA_TTABLE:
				lua_pushstring(L, "table");
				break;
			case LUA_TBOOLEAN:
				lua_pushboolean(L, lua_toboolean(x, i));
				break;
			default:
				lua_pushstring(L, lua_typename(x, i));
				break;
			}
			lua_setfield(L, -2, "value");
		}
		lua_pop(x, (int)lua_tonumber(L, 3));
		lua_pop(L, 3);
	}
	lua_pop(L, 3);
	return 0;
}
static void StackDump(lua_State* L, const char* id = "default") 
{
	int top = lua_gettop(L);
	printf("Stack [%s]:", id);
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	for (i = 1; i <= n; i++) 
	{
		printf("\n");
		lua_getglobal(L, "tostring");  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		const char *s = lua_tostring(L, -1);  /* get result */
		if (s == NULL) 
		{
			luaL_error(L, "tostring must return a string to print");
			return;
		}
		printf("\t%d: %s", i, s);
		lua_pop(L, 1);  /* pop result */
	}
	//lua_pop(L, 1);
	printf("\n");
}
static int nErrColor = FG_RED|BG_RED|BG_INTENSE;
static int Error(lua_State* L)
{
	dismay->SetConColor(nErrColor);
	const char* err = lua_tostring(L, lua_gettop(L));
	printf("[CAUGHT ERROR] %s", err);
	lua_Debug dbg;
	int i = 1;
	int c = 0;
	while((c = lua_getstack(L, i, &dbg)) == 1)
	{
		char tmp[256];
		sprintf(tmp, "%i", c);
		MessageBox(0, tmp, "Lua error!", 0); // here, if i remove this it crashes
		if(lua_getinfo(L, "nSl", &dbg) == 0)
			break;
		printf("\n");
		for (int g = 0; g <= i; g++) 
			printf(" ");
		printf("%d. %s - ", i, dbg.name ? dbg.name : "unknown");
		if (strcmp(dbg.short_src, "[C]"))
			printf("%s:%i", dbg.short_src, dbg.currentline);
		else
			printf("[C]");
		i++;
	}
	printf("\n");
	dismay->ResetConColor();
	return 0;
}

static int print(lua_State* L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i = 1; i <= n; i++) {
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		const char *s = lua_tostring(L, -1);  /* get result */
		if (s == NULL)
			return 0;
		if (i>1) printf("\t");
		printf("%s", s);
		lua_pop(L, 1);  /* pop result */
	}
	printf("\n");
	return 0;
}


extern DDismay* dismay;

class DLua
{
public:
	DLua();
	~DLua() {};

	void RunString(const char* string)
	{
		lua_pushcfunction(m_luaState, Error);
		int code = luaL_loadbuffer(m_luaState, string, strlen(string), "=startup");
		if(code)
		{
			const char* str = lua_tostring(m_luaState, -1);
			dismay->SetConColor(nErrColor);
			printf("[COMPILE ERROR] %s\n", str);
			dismay->ResetConColor();
			lua_pop(m_luaState, 1);
			return;
		}
		code = lua_pcall(m_luaState, 0, 0, -2);
		if(code != LUA_SUCCESS) 
		{
			lua_pop(m_luaState, 1);
		}
		lua_pop(m_luaState, 1);
	}
public:
	lua_State*		m_luaState;
};

#endif // DLUA_H