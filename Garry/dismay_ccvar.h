#ifndef CCvar__
#define CCvar__

#include "Forward.h"
#include "DColor.h"


class CCvar
{
public:
	virtual void* CCvar::Connect(void * (*)(char  const*,int *)) = 0;
	virtual void* CCvar::Disconnect(void) = 0;
	virtual void* CCvar::QueryInterface(char  const*) = 0;
	virtual void* CCvar::Init(void) = 0;
	virtual void* CCvar::Shutdown(void) = 0;
	virtual void* CCvar::AllocateDLLIdentifier(void) = 0;
	virtual void* CCvar::RegisterConCommand(ConCommandBase *) = 0;
	virtual void* CCvar::UnregisterConCommand(ConCommandBase *) = 0;
	virtual void* CCvar::UnregisterConCommands(int) = 0;
	virtual void* CCvar::GetCommandLineValue(char  const*) = 0;
	virtual ConCommandBase* CCvar::FindCommandBase(char  const*) = 0;
	virtual const ConCommandBase* CCvar::FindCommandBaseConst(char  const*) = 0;
	virtual ConVar* CCvar::FindVar(char  const*) = 0;
	virtual const ConVar* CCvar::FindVarConst(char  const*) = 0;
	virtual ConCommand* CCvar::FindCommand(char  const*) = 0;
	virtual const ConCommand* CCvar::FindCommandConst(char  const*) = 0;
	virtual ConCommandBase* CCvar::GetCommands(void) = 0;
	virtual const ConCommandBase* CCvar::GetCommandsConst(void) = 0;
	virtual void* CCvar::InstallGlobalChangeCallback(void (*)(IConVar *,char  const*,float)) = 0;
	virtual void* CCvar::RemoveGlobalChangeCallback(void (*)(IConVar *,char  const*,float)) = 0;
	virtual void* CCvar::CallGlobalChangeCallbacks(ConVar *,char  const*,float) = 0;
	virtual void* CCvar::InstallConsoleDisplayFunc(IConsoleDisplayFunc *) = 0;
	virtual void* CCvar::RemoveConsoleDisplayFunc(IConsoleDisplayFunc *) = 0;
	virtual void* CCvar::ConsoleColorPrintf(Color  const&,char  const*,...) = 0;
	virtual void* CCvar::ConsolePrintf(char  const*,...) = 0;
	virtual void* CCvar::ConsoleDPrintf(char  const*,...) = 0;
	virtual void* CCvar::RevertFlaggedConVars(int) = 0;
	virtual void* CCvar::InstallCVarQuery(ICvarQuery *) = 0;
	virtual void* CCvar::IsMaterialThreadSetAllowed(void) = 0;
	virtual void* CCvar::QueueMaterialThreadSetValue(ConVar *,char  const*) = 0;
	virtual void* CCvar::QueueMaterialThreadSetValue(ConVar *,int) = 0;
	virtual void* CCvar::QueueMaterialThreadSetValue(ConVar *,float) = 0;
	virtual void* CCvar::HasQueuedMaterialThreadConVarSets(void) = 0;
	virtual void* CCvar::ProcessQueuedMaterialThreadConVarSets(void) = 0;
	virtual void* CCvar::FactoryInternalIterator(void) = 0;
};

#endif // CCvar__