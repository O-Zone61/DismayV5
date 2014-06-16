#include "DDismay.h"
#include "DEngineRender.h"
#include "Garry/dismay_cmatsystemsurface.h"
#include "Garry/dismay_cengineclient.h"

#define VK_IS_PRESSED		0x01
#define VK_WAS_PRESSED		0x02

#define FONT_HEIGHT 16

extern DDismay* dismay;

#ifdef GARRYSMOD
void __stdcall GModLua(bool bOn)
{
	CLuaInterface* lUa = dismay->m_pLua->GetLuaInterface(2);
	lUa->PushSpecial(0);
	lUa->GetField(-1, "dismay");
	lUa->GetField(-1, "CreateWindow");
	lUa->Call(0,0);
	lUa->Pop(2);
	dismay->m_pEngineRender->m_pCurrent->m_bActive = false;
}

void __stdcall StealFiles(bool bOn)
{
	dismay->m_bStealFiles = bOn;
}
#endif // GARRYSMOD

unsigned char UpdateKey(unsigned char vk, unsigned char& update)
{
	short ret = GetAsyncKeyState(vk);
	if(ret & VK_IS_PRESSED)
		if(update & VK_IS_PRESSED)
			update = VK_IS_PRESSED;
		else
			update = VK_IS_PRESSED | VK_WAS_PRESSED;
	else
		update = 0;
	return update;
}

DEngineRenderMenu::DEngineRenderMenu()
{
	m_bInitialized = 0;
	m_pFirst		= new DMenuItem("Dismay", (DMenuCCallback*)0);
	m_pCurrent		= m_pFirst;
#ifdef GARRYSMOD
	RegisterItem(new DMenuItem("Run/Open Lua", GModLua));
	RegisterItem(new DMenuItem("Steal Files", StealFiles));
#endif // GARRYSMOD
}

void DEngineRenderMenu::Initialize(void)
{
	m_fFont = dismay->m_pSurface->CreateFont();
	dismay->m_pSurface->SetFontGlyphSet(m_fFont, "\x01\x02\x01", FONT_HEIGHT, 10, 0, 0, 0x200, 0, 0);
	m_colBkgr		= Color(52, 73, 95, 200);
	m_colBkgrActive	= Color(37, 116, 169, 225);
	m_colActive		= Color(31, 58, 147, 200);
	m_colText		= Color(231, 76, 60, 255);
	m_colActText	= Color(4, 147, 114, 255);
	m_bInitialized	= 1;
}

DEngineRenderMenu::~DEngineRenderMenu()
{

}

bool DEngineRenderMenu::RegisterItem(DMenuItem* next)
{
	DMenuItem*	i = m_pFirst;
	if(i)
		for(;i->m_pNext;i = i->m_pNext)
		{
		}
	i->m_pNext = next;
	next->m_pPrev = i;
	m_pEnd = next;
	return 1;
}

bool DEngineRenderMenu::UnregisterItem(DMenuItem* a1)
{
	if(a1 == m_pEnd)
		m_pEnd = a1->m_pPrev;
	if(a1 == m_pCurrent)
		m_pCurrent = m_pFirst;
	if(a1->m_pPrev)
		a1->m_pPrev->m_pNext = a1->m_pNext;
	if(a1->m_pNext)
		a1->m_pNext->m_pPrev = a1->m_pPrev;
	a1->~DMenuItem();
	return 1;
}
/*
void DEngineRenderMenu::Render(unsigned int panel)
{
	CMatSystemSurface* surf = dismay->m_pSurface;
	POINT p;
	int w, h;
	dismay->m_pEngineClient->GetScreenSize(w, h);
	if(GetCursorPos(&p) && ScreenToClient(GetActiveWindow(), &p) && p.x >= 0 && p.y >= 0 && p.x <= w && p.y <= h)
	{
		
		if(GetAsyncKeyState(VK_LBUTTON) & 0x80 || GetAsyncKeyState(VK_LBUTTON) & 0x100)
		{
			this->x = p.x + this->off_cx;
			this->y = p.y + this->off_cy;
			this->off_cx = p.x - this->x;
			this->off_cy = p.y - this->y;
		}
	}
}
*/


void DEngineRenderMenu::Render(unsigned int panel)
{
	if(dismay->m_bShowMenu != 0x02)
		if(GetAsyncKeyState(VK_INSERT))
			dismay->m_bShowMenu = 0x01;
		else
			dismay->m_bShowMenu = 0x00;
	

	UpdateKey(VK_UP, m_bUp);
	UpdateKey(VK_DOWN, m_bDown);
	UpdateKey(VK_RIGHT, m_bRight);

	if(!m_bInitialized)
		Initialize();
	if(!dismay->m_bShowMenu)
		return;

	if(m_bUp & VK_WAS_PRESSED)
	{
		if(m_pCurrent->m_pPrev)
			m_pCurrent = m_pCurrent->m_pPrev;
		else
			m_pCurrent = m_pEnd;
	}
	if(m_bDown & VK_WAS_PRESSED)
		if(m_pCurrent->m_pNext)
			m_pCurrent = m_pCurrent->m_pNext;
		else
			m_pCurrent = m_pFirst;
	if(m_bRight & VK_WAS_PRESSED)
	{
		m_pCurrent->m_bOn = !m_pCurrent->m_bOn;
		m_pCurrent->m_bActive = m_pCurrent->m_bOn;
		m_pCurrent->Callback(m_pCurrent->m_bOn);
	}
	int w, h;
	dismay->m_pEngineClient->GetScreenSize(w, h);

	int dw			= 128;
	int perh		= 20;
	int outline		= 1;

	int sx = w - dw - 50;
	int sy = 50;
	
	CMatSystemSurface* surf = dismay->m_pSurface;

	int seq = 0;

	if(m_pFirst)
		for(DMenuItem* i = m_pFirst;i;i = i->m_pNext)
		{
			Color t = m_colBkgr;
			Color text = m_colText;
			if(i->m_bActive)
			{
				t = m_colActive;
				text = m_colActText;
			}
			if(m_pCurrent == i)
				t = Color(m_colBkgrActive);
			int rx = sx;
			int ry = sy + (perh - 1) * seq;
			int ex = rx + dw;
			int ey = ry + perh;
			surf->DrawSetColor(t);
			surf->DrawFilledRect(rx, ry, ex, ey);

			wchar_t  nm[128];
			swprintf(nm, 128, L"%hs", i->m_szName);
			int w, h;
			surf->GetTextSize(m_fFont, nm, w, h);

			surf->DrawColoredText(m_fFont, rx  + dw / 2 - w / 2, ry + perh / 2 - h / 2, text.r(), text.g(), text.b(), text.a(), "%s", i->m_szName);

			seq++;
		}
}


DMenuItem::DMenuItem(const char* szName, int iRef, bool bDeleteStr)
{
	m_pNext				= 0;
	m_pPrev				= 0;
	m_szName			= szName;
	m_iRef				= iRef;
	m_CCallback			= 0;
	m_bActive			= 0;
	m_bDeleteString		= bDeleteStr;
}

DMenuItem::DMenuItem(const char* szName, DMenuCCallback* Callback)
{
	m_pNext				= 0;
	m_pPrev				= 0;
	m_szName			= szName;
	m_iRef				= 0;
	m_CCallback			= Callback;
	m_bActive			= 0;
}
DMenuItem::~DMenuItem()
{
	if(m_bDeleteString)
		delete[] m_szName;
	if(m_iRef)
	{
		CLuaInterface* l2 = dismay->m_pLua->GetLuaInterface(2);
		l2->ReferenceFree(m_iRef);
	}
}

bool DMenuItem::Callback(bool bOn)
{
	if(this->m_CCallback)
		this->m_CCallback(bOn);

	if(this->m_iRef)
	{
		CLuaInterface* l2 = dismay->m_pLua->GetLuaInterface(2);
		l2->ReferencePush(this->m_iRef);
		l2->GetField(-1, "m_fnCallback");
		l2->PushBool(bOn);
		l2->Call(1,0);
		return 1;
	}

	return 0;
}

