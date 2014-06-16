#include "DDirectX.h"

DDirectX::DDirectX(HWND hParent)
{
	m_hWnd = hParent;
	Initialize();
}

HRESULT DDirectX::Initialize()
{
   return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
}

void DDirectX::OnResize(UINT width, UINT height)
{
    if (m_pRenderTarget)
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
}

HRESULT DDirectX::OnRender()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
		// Draw a grid background.
		int width = static_cast<int>(rtSize.width);
		int height = static_cast<int>(rtSize.height);

		// Draw two rectangles.
		D2D1_RECT_F rectangle1 = D2D1::RectF(
			rtSize.width/2 - 50.0f,
			rtSize.height/2 - 50.0f,
			rtSize.width/2 + 50.0f,
			rtSize.height/2 + 50.0f
			);

		D2D1_RECT_F rectangle2 = D2D1::RectF(
			rtSize.width/2 - 100.0f,
			rtSize.height/2 - 100.0f,
			rtSize.width/2 + 100.0f,
			rtSize.height/2 + 100.0f
			);

		// Draw the outline of a rectangle.
		m_pRenderTarget->FillRectangle(&rectangle2, m_pLinearGradientBrush);

		// Draw a filled rectangle.
		m_pRenderTarget->FillRectangle(&rectangle1, m_pLightSlateGrayBrush);

		hr = m_pRenderTarget->EndDraw();

	}
	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
	return hr;
}

HRESULT DDirectX::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(m_hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = m_pDirect2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hWnd, size), &m_pRenderTarget);

        if (SUCCEEDED(hr))
            hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                &m_pLightSlateGrayBrush);

		ID2D1GradientStopCollection *pGradientStops = NULL;

		D2D1_GRADIENT_STOP gradientStops[2];
		gradientStops[0].color = D2D1::ColorF(D2D1::ColorF::Maroon, 1);
		gradientStops[0].position = 0.0f;
		gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Red, 1);
		gradientStops[1].position = 1.0f;

		hr = m_pRenderTarget->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2,
			D2D1_EXTEND_MODE_CLAMP, &pGradientStops);

		if (SUCCEEDED(hr))
			hr = m_pRenderTarget->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(
				D2D1::Point2F(0, 0), D2D1::Point2F(300, 300)), pGradientStops, &m_pLinearGradientBrush);
    }
    return hr;
}

template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

void DDirectX::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pLightSlateGrayBrush);
    SafeRelease(&m_pLinearGradientBrush);
}
