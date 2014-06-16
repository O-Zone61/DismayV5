#ifndef CVGUI
#define CVGUI

#include "Forward.h"

class CVGui
{
public:
	virtual void* CVGui::Connect(void * (*)(char  const*,int *)) = 0;
	virtual void* CVGui::Disconnect(void) = 0;
	virtual void* CVGui::QueryInterface(char  const*) = 0;
	virtual void* CVGui::Init(void) = 0;
	virtual void* CVGui::Shutdown(void) = 0;
	virtual void* CVGui::Start(void) = 0;
	virtual void* CVGui::Stop(void) = 0;
	virtual void* CVGui::IsRunning(void) = 0;
	virtual void* CVGui::RunFrame(void) = 0;
	virtual void* CVGui::ShutdownMessage(uint) = 0;
	virtual void* CVGui::AllocPanel(void) = 0;
	virtual void* CVGui::FreePanel(uint) = 0;
	virtual void* CVGui::DPrintf(char  const*,...) = 0;
	virtual void* CVGui::DPrintf2(char  const*,...) = 0;
	virtual void* CVGui::SpewAllActivePanelNames(void) = 0;
	virtual	HPanel CVGui::PanelToHandle(uint) = 0;
	virtual	uint CVGui::HandleToPanel(ulong) = 0;
	virtual void* CVGui::MarkPanelForDeletion(uint) = 0;
	virtual void* CVGui::AddTickSignal(uint,int) = 0;
	virtual void* CVGui::RemoveTickSignal(uint) = 0;
	virtual void* CVGui::PostMessage(uint,KeyValues *,uint,float) = 0;
	virtual void* CVGui::CreateContext(void) = 0;
	virtual void* CVGui::DestroyContext(int) = 0;
	virtual void* CVGui::AssociatePanelWithContext(int,uint) = 0;
	virtual void* CVGui::ActivateContext(int) = 0;
	virtual void* CVGui::SetSleep(bool) = 0;
};

#endif CVGUI