#include "ysRenderer.hpp"
#include "../ysWindow.hpp"
#include <d3d11_1.h>
#include <dxgi1_2.h>
#include <wrl.h>

using namespace YS::Graphics;

Renderer::Dx11Renderer::Dx11Renderer(std::shared_ptr<Window> pWindow) : Renderer(pWindow) { }

std::shared_ptr<Renderer::Dx11Renderer> Renderer::Dx11Renderer::Create(std::shared_ptr<Window> pWindow, Viewport const &vp)
{
    auto pRenderer = std::make_shared<Renderer::Dx11Renderer>(pWindow);
    D3D_FEATURE_LEVEL level;

    HRESULT hr = D3D11CreateDevice(
        nullptr,                    // 생성할 장치를 나타내는 디스플레이 어댑터 지정. (null or 0이면 기본 디스플레이 어댑터 사용)
        D3D_DRIVER_TYPE_HARDWARE,   // 드라이버 타입 설정, 일반적으로 하드웨어 가속을 위해 D3D_DRIVER_TYPE_HARDWARE 지정
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        pRenderer->m_pDevice.GetAddressOf(),
        &level,
        pRenderer->m_pDC.GetAddressOf()
        );

    if (FAILED(hr)) throw create_failed();

    pRenderer->SetViewport(vp);

    return pRenderer;
}

void Renderer::Dx11Renderer::Clear()
{

}
void Renderer::Dx11Renderer::Swap()
{

}
void Renderer::Dx11Renderer::Draw()
{

}
void Renderer::Dx11Renderer::SetViewport(Viewport const& vp)
{
    Renderer::SetViewport(vp);

    HRESULT hr;

    DXGI_SWAP_CHAIN_DESC1 sd{};
    sd.Width = vp.width;
    sd.Height = vp.height;
    sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.Stereo = false;

    // MSAA를 사용하지 않음
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2;
    sd.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
    sd.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
    sd.AlphaMode = DXGI_ALPHA_MODE::DXGI_ALPHA_MODE_UNSPECIFIED;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    DXGI_SWAP_CHAIN_FULLSCREEN_DESC sfd
    {
        {144, 1},
        DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
        DXGI_MODE_SCALING_UNSPECIFIED,
        GetWindow().lock()->GetWindowMode() == Window::WindowMode::Fullscreen
    };

    Microsoft::WRL::ComPtr<IDXGIDevice> pDxgiDevice;
    Microsoft::WRL::ComPtr<IDXGIAdapter> pDxgiAdapter;
    Microsoft::WRL::ComPtr<IDXGIFactory2> pDxgiFactory;

    hr = m_pDevice.As(&pDxgiDevice);
    if (FAILED(hr)) throw create_failed();
    hr = pDxgiDevice->GetAdapter(pDxgiAdapter.GetAddressOf());
    if (FAILED(hr)) throw create_failed();
    hr = pDxgiAdapter->GetParent(__uuidof(pDxgiFactory), reinterpret_cast<void**>(pDxgiFactory.GetAddressOf()));
    if (FAILED(hr)) throw create_failed();
    hr = pDxgiFactory->CreateSwapChainForHwnd(m_pDevice.Get(), GetWindow().lock()->GetHWnd(), &sd, nullptr, nullptr, m_pSwapChain.GetAddressOf());
    if (FAILED(hr)) throw create_failed();
}
