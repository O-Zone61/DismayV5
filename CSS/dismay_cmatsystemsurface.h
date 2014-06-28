#ifndef DISMAY_CMATSYSSURF
#define DISMAY_CMATSYSSURF

#include "../DColor.h"
#include "../DDismay.h"
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;

unk(ImageFormat);
unk(InputEvent_t);
unk(VMatrix);

class CMatSystemSurface
{
public:
	virtual void* CMatSystemSurface::Connect(void * (*)(char  const*,int *)) = 0;
	virtual void* CMatSystemSurface::Disconnect(void) = 0;
	virtual void* CMatSystemSurface::QueryInterface(char  const*) = 0;
	virtual void* CMatSystemSurface::Init(void) = 0;
	virtual void* CMatSystemSurface::Shutdown(void) = 0;
	virtual void* CMatSystemSurface::RunFrame(void) = 0;
	virtual void* CMatSystemSurface::GetEmbeddedPanel(void) = 0;
	virtual void* CMatSystemSurface::SetEmbeddedPanel(uint) = 0;
	virtual void* CMatSystemSurface::PushMakeCurrent(uint,bool) = 0;
	virtual void* CMatSystemSurface::PopMakeCurrent(uint) = 0;
	virtual void* CMatSystemSurface::DrawSetColor(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawSetColor(Color) = 0;
	virtual void* CMatSystemSurface::DrawFilledRect(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawFilledRectArray(void*,int) = 0;
	virtual void* CMatSystemSurface::DrawOutlinedRect(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawLine(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawPolyLine(int *,int *,int) = 0;
	virtual void* CMatSystemSurface::DrawSetTextFont(ulong) = 0;
	virtual void* CMatSystemSurface::DrawSetTextColor(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawSetTextColor(Color) = 0;
	virtual void* CMatSystemSurface::DrawSetTextPos(int,int) = 0;
	virtual void* CMatSystemSurface::DrawGetTextPos(int &,int &) = 0;
	virtual void* CMatSystemSurface::DrawPrintText(wchar_t  const*,int, ulong) = 0;
	virtual void* CMatSystemSurface::DrawUnicodeChar(wchar_t, ulong) = 0;
	virtual void* CMatSystemSurface::DrawFlushText(void) = 0;
	virtual void* CMatSystemSurface::CreateHTMLWindow(/* vgui::IHTMLEvents *, */ uint) = 0;
	virtual void* CMatSystemSurface::PaintHTMLWindow(/* vgui::IHTML * */) = 0;
	virtual void* CMatSystemSurface::DeleteHTMLWindow(/* vgui::IHTML * */) = 0;
	virtual void* CMatSystemSurface::DrawGetTextureId(char  const*) = 0;
	virtual void* CMatSystemSurface::DrawGetTextureFile(int,char *,int) = 0;
	virtual void* CMatSystemSurface::DrawSetTextureFile(int,char  const*,int,bool) = 0;
	virtual void* CMatSystemSurface::DrawSetTextureRGBA(int,uchar  const*,int,int,int,bool) = 0;
	virtual void* CMatSystemSurface::DrawSetTexture(int) = 0;
	virtual void* CMatSystemSurface::DrawGetTextureSize(int,int &,int &) = 0;
	virtual void* CMatSystemSurface::DrawTexturedRect(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::IsTextureIDValid(int) = 0;
	virtual void* CMatSystemSurface::DeleteTextureByID(int) = 0;
	virtual void* CMatSystemSurface::CreateNewTextureID(bool) = 0;
	virtual void* CMatSystemSurface::GetScreenSize(int &,int &) = 0;
	virtual void* CMatSystemSurface::SetAsTopMost(uint,bool) = 0;
	virtual void* CMatSystemSurface::BringToFront(uint) = 0;
	virtual void* CMatSystemSurface::SetForegroundWindow(uint) = 0;
	virtual void* CMatSystemSurface::SetPanelVisible(uint,bool) = 0;
	virtual void* CMatSystemSurface::SetMinimized(uint,bool) = 0;
	virtual void* CMatSystemSurface::IsMinimized(uint) = 0;
	virtual void* CMatSystemSurface::FlashWindow(uint,bool) = 0;
	virtual void* CMatSystemSurface::SetTitle(uint,wchar_t  const*) = 0;
	virtual void* CMatSystemSurface::SetAsToolBar(uint,bool) = 0;
	virtual void* CMatSystemSurface::CreatePopup(uint,bool,bool,bool,bool,bool) = 0;
	virtual void* CMatSystemSurface::SwapBuffers(uint) = 0;
	virtual void* CMatSystemSurface::Invalidate(uint) = 0;
	virtual void* CMatSystemSurface::SetCursor(ulong) = 0;
	virtual void* CMatSystemSurface::SetCursorAlwaysVisible(bool) = 0;
	virtual void* CMatSystemSurface::IsCursorVisible(void) = 0;
	virtual void* CMatSystemSurface::ApplyChanges(void) = 0;
	virtual void* CMatSystemSurface::IsWithin(int,int) = 0;
	virtual void* CMatSystemSurface::HasFocus(void) = 0;
	virtual void* CMatSystemSurface::SupportsFeature(/* vgui::ISurface::SurfaceFeature_e */) = 0;
	virtual void* CMatSystemSurface::RestrictPaintToSinglePanel(uint) = 0;
	virtual void* CMatSystemSurface::SetModalPanel(uint) = 0;
	virtual void* CMatSystemSurface::GetModalPanel(void) = 0;
	virtual void* CMatSystemSurface::UnlockCursor(void) = 0;
	virtual void* CMatSystemSurface::LockCursor(void) = 0;
	virtual void* CMatSystemSurface::SetTranslateExtendedKeys(bool) = 0;
	virtual void* CMatSystemSurface::GetTopmostPopup(void) = 0;
	virtual void* CMatSystemSurface::SetTopLevelFocus(uint) = 0;
	virtual void* CMatSystemSurface::CreateFont(void) = 0;
	virtual void* CMatSystemSurface::SetFontGlyphSet(ulong,char  const*,int,int,int,int,int,int,int) = 0;
	virtual void* CMatSystemSurface::AddCustomFontFile(char  const*,char  const*) = 0;
	virtual void* CMatSystemSurface::GetFontTall(ulong) = 0;
	virtual void* CMatSystemSurface::GetFontTallRequested(ulong) = 0;
	virtual void* CMatSystemSurface::GetFontAscent(ulong,wchar_t) = 0;
	virtual void* CMatSystemSurface::IsFontAdditive(ulong) = 0;
	virtual void* CMatSystemSurface::GetCharABCwide(ulong,int,int &,int &,int &) = 0;
	virtual void* CMatSystemSurface::GetCharacterWidth(ulong,int) = 0;
	virtual void* CMatSystemSurface::GetTextSize(ulong,wchar_t  const*,int &,int &) = 0;
	virtual void* CMatSystemSurface::GetNotifyPanel(void) = 0;
	virtual void* CMatSystemSurface::SetNotifyIcon(uint,ulong,uint,char  const*) = 0;
	virtual void* CMatSystemSurface::PlaySound(char  const*) = 0;
	virtual void* CMatSystemSurface::GetPopupCount(void) = 0;
	virtual void* CMatSystemSurface::GetPopup(int) = 0;
	virtual void* CMatSystemSurface::ShouldPaintChildPanel(uint) = 0;
	virtual void* CMatSystemSurface::RecreateContext(uint) = 0;
	virtual void* CMatSystemSurface::AddPanel(uint) = 0;
	virtual void* CMatSystemSurface::ReleasePanel(uint) = 0;
	virtual void* CMatSystemSurface::MovePopupToFront(uint) = 0;
	virtual void* CMatSystemSurface::MovePopupToBack(uint) = 0;
	virtual void* CMatSystemSurface::SolveTraverse(uint,bool) = 0;
	virtual void* CMatSystemSurface::PaintTraverse(uint) = 0;
	virtual void* CMatSystemSurface::EnableMouseCapture(uint,bool) = 0;
	virtual void* CMatSystemSurface::GetWorkspaceBounds(int &,int &,int &,int &) = 0;
	virtual void* CMatSystemSurface::GetAbsoluteWindowBounds(int &,int &,int &,int &) = 0;
	virtual void* CMatSystemSurface::GetProportionalBase(int &,int &) = 0;
	virtual void* CMatSystemSurface::CalculateMouseVisible(void) = 0;
	virtual void* CMatSystemSurface::NeedKBInput(void) = 0;
	virtual void* CMatSystemSurface::HasCursorPosFunctions(void) = 0;
	virtual void* CMatSystemSurface::SurfaceGetCursorPos(int &,int &) = 0;
	virtual void* CMatSystemSurface::SurfaceSetCursorPos(int,int) = 0;
	virtual void* CMatSystemSurface::DrawTexturedLine(/* vgui::Vertex_t  const&,vgui::Vertex_t  const& */) = 0;
	virtual void* CMatSystemSurface::DrawOutlinedCircle(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawTexturedPolyLine(/* vgui::Vertex_t  const* */,int) = 0;
	virtual void* CMatSystemSurface::DrawTexturedSubRect(int,int,int,int,float,float,float,float) = 0;
	virtual void* CMatSystemSurface::DrawTexturedPolygon(int /*,vgui::Vertex_t * */ ,bool) = 0;
	virtual void* CMatSystemSurface::GetTitle(uint) = 0;
	virtual void* CMatSystemSurface::IsCursorLocked(void) = 0;
	virtual void* CMatSystemSurface::SetWorkspaceInsets(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawGetUnicodeCharRenderInfo(wchar_t, /* vgui::CharRenderInfo & */ ) = 0;
	virtual void* CMatSystemSurface::DrawRenderCharFromInfo(/* vgui::CharRenderInfo  const& */) = 0;
	virtual void* CMatSystemSurface::DrawSetAlphaMultiplier(float) = 0;
	virtual void* CMatSystemSurface::DrawGetAlphaMultiplier(void) = 0;
	virtual void* CMatSystemSurface::SetAllowHTMLJavaScript(bool) = 0;
	virtual void* CMatSystemSurface::OnScreenSizeChanged(int,int) = 0;
	virtual void* CMatSystemSurface::CreateCursorFromFile(char  const*,char  const*) = 0;
	virtual void* CMatSystemSurface::DrawGetTextureMatInfoFactory(int) = 0;
	virtual void* CMatSystemSurface::PaintTraverseEx(uint,bool) = 0;
	virtual void* CMatSystemSurface::GetZPos(void) = 0;
	virtual void* CMatSystemSurface::SetPanelForInput(uint) = 0;
	virtual void* CMatSystemSurface::DrawFilledRectFastFade(int,int,int,int,int,int,uint,uint,bool) = 0;
	virtual void* CMatSystemSurface::DrawFilledRectFade(int,int,int,int,uint,uint,bool) = 0;
	virtual void* CMatSystemSurface::DrawSetTextureRGBAEx(int,uchar  const*,int,int,ImageFormat) = 0;
	virtual void* CMatSystemSurface::DrawSetTextScale(float,float) = 0;
	virtual void* CMatSystemSurface::SetBitmapFontGlyphSet(ulong,char  const*,float,float,int) = 0;
	virtual void* CMatSystemSurface::AddBitmapFontFile(char  const*) = 0;
	virtual void* CMatSystemSurface::SetBitmapFontName(char  const*,char  const*) = 0;
	virtual void* CMatSystemSurface::GetBitmapFontName(char  const*) = 0;
	virtual void* CMatSystemSurface::ClearTemporaryFontCache(void) = 0;
	virtual void* CMatSystemSurface::GetIconImageForFullPath(char  const*) = 0;
	virtual void* CMatSystemSurface::DrawUnicodeString(wchar_t  const*, ulong) = 0;
	virtual void* CMatSystemSurface::PrecacheFontCharacters(ulong,wchar_t  const*) = 0;
	virtual void* CMatSystemSurface::GetResolutionKey(void) = 0;
	virtual void* CMatSystemSurface::GetFontName(ulong) = 0;
	virtual void* CMatSystemSurface::GetFontFamilyName(ulong) = 0;
	virtual void* CMatSystemSurface::GetKernedCharWidth(ulong,wchar_t,wchar_t,wchar_t,float &,float &) = 0;
	virtual void* CMatSystemSurface::ForceScreenSizeOverride(bool,int,int) = 0;
	virtual void* CMatSystemSurface::ForceScreenPosOffset(bool,int,int) = 0;
	virtual void* CMatSystemSurface::OffsetAbsPos(int &,int &) = 0;
	virtual void* CMatSystemSurface::ResetFontCaches(void) = 0;
	virtual void* CMatSystemSurface::GetTextureNumFrames(int) = 0;
	virtual void* CMatSystemSurface::DrawSetTextureFrame(int,int,uint *) = 0;
	virtual void* CMatSystemSurface::IsScreenSizeOverrideActive(void) = 0;
	virtual void* CMatSystemSurface::IsScreenPosOverrideActive(void) = 0;
	virtual void* CMatSystemSurface::DestroyTextureID(int) = 0;
	virtual void* CMatSystemSurface::DrawUpdateRegionTextureRGBA(int,int,int,uchar  const*,int,int,ImageFormat) = 0;
	virtual void* CMatSystemSurface::BHTMLWindowNeedsPaint(/* vgui::IHTML * */) = 0;
	virtual void* CMatSystemSurface::GetWebkitHTMLUserAgentString(void) = 0;
	virtual void* CMatSystemSurface::AccessChromeHTMLController(void) = 0;
	virtual void* CMatSystemSurface::SetFullscreenViewport(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::GetFullscreenViewport(int &,int &,int &,int &) = 0;
	virtual void* CMatSystemSurface::PushFullscreenViewport(void) = 0;
	virtual void* CMatSystemSurface::PopFullscreenViewport(void) = 0;
	virtual void* CMatSystemSurface::SetSoftwareCursor(bool) = 0;
	virtual void* CMatSystemSurface::PaintSoftwareCursor(void) = 0;
	virtual void* CMatSystemSurface::AttachToWindow(void *,bool) = 0;
	virtual void* CMatSystemSurface::EnableWindowsMessages(bool) = 0;
	virtual void* CMatSystemSurface::Begin3DPaint(int,int,int,int,bool) = 0;
	virtual void* CMatSystemSurface::End3DPaint(void) = 0;
	virtual void* CMatSystemSurface::DisableClipping(bool) = 0;
	virtual void* CMatSystemSurface::GetClippingRect(int &,int &,int &,int &,bool &) = 0;
	virtual void* CMatSystemSurface::SetClippingRect(int,int,int,int) = 0;
	virtual void* CMatSystemSurface::SetMouseCallbacks(void (*)(int &,int &),void (*)(int,int)) = 0;
	virtual void* CMatSystemSurface::InstallPlaySoundFunc(void (*)(char  const*)) = 0;
	virtual void* CMatSystemSurface::DrawColoredCircle(int,int,float,int,int,int,int) = 0;
	virtual void* CMatSystemSurface::DrawColoredText(ulong,int,int,int,int,int,int,char  const*,...) = 0;
	virtual void* CMatSystemSurface::DrawColoredTextRect(ulong,int,int,int,int,int,int,int,int,char  const*,...) = 0;
	virtual void* CMatSystemSurface::DrawTextHeight(ulong,int,int &,char  const*,...) = 0;
	virtual void* CMatSystemSurface::DrawTextLen(ulong,char  const*,...) = 0;
	virtual void* CMatSystemSurface::DrawPanelIn3DSpace(uint,VMatrix  const&,int,int,float,float) = 0;
	virtual void* CMatSystemSurface::DrawSetTextureMaterial(int,IMaterial *) = 0;
	virtual void* CMatSystemSurface::HandleInputEvent(InputEvent_t  const&) = 0;
	virtual void* CMatSystemSurface::Set3DPaintTempRenderTarget(char  const*) = 0;
	virtual void* CMatSystemSurface::Reset3DPaintTempRenderTarget(void) = 0;
	virtual void* CMatSystemSurface::DrawGetTextureMaterial(int) = 0;
};
#endif