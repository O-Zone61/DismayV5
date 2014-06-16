#pragma once
#ifndef D_CLUAINT
#define D_CLUAINT

#include "DDismay.h"
#include "DColor.h"
#include <string>
unk(ILuaObject);
struct lua_State;

typedef int (*CLuaFunction)(lua_State*);

struct UserData
{
    void*			data;
    unsigned char	type;
};


#include "Garry\dismay_cbaseluainterface.h"

class CLuaInterface : private CBaseLuaInterface {
public:
	virtual void* CBaseLuaInterface::Top(void) = 0;
	virtual void* CBaseLuaInterface::Push(int) = 0;
	virtual void* CBaseLuaInterface::Pop(int) = 0;
	virtual ILuaObject* CBaseLuaInterface::GetTable(int) = 0;
	virtual void* CBaseLuaInterface::GetField(int,char  const*) = 0;
	virtual void* CBaseLuaInterface::SetField(int,char  const*) = 0;
	virtual ILuaObject* CBaseLuaInterface::CreateTable(void) = 0;
	virtual void* CBaseLuaInterface::SetTable(int) = 0;
	virtual void* CBaseLuaInterface::SetMetaTable(int) = 0;
	virtual void* CBaseLuaInterface::GetMetaTable(int) = 0;
	virtual void* CBaseLuaInterface::Call(int,int) = 0;
	virtual void* CBaseLuaInterface::PCall(int,int,int) = 0;
	virtual void* CBaseLuaInterface::Equal(int,int) = 0;
	virtual void* CBaseLuaInterface::RawEqual(int,int) = 0;
	virtual void* CBaseLuaInterface::Insert(int) = 0;
	virtual void* CBaseLuaInterface::Remove(int) = 0;
	virtual void* CBaseLuaInterface::Next(int) = 0;
	virtual void* CBaseLuaInterface::NewUserdata(unsigned int) = 0;
	virtual void* CBaseLuaInterface::ThrowError(char  const*) = 0;
	virtual void* CLuaInterface::CheckType(int,int) = 0;
	virtual void* CBaseLuaInterface::ArgError(int,char  const*) = 0;
	virtual void* CBaseLuaInterface::RawGet(int) = 0;
	virtual void* CBaseLuaInterface::RawSet(int) = 0;
	virtual const char* CBaseLuaInterface::GetString(int,unsigned int *) = 0;
	virtual double CBaseLuaInterface::GetNumber(int) = 0;
	virtual bool CBaseLuaInterface::GetBool(int) = 0;
	virtual void* CBaseLuaInterface::GetCFunction(int) = 0;
	virtual UserData* CBaseLuaInterface::GetUserdata(int) = 0;
	virtual void* CLuaInterface::PushNil(void) = 0;
	virtual void* CBaseLuaInterface::PushString(char  const*,unsigned int) = 0;
	virtual void* CBaseLuaInterface::PushNumber(double) = 0;
	virtual void* CBaseLuaInterface::PushBool(bool) = 0;
	virtual void* CBaseLuaInterface::PushCFunction(CLuaFunction) = 0;
	virtual void* CBaseLuaInterface::PushCClosure(CLuaFunction,int) = 0;
	virtual void* CBaseLuaInterface::PushUserdata(void *) = 0;
	virtual void* CBaseLuaInterface::ReferenceCreate(void) = 0;
	virtual void* CBaseLuaInterface::ReferenceFree(int) = 0;
	virtual void* CBaseLuaInterface::ReferencePush(int) = 0;
	virtual void* CBaseLuaInterface::PushSpecial(int) = 0;
	virtual void* CBaseLuaInterface::IsType(int,int) = 0;
	virtual void* CBaseLuaInterface::GetType(int) = 0;
	virtual void* CBaseLuaInterface::GetTypeName(int) = 0;
	virtual void* CBaseLuaInterface::CreateMetaTableType(char  const*,int) = 0;
	virtual void* CBaseLuaInterface::CheckString(int) = 0;
	virtual void* CBaseLuaInterface::CheckNumber(int) = 0;
	virtual void* CBaseLuaInterface::ObjLen(int) = 0;
	virtual void* CLuaInterface::AddThreadedCall(/* GarrysMod::Lua::IThreadedCall * */ void*) = 0;
	virtual void* CLuaInterface::Init(/* ILuaCallback * */ void* ,bool) = 0;
	virtual void* CLuaInterface::Shutdown(void) = 0;
	virtual void* CLuaInterface::Cycle(void) = 0;
	virtual lua_State* CLuaInterface::GetLuaState(void) = 0;
	virtual ILuaObject* CLuaInterface::Global(void) = 0;
	virtual void* CLuaInterface::GetObject(int) = 0;
	virtual void* CLuaInterface::DELETE_ME_5437(int) = 0;
	virtual void* CLuaInterface::_DELETE_ME2466(int) = 0;
	virtual void* CLuaInterface::PushLuaObject(ILuaObject *) = 0;
	virtual void* CLuaInterface::PushLuaFunction(int (*)(lua_State *)) = 0;
	virtual void* CLuaInterface::LuaError(char  const*,int) = 0;
	virtual void* CLuaInterface::TypeError(char  const*,int) = 0;
	virtual void* CLuaInterface::CallInternal(int,int) = 0;
	virtual void* CLuaInterface::CallInternalNoReturns(int) = 0;
	virtual void* CLuaInterface::CallInternalGetBool(int) = 0;
	virtual void* CLuaInterface::CallInternalGetString(int) = 0;
	virtual void* CLuaInterface::CallInternalGet(int,ILuaObject *) = 0;
	virtual void* CLuaInterface::_DELETE_ME(ILuaObject *,void *) = 0;
	virtual void* CLuaInterface::NewGlobalTable(char  const*) = 0;
	virtual void* CLuaInterface::NewTemporaryObject(void) = 0;
	virtual void* CLuaInterface::isUserData(int) = 0;
	virtual void* CLuaInterface::GetMetaTableObject(char  const*,int) = 0;
	virtual void* CLuaInterface::GetMetaTableObject(int) = 0;
	virtual void* CLuaInterface::GetReturn(int) = 0;
	virtual int CLuaInterface::IsServer(void) = 0;
	virtual int CLuaInterface::IsClient(void) = 0;
	virtual void* CLuaInterface::IsDedicatedServer(void) = 0;
	virtual void* CLuaInterface::DestroyObject(ILuaObject *) = 0;
	virtual void* CLuaInterface::CreateObject(void) = 0;
	virtual void* CLuaInterface::SetMember(ILuaObject *,ILuaObject *,ILuaObject *) = 0;
	virtual void* CLuaInterface::GetNewTable(void) = 0;
	virtual void* CLuaInterface::SetMember(ILuaObject *,float) = 0;
	virtual void* CLuaInterface::SetMember(ILuaObject *,float,ILuaObject *) = 0;
	virtual void* CLuaInterface::SetMember(ILuaObject *,char  const*) = 0;
	virtual void* CLuaInterface::SetMember(ILuaObject *,char  const*,ILuaObject *) = 0;
	virtual void* CLuaInterface::SetIsServer(bool) = 0;
	virtual void* CLuaInterface::PushLong(long) = 0;
	virtual void* CLuaInterface::GetFlags(int) = 0;
	virtual void* CLuaInterface::FindOnObjectsMetaTable(int,int) = 0;
	virtual void* CLuaInterface::FindObjectOnTable(int,int) = 0;
	virtual void* CLuaInterface::SetMemberFast(ILuaObject *,int,int) = 0;
	virtual bool CLuaInterface::RunString(char  const*,char  const*,char  const*,bool,bool) = 0;
	virtual char CLuaInterface::IsEqual(ILuaObject *,ILuaObject *) = 0;
	virtual void* CLuaInterface::Error(char  const*) = 0;
	virtual void* CLuaInterface::GetStringOrError(int) = 0;
	virtual void* CLuaInterface::RunLuaModule(char  const*) = 0;
	virtual void* CLuaInterface::FindAndRunScript(char  const*,bool,bool,char  const*) = 0;
	virtual void* CLuaInterface::SetPathID(char  const*) = 0;
	virtual void* CLuaInterface::GetPathID(void) = 0;
	virtual void* CLuaInterface::ErrorNoHalt(char  const*,...) = 0;
	virtual void* CLuaInterface::Msg(char  const*,...) = 0;
	virtual void* CLuaInterface::PushPath(char  const*) = 0;
	virtual void* CLuaInterface::PopPath(void) = 0;
	virtual void* CLuaInterface::GetPath(void) = 0;
	virtual Color CLuaInterface::GetColor(int) = 0;
	virtual void* CLuaInterface::PushColor(int,int,int,int) = 0;
	virtual void* CLuaInterface::GetStack(int,void *) = 0;
	virtual void* CLuaInterface::GetInfo(char  const*,void *) = 0;
	virtual void* CLuaInterface::GetLocal(void *,int) = 0;
	virtual void* CLuaInterface::GetUpvalue(int,int) = 0;
	virtual void* CLuaInterface::RunStringEx(char  const*,char  const*,char  const*,bool,bool,bool) = 0;
	virtual void* CLuaInterface::DELETE_ME1(char  const*,int) = 0;
	virtual void* CLuaInterface::GetDataString(int,void **) = 0;
	virtual void* CLuaInterface::ErrorFromLua(char  const*,...) = 0;
	virtual void* CLuaInterface::GetCurrentLocation(void) = 0;
	virtual void* CLuaInterface::MsgColour(Color  const&,char  const*,...) = 0;
	virtual void* CLuaInterface::SetState(lua_State *) = 0;
	virtual void* CLuaInterface::DELETE_ME2(void) = 0;
	virtual void* CLuaInterface::GetCurrentFile(std::string &) = 0;
	virtual void* CLuaInterface::CompileString(/* Bootil::Buffer & */ void*,std::string  const&) = 0;
	virtual void* CBaseLuaInterface::ThreadLock(void) = 0;
	virtual void* CBaseLuaInterface::ThreadUnlock(void) = 0;
	virtual void* CLuaInterface::CallFunctionProtected(int,int,bool) = 0;
	virtual void* CLuaInterface::Require(char  const*) = 0;
	virtual void* CLuaInterface::GetActualTypeName(int) = 0;
	virtual void* CLuaInterface::SetupInfiniteLoopProtection(void) = 0;

public:
	lua_State* L;
};
#endif //D_CLUAINT