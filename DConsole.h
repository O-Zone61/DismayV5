#ifndef DCONSOLE_H
#define DCONSOLE_H

class DConsole
{
public:
	DConsole();
	~DConsole();

	bool SetText(char* text);
	bool TypeKey(char key);
	bool Enter();
	bool Left();
	bool Right();
	bool AddLine(char* text);

	bool SetCharArraySize(int size);

public:
	char*	m_szText;
	int		m_iTextSize;
	char	m_szTemp[255];
	int		m_iCharIndex;
};

#endif // DCONSOLE_H