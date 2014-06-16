#ifndef DCOMMAND
#define DCOMMAND

#include "DDismay.h"

class DCommand;

typedef void DCommandCallback_t(const char*);
extern DDismay* dismay;
class DCommand
{
public:
	DCommand()
	{
		
	}
	DCommand(const char* name, int fnCallback)
	{
		m_pszName		= name;
		m_bIsLua		= true;
		m_fnLuaCallback = fnCallback;
		m_pNext			= 0;
	}
	DCommand(const char* name, DCommandCallback_t* fnCallback)
	{
		m_pszName		= name;
		m_fnCallback	= fnCallback;
		m_bIsLua		= false;
		m_pNext			= 0;
	}

	bool Callback(char* x)
	{
		if(m_bIsLua) 
		{
			if(!m_fnLuaCallback)
				return 0;
			dismay->m_pLua->GetLuaInterface(2)->ReferencePush(m_fnLuaCallback);
			dismay->m_pLua->GetLuaInterface(2)->PushString(x, 0);
			dismay->m_pLua->GetLuaInterface(2)->Call(1,0);
			return 1;
		}
		else
		{
			if(!m_fnCallback)
				return 0;
			m_fnCallback(x);
			return 1;
		}
	}

	int						m_fnLuaCallback;
	const char*				m_pszName;
	DCommandCallback_t*		m_fnCallback;
	DCommand*				m_pNext;
	bool					m_bIsLua;
};

#endif // DCOMMAND