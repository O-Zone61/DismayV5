#ifndef CLUASHARED_H
#define CLUASHARED_H

#include <string>
#include <vector>
#include "../Forward.h"
#include "DGame.h"
#include "dismay_cluainterface.h"


class CLuaShared
{
public:
	virtual CLuaShared::~CLuaShared() = 0;
	virtual void* CLuaShared::Init(void* (*)(const char*,int*), bool, CSteamAPIContext*, IGet*) = 0;
	virtual void* CLuaShared::Shutdown(void) = 0;
	virtual void* CLuaShared::DumpStats(void) = 0;
	virtual void* CLuaShared::CreateLuaInterface(unsigned char ToCreate,bool) = 0; // 0 = client, 1 = server, 2 = menu
	virtual void* CLuaShared::CloseLuaInterface(CLuaInterface* pToClose) = 0;
	virtual CLuaInterface* CLuaShared::GetLuaInterface(unsigned char ToGet) = 0;
	virtual void* CLuaShared::LoadFile(const std::string&, const std::string&, bool, bool) = 0;
	virtual void* CLuaShared::GetCache(const std::string&) = 0;
	virtual void* CLuaShared::MountLua(const char*) = 0;
	virtual void* CLuaShared::MountLuaAdd(const char*, const char*) = 0;
	virtual void* CLuaShared::UnMountLua(const char*) = 0;
	virtual void* CLuaShared::SetFileContents(const char*, const char*) = 0;
	virtual void* CLuaShared::SetLuaFindHook(LuaClientDatatableHook*) = 0;
	virtual void* CLuaShared::FindScripts(const std::string&, const std::string&, std::vector<std::string,std::allocator<std::string>>&) = 0;
};

#endif // CLUASHARED_H