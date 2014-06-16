#ifndef FORWARD_H
#define FORWARD_H

class	IClientRenderable;
class	IClientNetworkable;
class	IClientUnknown;

#ifndef C_BASEENTITY_H
class C_BaseEntity;
typedef C_BaseEntity IClientEntity;
#endif
#ifndef ANGLE_H
class QAngle;
#endif
#ifndef VECTOR_H
class DVector;
typedef DVector Vector;
#endif
#ifndef DLUA_H
class DLua;
#endif
#ifndef CLUAINTERFACE_H
class CLuaInterface;
#endif
#ifndef CBASELUAINTERFACE_H
class CBaseLuaInterface;
#endif
class	ImageFormat;
class	InputEvent_t;
class	ConCommandBase;
class	ConVar;
class	ConCommand;
class	IConsoleDisplayFunc;
class	ICvarQuery;
class	IConVar;
class	model_t;
class	SurfInfo;
class	CAudioSource;
class	ButtonCode_t;
class	con_nprint_s;
class	IMaterialSystem;
class	AudioState_t;
class	CPhysCollide;
class	IMaterial;
class	matrix3x4_t;
class	color32_s;
class	INetChannel;
class	OcclusionParams_t;
class	IAchievementMgr;
class	CGamestatsData;
class	IDemoRecorder;
class	INetMessage;
class	INetChannelHandler;
class	INetChannelInfo;
class	bf_write;
class	bf_read;
class	IClientPanel;
class	SurfacePlat;
class	KeyValues;
class	VPanel;
class	Color;
class	QAngle;
class	CSteamAPIContext;
class	IGet;
class	LuaClientDatatableHook;
class	ILuaObject;
class	CGlobalVarsBase;
class	bf_write;
class	bf_read;
class	vrect_t;
class	CViewSetup;
class	ScreenFade_t;
class	CEngineSprite;
class	ClientFrameStage_t;
class	CSaveRestoreData;
class	datamap_t;
class	typedescription_t;
struct	lua_State;
struct	UserData;
typedef struct netpacket_s netpacket_t;
typedef struct netadr_s	netadr_t;
typedef unsigned short	ushort;
typedef unsigned long	ulong;
typedef unsigned int	uint;
typedef unsigned char	uchar;
typedef unsigned long	HPanel;
typedef unsigned int	VPANEL;

#endif // FORWARD_H