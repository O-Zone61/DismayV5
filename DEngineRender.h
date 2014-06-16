#ifndef ENGREND__
#define ENGREND__
#include "DDismay.h"
#include "Forward.h"
#include "DColor.h"

typedef void (__stdcall DMenuCCallback)(bool bOn);

class DMenuItem
{
public:
	~DMenuItem();
	DMenuItem(const char* szName, int iRef, bool bDeleteStr = false);
	DMenuItem(const char* szName, DMenuCCallback* Callback);
	bool Callback(bool bOn);

public:
	DMenuCCallback*		m_CCallback;
	int					m_iRef;
	const char*			m_szName;
	DMenuItem*			m_pPrev;
	DMenuItem*			m_pNext;

	bool				m_bOn;
	bool				m_bActive;
	bool				m_bDeleteString;
};

class DEngineRenderMenu
{
public:
	DEngineRenderMenu();
	~DEngineRenderMenu();

public:
	bool UnregisterItem(DMenuItem*);
	bool RegisterItem(DMenuItem*);
	void Render(unsigned int panel);
	void Initialize(void);

public:
	
	int				x;
	int				y;
	unsigned int	click_width;
	unsigned int	click_height;
	unsigned int	nonclick_width;
	unsigned int	nonclick_height;
	int				off_cx;
	int				off_cy;

	DMenuItem*		m_pFirst;
	DMenuItem*		m_pCurrent;
	DMenuItem*		m_pEnd;
	Color			m_colBkgr;
	Color			m_colText;
	Color			m_colActText;
	Color			m_colEnabled;
	Color			m_colDisabled;
	Color			m_colBkgrActive;
	Color			m_colActive;
	unsigned long	m_fFont;
	bool			m_bInitialized;
	bool			m_bVisible;
	unsigned char	m_bDown;
	unsigned char	m_bUp;
	unsigned char	m_bRight;
};

#endif // ENGREND__