#ifndef DISMAY_CCLIENTTOOLS
#define DISMAY_CCLIENTTOOLS

#include "../Forward.h"

#define CClientTools _CClientTools

class CClientTools
{
public:
	virtual CClientTools::~CClientTools() = 0;
	virtual void* CClientTools::AttachToEntity(void *) = 0;
	virtual void* CClientTools::DetachFromEntity(void *) = 0;
	virtual void* CClientTools::IsValidHandle(uint) = 0;
	virtual void* CClientTools::GetNumRecordables(void) = 0;
	virtual void* CClientTools::GetRecordable(int) = 0;
	virtual void* CClientTools::NextEntity(void *) = 0;
	virtual void* CClientTools::SetEnabled(uint,bool) = 0;
	virtual void* CClientTools::SetRecording(uint,bool) = 0;
	virtual void* CClientTools::ShouldRecord(uint) = 0;
	virtual void* CClientTools::GetToolHandleForEntityByIndex(int) = 0;
	virtual void* CClientTools::GetModelIndex(uint) = 0;
	virtual void* CClientTools::GetModelName(uint) = 0;
	virtual void* CClientTools::GetClassname(uint) = 0;
	virtual void* CClientTools::AddClientRenderable(IClientRenderable *,int) = 0;
	virtual void* CClientTools::RemoveClientRenderable(IClientRenderable *) = 0;
	virtual void* CClientTools::SetRenderGroup(IClientRenderable *,int) = 0;
	virtual void* CClientTools::MarkClientRenderableDirty(IClientRenderable *) = 0;
	virtual void* CClientTools::UpdateProjectedTexture(ushort,bool) = 0;
	virtual void* CClientTools::DrawSprite(IClientRenderable *,float,float,int,int,Color  const&,float,int *) = 0;
	virtual int CClientTools::GetLocalPlayer(void) = 0;
	virtual void* CClientTools::GetLocalPlayerEyePosition(Vector &,QAngle &,float &) = 0;
	virtual void* CClientTools::CreateShadow(CBaseHandle,int) = 0;
	virtual void* CClientTools::DestroyShadow(ushort) = 0;
	virtual void* CClientTools::CreateFlashlight(FlashlightState_t  const&) = 0;
	virtual void* CClientTools::DestroyFlashlight(ushort) = 0;
	virtual void* CClientTools::UpdateFlashlightState(ushort,FlashlightState_t  const&) = 0;
	virtual void* CClientTools::AddToDirtyShadowList(ushort,bool) = 0;
	virtual void* CClientTools::MarkRenderToTextureShadowDirty(ushort) = 0;
	virtual void* CClientTools::EnableRecordingMode(bool) = 0;
	virtual void* CClientTools::IsInRecordingMode(void) = 0;
	virtual void* CClientTools::TriggerTempEntity(KeyValues *) = 0;
	virtual void* CClientTools::GetOwningWeaponEntIndex(int) = 0;
	virtual void* CClientTools::GetEntIndex(void *) = 0;
	virtual void* CClientTools::FindGlobalFlexcontroller(char  const*) = 0;
	virtual void* CClientTools::GetGlobalFlexControllerName(int) = 0;
	virtual void* CClientTools::GetOwnerEntity(void *) = 0;
	virtual bool CClientTools::IsPlayer(void *) = 0;
	virtual bool CClientTools::IsBaseCombatCharacter(void *) = 0;
	virtual bool CClientTools::IsNPC(void *) = 0;
	virtual void* CClientTools::GetAbsOrigin(uint) = 0;
	virtual void* CClientTools::GetAbsAngles(uint) = 0;
	virtual void* CClientTools::ReloadParticleDefintions(char  const*,void  const*,int) = 0;
	virtual void* CClientTools::PostToolMessage(KeyValues *) = 0;
	virtual void* CClientTools::EnableParticleSystems(bool) = 0;
	virtual void* CClientTools::IsRenderingThirdPerson(void) = 0;
	virtual void* CClientTools::OnEntityDeleted(C_BaseEntity *) = 0;
	virtual void* CClientTools::OnEntityCreated(C_BaseEntity *) = 0;
};
#endif