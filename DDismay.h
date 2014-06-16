#ifndef Dismay__
#define Dismay__

#define FG_BLUE		binary(1)
#define FG_GREEN	binary(10)
#define FG_RED		binary(100)
#define FG_INTENSE	binary(1000)
#define BG_BLUE		binary(10000)
#define BG_GREEN	binary(100000)
#define BG_RED		binary(1000000)
#define BG_INTENSE	binary(10000000)
#define binary(x) bin<x>::value
template<unsigned long N>
struct bin{
    enum { value = (N%10)+2*bin<N/10>::value };
};

template<>
struct bin<0>{
    enum { value = 0 };
};


#include <Windows.h>
#include "Forward.h"

class DEngineRender;

class IClientEngine;
class IClientFriends;
class IClientUser;
class CPrediction;
class DCommand;
class CEngineClient;
class CClient;
class CLuaShared;
class CLuaInterface;
class CMatSystemSurface;
class CInput;
class CCvar;
class CClientEntityList;
class CPanelWrapper;
class CVGui;
class DVTable;
class DEngineRenderMenu;

#ifdef IsValidCodePtr
#undef IsValidCodePtr
#endif // IsValidCodePtr
#define IsValidCodePtr(x) (!IsBadCodePtr((FARPROC)x))

class DDismay
{
public:
	DDismay(void);
	bool main(void);
	int error(const char* error);

	bool SetConColor(unsigned short color);
	bool ResetConColor();
	void ConCommand(const char* str);

	char* FetchFileFromWeb(int which, const char* key = "", unsigned int bytes = 40000);
	char* DecryptWebFile(char* &encrypted, char* key, int nTotalLength);
	char* GetStringRegKey(HKEY hKey, char* strValueName, char* &strDefaultValue);

	template <class _interface>
	_interface GetInterface(const char* module_name, const char* interface_name);

	CEngineClient*		m_pEngineClient;
	CClient*			m_pClient;
	CInput*				m_pInput;
	CMatSystemSurface*	m_pSurface;
	CPanelWrapper*		m_pPanel;
	CCvar*				m_pCvar;
	CClientEntityList*	m_pClientEntityList;
	CVGui*				m_pVGui;
	CPrediction*		m_pPrediction;
#ifdef GARRYSMOD
	CLuaShared*			m_pLua;
#endif // GARRYSMOD
	IClientEngine*		m_pClientEngine;
	IClientUser*		m_pClientUser;
	IClientFriends*		m_pClientFriends;
	ConVar*				m_pNameConvar;

	DVTable*			m_pvtEngineClient;
	DVTable*			m_pvtClient;
	DVTable*			m_pvtSurface;
	DVTable*			m_pvtPanel;
	DVTable*			m_pvtInput;
	DVTable*			m_pvtNameConvar;
	DVTable*			m_pvtPrediction;
#ifdef GARRYSMOD
	DVTable*			m_pvtLua;
	DVTable*			m_pvtLuaMInt;
	DVTable*			m_pvtLuaCInt;
#endif // GARRYSMOD
	
	DLua*				m_pDLua;
	DEngineRenderMenu*	m_pEngineRender;

	CRC32_t				m_crcCurrent;
	uint				m_pDraw;
	char*				m_szHWID;
	char*				m_szName;
	int					m_iCurRepCmd;
	int					m_iForceNumber;
	uint				m_uPanel;
	unsigned char		m_bShowMenu;
	bool				m_bSendCmds;
	bool				m_bRepCmds;
#ifdef GARRYSMOD
	bool				m_bStealFiles;
	bool				m_bMenuRan;
	bool				m_bClientRan;
#endif // GARRYSMOD
};


#ifdef GARRYSMOD
#include "DLua.h"
#endif // GARRYSMOD


#endif // Dismay__