#ifndef VPANEL__
#define VPANEL__

#include "Forward.h"

class VPanel
{
public:
	virtual VPanel::~VPanel() = 0;
	virtual void VPanel::Destruct02() = 0;
	virtual void* VPanel::Init(IClientPanel *) = 0;
	virtual void* VPanel::Plat(void) = 0;
	virtual void* VPanel::SetPlat(SurfacePlat *) = 0;
	virtual HPanel VPanel::GetHPanel(void) = 0;
	virtual void VPanel::SetHPanel(ulong) = 0;
	virtual bool VPanel::PopupWantsFront(void) = 0;
	virtual void VPanel::SetPopupWantsFront(bool) = 0;
	virtual bool VPanel::IsPopup(void) = 0;
	virtual void VPanel::SetPopup(bool) = 0;
	virtual bool VPanel::IsFullyVisible(void) = 0;
	virtual void VPanel::SetPos(int,int) = 0;
	virtual void VPanel::GetPos(int &,int &) = 0;
	virtual void VPanel::SetSize(int,int) = 0;
	virtual void VPanel::GetSize(int &,int &) = 0;
	virtual void VPanel::SetMinimumSize(int,int) = 0;
	virtual void VPanel::GetMinimumSize(int &,int &) = 0;
	virtual void VPanel::SetZPos(int) = 0;
	virtual int VPanel::GetZPos(void) = 0;
	virtual void VPanel::GetAbsPos(int &,int &) = 0;
	virtual void VPanel::GetClipRect(int &,int &,int &,int &) = 0;
	virtual void VPanel::SetInset(int,int,int,int) = 0;
	virtual void VPanel::GetInset(int &,int &,int &,int &) = 0;
	virtual void VPanel::Solve(void) = 0;
	virtual void VPanel::SetVisible(bool) = 0;
	virtual void VPanel::SetEnabled(bool) = 0;
	virtual bool VPanel::IsVisible(void) = 0;
	virtual bool VPanel::IsEnabled(void) = 0;
	virtual void VPanel::SetParent(VPanel*) = 0;
	virtual int VPanel::GetChildCount(void) = 0;
	virtual VPanel* VPanel::GetChild(int) = 0;
	virtual VPanel* VPanel::GetParent(void) = 0;
	virtual void* VPanel::MoveToFront(void) = 0;
	virtual void* VPanel::MoveToBack(void) = 0;
	virtual	bool VPanel::HasParent(VPanel*) = 0;
	virtual void* VPanel::GetChildren(void) = 0;
	virtual const char* VPanel::GetName(void) = 0;
	virtual const char* VPanel::GetClassName(void) = 0;
	virtual void* VPanel::GetScheme(void) = 0;
	virtual void* VPanel::SendMessage(KeyValues *,uint) = 0;
	virtual void* VPanel::Client(void) = 0;
	virtual void* VPanel::SetKeyBoardInputEnabled(bool) = 0;
	virtual void* VPanel::SetMouseInputEnabled(bool) = 0;
	virtual bool VPanel::IsKeyBoardInputEnabled(void) = 0;
	virtual bool VPanel::IsMouseInputEnabled(void) = 0;
	virtual bool VPanel::IsTopmostPopup(void) = 0;
	virtual void* VPanel::SetTopmostPopup(bool) = 0;
	virtual void* VPanel::SetSiblingPin(VPanel*,uchar,uchar) = 0;
	virtual void* VPanel::GetInternalAbsPos(int &,int &) = 0;
};
#endif