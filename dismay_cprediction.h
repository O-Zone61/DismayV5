#ifndef PREDICTION
#define PREDICTION
#include "DVector.h"
#include "DAngle.h"

class C_BasePlayer;
class CMoveData;
class CUserCmd;
class IMoveHelper;


class CPrediction
{
public:
	virtual CPrediction::~CPrediction() = 0;
	virtual void* destruct02() = 0;
	virtual void* CPrediction::Init(void) = 0;
	virtual void* CPrediction::Shutdown(void) = 0;
	virtual void* CPrediction::Update(int,bool,int,int) = 0;
	virtual void* CPrediction::PreEntityPacketReceived(int,int) = 0;
	virtual void* CPrediction::PostEntityPacketReceived(void) = 0;
	virtual void* CPrediction::PostNetworkDataReceived(int) = 0;
	virtual void* CPrediction::OnReceivedUncompressedPacket(void) = 0;
	virtual void* CPrediction::GetViewOrigin(Vector &) = 0;
	virtual void* CPrediction::SetViewOrigin(Vector &) = 0;
	virtual void* CPrediction::GetViewAngles(QAngle &) = 0;
	virtual void* CPrediction::SetViewAngles(QAngle &) = 0;
	virtual void* CPrediction::GetLocalViewAngles(QAngle &) = 0;
	virtual void* CPrediction::SetLocalViewAngles(QAngle &) = 0;
	virtual bool  CPrediction::InPrediction(void) = 0;
	virtual bool  CPrediction::IsFirstTimePredicted(void) = 0;
	virtual int   CPrediction::GetIncomingPacketNumber(void) = 0;
	virtual void* CPrediction::RunCommand(C_BasePlayer *,CUserCmd *,IMoveHelper *) = 0;
	virtual void* CPrediction::SetupMove(C_BasePlayer *,CUserCmd *,IMoveHelper *,CMoveData *) = 0;
	virtual void* CPrediction::FinishMove(C_BasePlayer *,CUserCmd *,CMoveData *) = 0;
	virtual void* CPrediction::SetIdealPitch(C_BasePlayer *,Vector  const&,QAngle  const&,Vector  const&) = 0;
	virtual void* CPrediction::_Update(bool,bool,int,int) = 0;
};

#endif // PREDICTION