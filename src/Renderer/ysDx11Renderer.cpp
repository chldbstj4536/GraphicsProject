#include "ysRenderer.hpp"
#include <d3d11.h>
#include <wrl.h>

using namespace YS::Graphics;

Renderer::Dx11Renderer::Dx11Renderer(std::shared_ptr<Window> pWindow) : Renderer(pWindow) { }

std::shared_ptr<Renderer::Dx11Renderer> Renderer::Dx11Renderer::Create(std::shared_ptr<Window> pWindow)
{
    auto pRenderer = std::make_shared<Renderer::Dx11Renderer>(pWindow);

    HRESULT hr = D3D11CreateDevice(
        nullptr,                    // 생성할 장치를 나타내는 디스플레이 어댑터 지정. (null or 0이면 기본 디스플레이 어댑터 사용)
        D3D_DRIVER_TYPE_HARDWARE,   // 드라이버 타입 설정, 일반적으로 하드웨어 가속을 위해 D3D_DRIVER_TYPE_HARDWARE 지정
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        pRenderer->m_pDevice.GetAddressOf(),
        &pRenderer->m_level,
        pRenderer->m_pDC.GetAddressOf()
        );

    if (FAILED(hr)) throw create_failed();

    return pRenderer;
}
