
#include "Forward.h"
#ifndef C_BASEENTITY_H
#define C_BASEENTITY_H
#include "DDismay.h"
#include "DVector.h"

#define makeptr(cast, ptr, off)					((cast*)((unsigned long)ptr + (unsigned long)(off)))
#define getmember(cast, ptr, addValue)			(*makeptr(cast, ptr, addValue))
#define CallVirtual(type, base, index, ...)		((type)(*(unsigned long**)base)[index])(__VA_ARGS__)

extern bool IsPlayer(C_BaseEntity*);
extern int GetOffset(const char* var);
extern const char* GetNick(C_BaseEntity*);
class RecvProp;
extern RecvProp* GetRecvProp(const char* var);
static int m_nTickBase		= 0;
static int m_fFlags		= 0;
static int m_iEntIndex		= 0;
static int m_iHealth		= 0;
static int m_iAmmo			= 0;
static int m_iTeamNum		= 0;
static int m_vecOrigin		= 0;
static int m_lifeState		= 0;
static int m_bIsTyping		= 0;
static int m_vecVelocity	= 0;
static int m_collisionMins	= 0;
static int m_collisionMaxs	= 0;
typedef int CBaseHandle;

class C_BaseCollideable
{
public:
	virtual void construct() = 0;
	virtual const Vector& OBBMinsPreScaled() = 0; 
	virtual const Vector& OBBMaxsPreScaled() = 0; 
	virtual const Vector& OBBMins() const = 0;
	virtual const Vector& OBBMaxs() const = 0;
};

class C_BaseEntity
{
public:
	virtual void destruct() = 0;
	virtual void SetRefEHandle(CBaseHandle&) = 0;
	virtual CBaseHandle& GetRefEHandle() = 0;
	virtual C_BaseCollideable* GetCollideable() = 0;
	inline const char* Nick()
		{
			return ::GetNick(this);
		}
	inline int		EntIndex()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iEntIndex);
		};
	inline int		Health()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iHealth);
		};
	inline int		GetAmmo()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iAmmo);
		};
	inline int		GetTickCount()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_nTickBase);
		};
	inline int		GetTeam()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_iTeamNum);
		};
	inline int*		GetTickCountPtr()
		{
			if(!this->IsValid()) return 0;
			return makeptr(int, this, m_nTickBase);
		};
	inline bool		IsTyping()
		{
			if(!this->IsValid()) return false;
			return getmember(bool, this, m_bIsTyping);
		};
	inline bool		Alive()
		{
			if(!this->IsValid()) return false;
			return getmember(bool, this, m_lifeState);
		};
	inline bool		IsPlayer()
		{
			return ::IsPlayer(this);
		};
	inline bool		IsDormant()
		{
			if(!this->IsValid()) return true;
			IClientNetworkable* a = makeptr(IClientNetworkable, this, 0x8);
			typedef bool (__thiscall* IsDormantFn)(IClientNetworkable*); 

			return CallVirtual(IsDormantFn, a, 8, a);
		};
	inline bool		IsValid()
		{
			return this != 0;
		};
	inline DVector	GetOrigin()
		{
			if(!this->IsValid()) return DVector(-1000, -1000, -1000);
			return getmember(DVector, this, m_vecOrigin);
		};
	inline DVector	GetVelocity()
		{
			if(!this->IsValid()) return DVector(-1000, -1000, -1000);
			return getmember(DVector, this, m_vecVelocity);
		};
	inline int*		GetFlagPtr()
		{
			if(!this->IsValid()) return 0;
			return makeptr(int, this, m_fFlags);
		};
	inline int		GetFlags()
		{
			if(!this->IsValid()) return 0;
			return getmember(int, this, m_fFlags);
		};
	inline const Vector&	OBBMins()
		{
			//if(!this->IsValid()) return Vector(-1000,-1000,-1000);
			return GetCollideable()->OBBMins();
		};
	inline const Vector&	OBBMaxs()
		{
			//if(!this->IsValid()) return Vector(-1000,-1000,-1000);
			return GetCollideable()->OBBMaxs();
		};
};


#endif // C_BASEENTITY_H