#ifndef D_CINP
#define D_CINP
#pragma once

typedef unsigned long CRC32_t;

void CRC32_Init( CRC32_t *pulCRC );
void CRC32_ProcessBuffer( CRC32_t *pulCRC, const void *p, int len );
void CRC32_Final( CRC32_t *pulCRC );
CRC32_t	CRC32_GetTableEntry( unsigned int slot );

#include "DAngle.h"
#include "../checksum_md5.h"

class CUserCmd // sizeof(CUserCmd) == 0x15C
{
public:
	int		header;				// 4	(+x00)
	int     command_number;		// 4	(+x04)
	int     tick_count;			// 4	(+x08)
	QAngle  viewangles;			// 12	(+x0C)
	float   forwardmove;		// 4	(+x18)
	float   sidemove;			// 4	(+x1C) 
	float   upmove;				// 4	(+x20)   
	int     buttons;			// 4	(+x24)
	byte    impulse;			// 1	(+x28)
	int     weaponselect;		// 4	(+x2C)
	int     weaponsubtype;		// 4	(+x30)
	int     random_seed;		// 4	(+x34)
	short   mousedx;			// 2	(+x38)
	short   mousedy;			// 2	(+x3A)
	bool	unk3C;				// 4	(+x3C)
	byte	entityground[20];	// 20	(+x40)
	int		unk54;				// 4	(+x54)
	int		unk58;				// 4	(+x58)
	short	unk5A;				// 2	(+x5A)
	short	unk5C;				// 2	(+x5C)
	int		unk60;				// 4	(+x60)
	int		unk64;				// 4	(+x64)
	bool	unk68;				// 4	(+x68)
	byte	unk6C[240];			// 240	(+x6C)

	
	__forceinline CRC32_t GetChecksum( void ) const
	{
		CRC32_t crc;

		CRC32_Init(&crc);
		DWORD* t = (DWORD*)this;
		CRC32_ProcessBuffer(&crc, t + 1, 4);
		CRC32_ProcessBuffer(&crc, t + 2, 4);
		CRC32_ProcessBuffer(&crc, t + 3, 12);    
		CRC32_ProcessBuffer(&crc, t + 6, 4);   
		CRC32_ProcessBuffer(&crc, t + 7, 4);      
		CRC32_ProcessBuffer(&crc, t + 8, 4);         
		CRC32_ProcessBuffer(&crc, t + 9, 4);		
		CRC32_ProcessBuffer(&crc, t + 10, 1);        
		CRC32_ProcessBuffer(&crc, t + 11, 4);	
		CRC32_ProcessBuffer(&crc, t + 12, 4);
		CRC32_ProcessBuffer(&crc, t + 13, 4);
		CRC32_ProcessBuffer(&crc, t + 14, 2);
		CRC32_ProcessBuffer(&crc, (void*)((DWORD)this + 0x3A), 2);
		CRC32_ProcessBuffer(&crc, (void*)((DWORD)this + 0x59), 1);
		CRC32_Final(&crc);

		return crc;
	}

	__forceinline void FixSeed()
	{
		random_seed = MD5_PseudoRandom(command_number) & 0x7FFFFFFF;
	}

	__forceinline void operator=(CUserCmd* toset)
	{
		memcpy(toset, this, sizeof(CUserCmd));
	}
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_cmd;
	CRC32_t m_crc;
};


class CInput {
public:
    virtual void* CInput::Init_All(void) = 0;
    virtual void* CInput::Shutdown_All(void) = 0;
    virtual void* CInput::GetButtonBits(int) = 0;
    virtual void* CInput::CreateMove(int,float,bool) = 0;
    virtual void* CInput::ExtraMouseSample(float,bool) = 0;
    virtual void* CInput::WriteUsercmdDeltaToBuffer(bf_write *,int,int,bool) = 0;
    virtual void* CInput::EncodeUserCmdToBuffer(bf_write &,int) = 0;
    virtual void* CInput::DecodeUserCmdFromBuffer(bf_read &,int) = 0;
    virtual CUserCmd* CInput::GetUserCmd(int) = 0;
    virtual void* CInput::MakeWeaponSelection(void* /* C_BaseCombatWeapon * */) = 0;
    virtual void* CInput::KeyState(void* /* kbutton_t * */) = 0;
    virtual void* CInput::KeyEvent(int,ButtonCode_t,char  const*) = 0;
    virtual void* CInput::FindKey(char  const*) = 0;
    virtual void* CInput::ControllerCommands(void) = 0;
    virtual void* CInput::Joystick_Advanced(void) = 0;
    virtual void* CInput::Joystick_SetSampleTime(float) = 0;
    virtual void* CInput::IN_SetSampleTime(float) = 0;
    virtual void* CInput::AccumulateMouse(void) = 0;
    virtual void* CInput::ActivateMouse(void) = 0;
    virtual void* CInput::DeactivateMouse(void) = 0;
    virtual void* CInput::ClearStates(void) = 0;
    virtual void* CInput::GetLookSpring(void) = 0;
    virtual void* CInput::GetFullscreenMousePos(int *,int *,int *,int *) = 0;
    virtual void* CInput::SetFullscreenMousePos(int,int) = 0;
    virtual void* CInput::ResetMouse(void) = 0;
    virtual void* CInput::GetLastForwardMove(void) = 0;
    virtual void* CInput::Joystick_GetForward(void) = 0;
    virtual void* CInput::Joystick_GetSide(void) = 0;
    virtual void* CInput::Joystick_GetPitch(void) = 0;
    virtual void* CInput::Joystick_GetYaw(void) = 0;
    virtual void* CInput::CAM_Think(void) = 0;
    virtual void* CInput::CAM_IsThirdPerson(void) = 0;
    virtual void* CInput::CAM_ToThirdPerson(void) = 0;
    virtual void* CInput::CAM_ToFirstPerson(void) = 0;
    virtual void* CInput::CAM_StartMouseMove(void) = 0;
    virtual void* CInput::CAM_EndMouseMove(void) = 0;
    virtual void* CInput::CAM_StartDistance(void) = 0;
    virtual void* CInput::CAM_EndDistance(void) = 0;
    virtual void* CInput::CAM_InterceptingMouse(void) = 0;
    virtual void* CInput::CAM_ToOrthographic(void) = 0;
    virtual void* CInput::CAM_IsOrthographic(void) = 0;
    virtual void* CInput::CAM_OrthographicSize(float &,float &) = 0;
    virtual void* CInput::AddIKGroundContactInfo(int,float,float) = 0;
    virtual void* CInput::LevelInit(void) = 0;
    virtual void* CInput::ClearInputButton(int) = 0;
    virtual void* CInput::CAM_SetCameraThirdData(void* /* CameraThirdData_t * */,QAngle  const&) = 0;
    virtual void* CInput::CAM_CameraThirdThink(void) = 0;
    virtual void* CInput::EnableJoystickMode(void) = 0;
    virtual void* CInput::MouseWheeled(int) = 0;
    virtual void* CInput::CAM_CapYaw(float) = 0;
    virtual void* CInput::AdjustYaw(float,QAngle &) = 0;
	__forceinline CUserCmd* HGetUserCmd(int seq)
	{
		CUserCmd* cmds = (CUserCmd*)(((DWORD*)this)[49]);
		DWORD cmd = ((DWORD)cmds +  seq % 90 * sizeof(CUserCmd));
		return (CUserCmd*)cmd;
	}
	__forceinline CVerifiedUserCmd* HGetVUserCmd(int seq)
	{
		CVerifiedUserCmd* cmds = (CVerifiedUserCmd*)(((DWORD*)this)[50]);
		DWORD cmd = ((DWORD)cmds +  seq % 90 * sizeof(CVerifiedUserCmd));
		return (CVerifiedUserCmd*)cmd;
	}
	__forceinline void HSetUserCmd(int seq, CUserCmd* cmd)
	{
		CUserCmd* seqcmd = HGetUserCmd(seq);
		seqcmd = cmd;
		CVerifiedUserCmd* seqvcmd = HGetVUserCmd(seq);
		seqvcmd->m_cmd = *cmd;
		seqvcmd->m_crc = cmd->GetChecksum();
	}
};

#endif // D_CINP