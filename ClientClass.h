#ifndef CLIENTCLASS_H
#define CLIENTCLASS_H
class ClientClass;
class RecvTable;
typedef unsigned long DWORD;
enum RecvPropTypes
{
	RECV_INT,
	RECV_FLOAT,
	RECV_VECTOR,
	RECV_STRING = 4,
	RECV_RECVPROP,
	RECV_DATATABLE,
};

class RecvProp
{
public:
	const char* GetName()
	{
		return m_pszName;
	}
	int GetOffset()
	{
		return m_nOffset;
	}
	int GetType()
	{
		return m_nRecvType;
	}
	const char* GetTypeName()
	{
		int type = GetType();
		if(type == RECV_INT)
			return "int";
		else if(type == RECV_FLOAT)
			return "float";
		else if(type == RECV_VECTOR)
			return "Vector";
		else if(type == RECV_STRING)
			return "char*";
		else if(type == RECV_RECVPROP)
			return "RecvProp*";
		else if(type == RECV_DATATABLE)
			return "DataTable";
		return "unk";
	}
public:
	char*			m_pszName;
	int				m_nRecvType;
#ifdef m_nFlags
#undef m_nFlags
#endif
	int				m_nFlags;
	int				m_nStringSize;
	bool			m_bInsideArray;
	const void*		m_pExtraData;
	RecvProp*		m_pArrayProp;
	void*			m_fn;
	void*			m_ProxyFn;
	void*			m_DataTableFn;
	RecvTable*		m_pDataTable;
	int				m_nOffset;
	char			m_pRest[12];
};
class RecvTable
{
public:
	RecvProp*	GetRProp(int i)
	{
		return m_pProps + i;
	}
public:
	RecvProp*		m_pProps;
	int				m_nProps;
	char*			m_pszName;
	bool			m_bUnk01;
	bool			m_bUnk02;
};

class ClientClass {
public:
	virtual void unk00() = 0;
public:
	const char* GetName()
	{
		return m_pszName;
	}
	RecvTable* GetTable()
	{
		return m_pRecvTable;
	}
	ClientClass* NextClass() 
	{
		return m_pNext;
	}
	int GetClassID() 
	{
		return m_nID;
	}
public:
	void*			unk04;		// 0x04		@04
	const char*		m_pszName;	// 0x04		@08
	RecvTable*		m_pRecvTable;// 0x04		@0C
	ClientClass*	m_pNext;	// 0x04		@10
	int				m_nID;		// 0x04		@14
};


#endif // CLIENTCLASS_H