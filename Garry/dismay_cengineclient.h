#ifndef CENGINECLIENT_H
#define CENGINECLIENT_H

#include "DVector.h"
#include "Forward.h"


typedef struct player_info_s
{
	// scoreboard information
	char			name[64];
	// local server user ID, unique while server is running
	int				userID;
	// global unique player identifer
	char			guid[33];
	// friends identification number
	unsigned int	friendsID;
	// friends name
	char			friendsName[64];
	// true, if player is a bot controlled by game.dll
	bool			fakeplayer;
	// true if player is the HLTV proxy
	bool			ishltv;
	// custom files CRC for this player
	unsigned long	customFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	filesDownloaded;
} player_info_t;
typedef DVector Vector;

class CEngineClient
{
public:
	virtual void* CEngineClient::GetIntersectingSurfaces(model_t  const*,Vector  const&,float,bool,SurfInfo *,int) = 0;
	virtual void* CEngineClient::GetLightForPoint(Vector  const&,bool) = 0;
	virtual void* CEngineClient::TraceLineMaterialAndLighting(Vector  const&,Vector  const&,Vector&,Vector&) = 0;
	virtual void* CEngineClient::ParseFile(char  const*,char *,int) = 0;
	virtual void* CEngineClient::CopyLocalFile(char  const*,char  const*) = 0;
	virtual void* CEngineClient::GetScreenSize(int &,int &) = 0;
	virtual void* CEngineClient::ServerCmd(char const*,bool) = 0;
	virtual void* CEngineClient::ClientCmd(char const*) = 0;
	virtual bool CEngineClient::GetPlayerInfo(int, player_info_s *) = 0;
	virtual void* CEngineClient::GetPlayerForUserID(int) = 0;
	virtual void* CEngineClient::TextMessageGet(char  const*) = 0;
	virtual bool CEngineClient::Con_IsVisible(void) = 0;
	virtual int CEngineClient::GetLocalPlayer(void) = 0;
	virtual void* CEngineClient::LoadModel(char  const*,bool) = 0;
	virtual void* CEngineClient::Time(void) = 0;
	virtual void* CEngineClient::GetLastTimeStamp(void) = 0;
	virtual void* CEngineClient::GetSentence(CAudioSource *) = 0;
	virtual void* CEngineClient::GetSentenceLength(CAudioSource *) = 0;
	virtual void* CEngineClient::IsStreaming(CAudioSource *) = 0;
	virtual void* CEngineClient::GetViewAngles(QAngle &) = 0;
	virtual void* CEngineClient::SetViewAngles(QAngle &) = 0;
	virtual int CEngineClient::GetMaxClients(void) = 0;
	virtual void* CEngineClient::Key_LookupBinding(char  const*) = 0;
	virtual void* CEngineClient::Key_BindingForKey(ButtonCode_t) = 0;
	virtual void* CEngineClient::StartKeyTrapMode(void) = 0;
	virtual bool CEngineClient::CheckDoneKeyTrapping(ButtonCode_t &) = 0;
	virtual bool CEngineClient::IsInGame(void) = 0;
	virtual bool CEngineClient::IsConnected(void) = 0;
	virtual void* CEngineClient::IsDrawingLoadingImage(void) = 0;
	virtual void* CEngineClient::Con_NPrintf(int,char  const*,...) = 0;
	virtual void* CEngineClient::Con_NXPrintf(con_nprint_s  const*,char  const*,...) = 0;
	virtual void* CEngineClient::IsBoxVisible(Vector  const&,Vector  const&) = 0;
	virtual void* CEngineClient::IsBoxInViewCluster(Vector  const&,Vector  const&) = 0;
	virtual void* CEngineClient::CullBox(Vector  const&,Vector  const&) = 0;
	virtual void* CEngineClient::Sound_ExtraUpdate(void) = 0;
	virtual void* CEngineClient::GetGameDirectory(void) = 0;
	virtual void* CEngineClient::WorldToScreenMatrix(void) = 0;
	virtual void* CEngineClient::WorldToViewMatrix(void) = 0;
	virtual void* CEngineClient::GameLumpVersion(int) = 0;
	virtual void* CEngineClient::GameLumpSize(int) = 0;
	virtual void* CEngineClient::LoadGameLump(int,void *,int) = 0;
	virtual void* CEngineClient::LevelLeafCount(void) = 0;
	virtual void* CEngineClient::GetBSPTreeQuery(void) = 0;
	virtual void* CEngineClient::LinearToGamma(float *,float *) = 0;
	virtual void* CEngineClient::LightStyleValue(int) = 0;
	virtual void* CEngineClient::ComputeDynamicLighting(Vector  const&,Vector  const*,Vector&) = 0;
	virtual void* CEngineClient::GetAmbientLightColor(Vector &) = 0;
	virtual void* CEngineClient::GetDXSupportLevel(void) = 0;
	virtual void* CEngineClient::SupportsHDR(void) = 0;
	virtual void* CEngineClient::Mat_Stub(IMaterialSystem *) = 0;
	virtual void* CEngineClient::GetChapterName(char *,int) = 0;
	virtual void* CEngineClient::GetLevelName(void) = 0;
	virtual void* CEngineClient::GetLevelVersion(void) = 0;
	virtual void* CEngineClient::GetVoiceTweakAPI(void) = 0;
	virtual void* CEngineClient::EngineStats_BeginFrame(void) = 0;
	virtual void* CEngineClient::EngineStats_EndFrame(void) = 0;
	virtual void* CEngineClient::FireEvents(void) = 0;
	virtual void* CEngineClient::GetLeavesArea(int *,int) = 0;
	virtual void* CEngineClient::DoesBoxTouchAreaFrustum(Vector  const&,Vector  const&,int) = 0;
	virtual void* CEngineClient::SetAudioState(AudioState_t  const&) = 0;
	virtual void* CEngineClient::SentenceGroupPick(int,char *,int) = 0;
	virtual void* CEngineClient::SentenceGroupPickSequential(int,char *,int,int,int) = 0;
	virtual void* CEngineClient::SentenceIndexFromName(char  const*) = 0;
	virtual void* CEngineClient::SentenceNameFromIndex(int) = 0;
	virtual void* CEngineClient::SentenceGroupIndexFromName(char  const*) = 0;
	virtual void* CEngineClient::SentenceGroupNameFromIndex(int) = 0;
	virtual void* CEngineClient::SentenceLength(int) = 0;
	virtual void* CEngineClient::ComputeLighting(Vector  const&,Vector  const*,bool,Vector&,Vector*) = 0;
	virtual void* CEngineClient::ActivateOccluder(int,bool) = 0;
	virtual void* CEngineClient::IsOccluded(Vector  const&,Vector  const&) = 0;
	virtual void* CEngineClient::SaveAllocMemory(ulong,ulong) = 0;
	virtual void* CEngineClient::SaveFreeMemory(void *) = 0;
	virtual INetChannel* CEngineClient::GetNetChannelInfo(void) = 0;
	virtual void* CEngineClient::DebugDrawPhysCollide(CPhysCollide  const*,IMaterial *,matrix3x4_t &,color32_s  const&) = 0;
	virtual void* CEngineClient::CheckPoint(char  const*) = 0;
	virtual void* CEngineClient::DrawPortals(void) = 0;
	virtual void* CEngineClient::IsPlayingDemo(void) = 0;
	virtual void* CEngineClient::IsRecordingDemo(void) = 0;
	virtual void* CEngineClient::IsPlayingTimeDemo(void) = 0;
	virtual void* CEngineClient::GetDemoRecordingTick(void) = 0;
	virtual void* CEngineClient::GetDemoPlaybackTick(void) = 0;
	virtual void* CEngineClient::GetDemoPlaybackStartTick(void) = 0;
	virtual void* CEngineClient::GetDemoPlaybackTimeScale(void) = 0;
	virtual void* CEngineClient::GetDemoPlaybackTotalTicks(void) = 0;
	virtual void* CEngineClient::IsPaused(void) = 0;
	virtual void* CEngineClient::IsTakingScreenshot(void) = 0;
	virtual void* CEngineClient::IsHLTV(void) = 0;
	virtual void* CEngineClient::IsLevelMainMenuBackground(void) = 0;
	virtual void* CEngineClient::GetMainMenuBackgroundName(char *,int) = 0;
	virtual void* CEngineClient::GetVideoModes(int &,void* /* vmode_s *& */) = 0;
	virtual void* CEngineClient::SetOcclusionParameters(OcclusionParams_t  const&) = 0;
	virtual void* CEngineClient::GetUILanguage(char *,int) = 0;
	virtual void* CEngineClient::IsSkyboxVisibleFromPoint(Vector  const&) = 0;
	virtual void* CEngineClient::GetMapEntitiesString(void) = 0;
	virtual void* CEngineClient::IsInEditMode(void) = 0;
	virtual void* CEngineClient::GetScreenAspectRatio(void) = 0;
	virtual void* CEngineClient::REMOVED_SteamRefreshLogin(char  const*,bool) = 0;
	virtual void* CEngineClient::REMOVED_SteamProcessCall(bool &) = 0;
	virtual void* CEngineClient::GetEngineBuildNumber(void) = 0;
	virtual void* CEngineClient::GetProductVersionString(void) = 0;
	virtual void* CEngineClient::GrabPreColorCorrectedFrame(int,int,int,int) = 0;
	virtual void* CEngineClient::IsHammerRunning(void) = 0;
	virtual void* CEngineClient::ExecuteClientCmd(char  const*) = 0;
	virtual void* CEngineClient::MapHasHDRLighting(void) = 0;
	virtual void* CEngineClient::GetAppID(void) = 0;
	virtual void* CEngineClient::GetLightForPointFast(Vector  const&,bool) = 0;
	virtual void* CEngineClient::ClientCmd_Unrestricted(char  const*) = 0;
	virtual void* CEngineClient::SetRestrictServerCommands(bool) = 0;
	virtual void* CEngineClient::SetRestrictClientCommands(bool) = 0;
	virtual void* CEngineClient::SetOverlayBindProxy(int,void *) = 0;
	virtual void* CEngineClient::CopyFrameBufferToMaterial(char  const*) = 0;
	virtual void* CEngineClient::ChangeTeam(char  const*) = 0;
	virtual void* CEngineClient::ReadConfiguration(bool) = 0;
	virtual void* CEngineClient::SetAchievementMgr(IAchievementMgr *) = 0;
	virtual void* CEngineClient::GetAchievementMgr(void) = 0;
	virtual void* CEngineClient::MapLoadFailed(void) = 0;
	virtual void* CEngineClient::SetMapLoadFailed(bool) = 0;
	virtual void* CEngineClient::IsLowViolence(void) = 0;
	virtual void* CEngineClient::GetMostRecentSaveGame(void) = 0;
	virtual void* CEngineClient::SetMostRecentSaveGame(char  const*) = 0;
	virtual void* CEngineClient::StartXboxExitingProcess(void) = 0;
	virtual void* CEngineClient::IsSaveInProgress(void) = 0;
	virtual void* CEngineClient::OnStorageDeviceAttached(void) = 0;
	virtual void* CEngineClient::OnStorageDeviceDetached(void) = 0;
	virtual void* CEngineClient::ResetDemoInterpolation(void) = 0;
	virtual void* CEngineClient::SetGamestatsData(CGamestatsData *) = 0;
	virtual void* CEngineClient::GetGamestatsData(void) = 0;
	virtual void* CEngineClient::GetMouseDelta(int &,int &,bool) = 0;
	virtual void* CEngineClient::ServerCmdKeyValues(void* /* KeyValues * */) = 0;
	virtual void* CEngineClient::IsSkippingPlayback(void) = 0;
	virtual void* CEngineClient::IsLoadingDemo(void) = 0;
	virtual void* CEngineClient::IsPlayingDemoALocallyRecordedDemo(void) = 0;
	virtual void* CEngineClient::Key_LookupBindingExact(char  const*) = 0;
	virtual void* CEngineClient::GMOD_SetTimeManipulator(float) = 0;
	virtual void* CEngineClient::GMOD_SendToServer(void *,uint) = 0;
	virtual void* CEngineClient::GMOD_PlaceDecalMaterial(IMaterial *,bool,int,IClientEntity *,Vector  const&,Vector  const&,color32_s  const&,float,float) = 0;
	virtual void* CEngineClient::GMOD_GetSpew(char *,ulong) = 0;
	virtual void* CEngineClient::GMOD_SetViewEntity(uint) = 0;
	virtual void* CEngineClient::GMOD_BrushMaterialOverride(IMaterial *) = 0;
	virtual void* CEngineClient::GMOD_R_RedownloadAllLightmaps(void) = 0;
	virtual void* CEngineClient::GetProtocolVersion(void) = 0;
	virtual void* CEngineClient::IsWindowedMode(void) = 0;
	virtual void* CEngineClient::FlashWindow(void) = 0;
	virtual void* CEngineClient::GetClientVersion(void) = 0;
	virtual void* CEngineClient::IsActiveApp(void) = 0;
	virtual void* CEngineClient::DisconnectInternal(void) = 0;
	virtual void* CEngineClient::IsInCommentaryMode(void) = 0;
};
#endif // CENGINECLIENT_H