#pragma once
#ifndef D_CCLIENT
#define D_CCLIENT
#include "../DDismay.h"

unk(CGlobalVarsBase);
unk(bf_write);
unk(bf_read);
unk(vrect_t);
unk(CViewSetup);
unk(ScreenFade_t);
unk(CEngineSprite);
unk(ClientFrameStage_t);
unk(CSaveRestoreData);
unk(datamap_t);
unk(typedescription_t);

class CClient
{
public://0
	virtual void* CClient::Init(void * (*)(char  const*,int *),void * (*)(char  const*,int *),CGlobalVarsBase *,void* /* IGet * */ ) = 0;
	virtual void* CClient::PostInit(void) = 0;
	virtual void* CClient::Shutdown(void) = 0;
	virtual void* CClient::ReplayInit(void * (*)(char  const*,int *)) = 0;
	virtual void* CClient::ReplayPostInit(void) = 0;
	virtual void* CClient::LevelInitPreEntity(char  const*) = 0;
	virtual void* CClient::LevelInitPostEntity(void) = 0;
	virtual void* CClient::LevelShutdown(void) = 0;
	virtual void* CClient::GetAllClasses(void) = 0;
	virtual void* CClient::HudVidInit(void) = 0;//10
	virtual void* CClient::HudProcessInput(bool) = 0;
	virtual void CClient::HudUpdate(bool) = 0;
	virtual void* CClient::HudReset(void) = 0;
	virtual void* CClient::HudText(char  const*) = 0;
	virtual void* CClient::IN_ActivateMouse(void) = 0;
	virtual void* CClient::IN_DeactivateMouse(void) = 0;
	virtual void* CClient::IN_Accumulate(void) = 0;
	virtual void* CClient::IN_ClearStates(void) = 0;
	virtual void* CClient::IN_IsKeyDown(char  const*,bool &) = 0;
	virtual void* CClient::IN_OnMouseWheeled(int) = 0;
	virtual void* CClient::IN_KeyEvent(int,ButtonCode_t,char  const*) = 0;
	virtual void* CClient::CreateMove(int,float,bool) = 0;
	virtual void* CClient::ExtraMouseSample(float,bool) = 0;
	virtual void* CClient::WriteUsercmdDeltaToBuffer(bf_write *,int,int,bool) = 0;
	virtual void* CClient::EncodeUserCmdToBuffer(bf_write &,int) = 0;
	virtual void* CClient::DecodeUserCmdFromBuffer(bf_read &,int) = 0;
	virtual void* CClient::View_Render(vrect_t *) = 0;
	virtual void* CClient::RenderView(CViewSetup  const&,int,int) = 0;
	virtual void* CClient::View_Fade(ScreenFade_t *) = 0;
	virtual void* CClient::SetCrosshairAngle(QAngle  const&) = 0;
	virtual void* CClient::InitSprite(CEngineSprite *,char  const*) = 0;
	virtual void* CClient::ShutdownSprite(CEngineSprite *) = 0;
	virtual void* CClient::GetSpriteSize(void) = 0;
	virtual void* CClient::VoiceStatus(int,int) = 0;
	virtual void* CClient::InstallStringTableCallback(char  const*) = 0;
	virtual void* CClient::FrameStageNotify(ClientFrameStage_t) = 0;
	virtual void* CClient::DispatchUserMessage(int,bf_read &) = 0;
	virtual void* CClient::SaveInit(int) = 0;
	virtual void* CClient::SaveWriteFields(CSaveRestoreData *,char  const*,void *,datamap_t *,typedescription_t *,int) = 0;
	virtual void* CClient::SaveReadFields(CSaveRestoreData *,char  const*,void *,datamap_t *,typedescription_t *,int) = 0;
	virtual void* CClient::PreSave(CSaveRestoreData *) = 0;
	virtual void* CClient::Save(CSaveRestoreData *) = 0;
	virtual void* CClient::WriteSaveHeaders(CSaveRestoreData *) = 0;
	virtual void* CClient::ReadRestoreHeaders(CSaveRestoreData *) = 0;
	virtual void* CClient::Restore(CSaveRestoreData *,bool) = 0;
	virtual void* CClient::DispatchOnRestore(void) = 0;
	virtual void* CClient::GetStandardRecvProxies(void) = 0;
	virtual void* CClient::WriteSaveGameScreenshot(char  const*) = 0;
	virtual void* CClient::EmitSentenceCloseCaption(char  const*) = 0;
	virtual void* CClient::EmitCloseCaption(char  const*,float) = 0;
	virtual void* CClient::CanRecordDemo(char *,int) = 0;
	virtual void* CClient::OnDemoRecordStart(char  const*) = 0;
	virtual void* CClient::OnDemoRecordStop(void) = 0;
	virtual void* CClient::OnDemoPlaybackStart(char  const*) = 0;
	virtual void* CClient::OnDemoPlaybackStop(void) = 0;
	virtual void* CClient::ShouldDrawDropdownConsole(void) = 0;
	virtual void* CClient::GetScreenWidth(void) = 0;
	virtual void* CClient::GetScreenHeight(void) = 0;
	virtual void* CClient::WriteSaveGameScreenshotOfSize(char  const*,int,int,bool,bool) = 0;
	virtual void* CClient::GetPlayerView(CViewSetup &) = 0;
	virtual void* CClient::SetupGameProperties(void* /* CUtlVector&<_XUSER_PROPERTY,CUtlMemory<CUtlVector&,int>> */ ) = 0;
	virtual void* CClient::GetPresenceID(char  const*) = 0;
	virtual void* CClient::GetPropertyIdString(unsigned int) = 0;
	virtual void* CClient::GetPropertyDisplayString(unsigned int,unsigned int,char *,int) = 0;
	virtual void* CClient::InvalidateMdlCache(void) = 0;
	virtual void* CClient::IN_SetSampleTime(float) = 0;
	virtual void* CClient::ReloadFilesInList(void* /* IFileList * */ ) = 0;
	virtual void* CClient::StartStatsReporting(void *,bool) = 0;
	virtual void* CClient::HandleUiToggle(void) = 0;
	virtual void* CClient::ShouldAllowConsole(void) = 0;
	virtual void* CClient::GetRenamedRecvTableInfos(void) = 0;
	virtual void* CClient::GetClientUIMouthInfo(void) = 0;
	virtual void* CClient::FileReceived(char  const*,unsigned int) = 0;
	virtual void* CClient::TranslateEffectForVisionFilter(char  const*,char  const*) = 0;
	virtual void* CClient::ClientAdjustStartSoundParams(void* /* StartSoundParams_t & */ ) = 0;
	virtual void* CClient::DisconnectAttempt(void) = 0;
	virtual void* CClient::GMOD_ReceiveServerMessage(bf_read *,int) = 0;
	virtual void* CClient::GMOD_DoSnapshots(void) = 0;
	virtual void* CClient::GMOD_VoiceVolume(unsigned int,float) = 0;
	virtual void* CClient::GMOD_OnDrawSkybox(void) = 0;
	virtual void* CClient::IN_MouseWheelAnalog(int) = 0;
};

#endif //D_CCLIENT