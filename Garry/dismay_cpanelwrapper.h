#ifndef DISMAY_VPANEL
#define DISMAY_VPANEL

typedef unsigned char uchar;
typedef unsigned int uint;

class CPanelWrapper
{
public:
	virtual CPanelWrapper::~CPanelWrapper() = 0;
	virtual void* CPanelWrapper::Init(uint, void* /* vgui::IClientPanel * */ ) = 0;
	virtual void* CPanelWrapper::SetPos(uint,int,int) = 0;
	virtual void* CPanelWrapper::GetPos(uint,int &,int &) = 0;
	virtual void* CPanelWrapper::SetSize(uint,int,int) = 0;
	virtual void* CPanelWrapper::GetSize(uint,int &,int &) = 0;
	virtual void* CPanelWrapper::SetMinimumSize(uint,int,int) = 0;
	virtual void* CPanelWrapper::GetMinimumSize(uint,int &,int &) = 0;
	virtual void* CPanelWrapper::SetZPos(uint,int) = 0;
	virtual void* CPanelWrapper::GetZPos(uint) = 0;
	virtual void* CPanelWrapper::GetAbsPos(uint,int &,int &) = 0;
	virtual void* CPanelWrapper::GetClipRect(uint,int &,int &,int &,int &) = 0;
	virtual void* CPanelWrapper::SetInset(uint,int,int,int,int) = 0;
	virtual void* CPanelWrapper::GetInset(uint,int &,int &,int &,int &) = 0;
	virtual void* CPanelWrapper::SetVisible(uint,bool) = 0;
	virtual bool CPanelWrapper::IsVisible(uint) = 0;
	virtual void* CPanelWrapper::SetParent(uint,uint) = 0;
	virtual void* CPanelWrapper::GetChildCount(uint) = 0;
	virtual void* CPanelWrapper::GetChild(uint,int) = 0;
	virtual void* CPanelWrapper::GetChildren(uint) = 0;
	virtual void* CPanelWrapper::GetParent(uint) = 0;
	virtual void* CPanelWrapper::MoveToFront(uint) = 0;
	virtual void* CPanelWrapper::MoveToBack(uint) = 0;
	virtual void* CPanelWrapper::HasParent(uint,uint) = 0;
	virtual void* CPanelWrapper::IsPopup(uint) = 0;
	virtual void* CPanelWrapper::SetPopup(uint,bool) = 0;
	virtual bool CPanelWrapper::IsFullyVisible(uint) = 0;
	virtual void* CPanelWrapper::GetScheme(uint) = 0;
	virtual void* CPanelWrapper::IsProportional(uint) = 0;
	virtual void* CPanelWrapper::IsAutoDeleteSet(uint) = 0;
	virtual void* CPanelWrapper::DeletePanel(uint) = 0;
	virtual void* CPanelWrapper::SetKeyBoardInputEnabled(uint,bool) = 0;
	virtual void* CPanelWrapper::SetMouseInputEnabled(uint,bool) = 0;
	virtual void* CPanelWrapper::IsKeyBoardInputEnabled(uint) = 0;
	virtual void* CPanelWrapper::IsMouseInputEnabled(uint) = 0;
	virtual void* CPanelWrapper::Solve(uint) = 0;
	virtual const char* CPanelWrapper::GetName(uint) = 0;
	virtual const char* CPanelWrapper::GetClassName(uint) = 0;
	virtual void* CPanelWrapper::SendMessage(uint,void * /* KeyValues * */ ,uint) = 0;
	virtual void* CPanelWrapper::Think(uint) = 0;
	virtual void* CPanelWrapper::PerformApplySchemeSettings(uint) = 0;
	virtual void* CPanelWrapper::PaintTraverse(uint,bool,bool) = 0;
	virtual void* CPanelWrapper::Repaint(uint) = 0;
	virtual void* CPanelWrapper::IsWithinTraverse(uint,int,int,bool) = 0;
	virtual void* CPanelWrapper::OnChildAdded(uint,uint) = 0;
	virtual void* CPanelWrapper::OnSizeChanged(uint,int,int) = 0;
	virtual void* CPanelWrapper::InternalFocusChanged(uint,bool) = 0;
	virtual void* CPanelWrapper::RequestInfo(uint, void* /* KeyValues * */) = 0;
	virtual void* CPanelWrapper::RequestFocus(uint,int) = 0;
	virtual void* CPanelWrapper::RequestFocusPrev(uint,uint) = 0;
	virtual void* CPanelWrapper::RequestFocusNext(uint,uint) = 0;
	virtual void* CPanelWrapper::GetCurrentKeyFocus(uint) = 0;
	virtual void* CPanelWrapper::GetTabPosition(uint) = 0;
	virtual void* CPanelWrapper::Plat(uint) = 0;
	virtual void* CPanelWrapper::SetPlat(uint,void* /* vgui::SurfacePlat * */ ) = 0;
	virtual void* CPanelWrapper::GetPanel(uint,char  const*) = 0;
	virtual void* CPanelWrapper::IsEnabled(uint) = 0;
	virtual void* CPanelWrapper::SetEnabled(uint,bool) = 0;
	virtual bool CPanelWrapper::IsTopmostPopup(uint) = 0;
	virtual void* CPanelWrapper::SetTopmostPopup(uint,bool) = 0;
	virtual void* CPanelWrapper::SetSiblingPin(uint,uint,uchar,uchar) = 0;
	virtual void* CPanelWrapper::PopupWantsFront(uint) = 0;
	virtual void* CPanelWrapper::SetPopupWantsFront(uint,bool) = 0;
	virtual void* CPanelWrapper::Client(uint) = 0;
	virtual void* CPanelWrapper::GetModuleName(uint) = 0;
};
#undef uint
#endif