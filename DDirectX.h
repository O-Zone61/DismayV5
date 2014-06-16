#ifndef D3D__
#define D3D__
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>
class DDirectX
{
public:
	DDirectX(HWND hParentWnd);
	~DDirectX(void);
	HRESULT Initialize();
	HRESULT OnRender();
	void OnResize(UINT width, UINT height);

private:
	HRESULT CreateDeviceResources();
	void DiscardDeviceResources();

private:
	HWND					m_hWnd;
	ID2D1Factory*			m_pDirect2dFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	ID2D1SolidColorBrush*	m_pLightSlateGrayBrush;
	ID2D1LinearGradientBrush* m_pLinearGradientBrush;
};
#endif // D3D__