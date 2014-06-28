#include "DConsole.h"
#include <Windows.h>
#include "DDismay.h"

extern DDismay* dismay;

#define MAX_SIZE (255*10)

DConsole::DConsole()
{
	m_szText = new char[MAX_SIZE];
	SetCharArraySize(MAX_SIZE); // 10 lines of 255 chars
	SetText("Dismay Initialized.");
}

DConsole::~DConsole()
{
	realloc(m_szText, m_iTextSize);
	realloc(m_szTemp, 255);
}

bool DConsole::SetText(char* text)
{
	for(int i = 0;i < strlen(text);i++)
	{
		m_szText[i] = text[i];
		m_szText[i+1] = 0;
	}
	return true;
}

bool DConsole::SetCharArraySize(int size)
{
	MessageBox(0, "IMPLEMENT ME", "ERROR", 0);
}

bool DConsole::TypeKey(char x)
{
	if(strlen(m_szTemp) >= 255)
	{
		return false;
	}
	m_szTemp[strlen(m_szTemp)] = x;
	m_szTemp[strlen(m_szTemp)] = 0;
	return true;
}

bool DConsole::AddLine(char* text)
{
	size_t x = strlen(m_szText) + strlen(text) + 1;
	char tmp[MAX_SIZE];
	if(x > MAX_SIZE)
	{
		for(int i = x - MAX_SIZE; i < x - (x - MAX_SIZE); i++)
		{
			if(m_szText[i] == '\n')
			{
				for(int b = i + 1; i < i - (i - MAX_SIZE); i++)
				{
					tmp[b] = m_szText[b];
					tmp[b + 1] = 0;
				}
				strcpy(m_szText, tmp);
			}
		}
	}
	strcat(m_szText, text);
	strcat(m_szText, "\n");
	return true;
}

bool DConsole::Enter()
{
	AddLine(m_szTemp);
	dismay->m_pDLua->RunString(m_szTemp);
	m_szTemp[0] = 0;
	return true;
	
}