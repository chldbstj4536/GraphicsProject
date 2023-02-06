#include "ysRenderer.hpp"
#include "../ysWindow.hpp"
#include "../ysTexture2D.hpp"
#include <functional>

using namespace YS::Graphics;

Renderer::Renderer(std::shared_ptr<Window> pWindow)
    : m_pWindow(pWindow)
    , m_vp{ pWindow->GetPosX(), pWindow->GetPosY(), pWindow->GetWidth(), pWindow->GetHeight() }
{}

std::shared_ptr<Renderer> Renderer::Create(RendererType rt, std::shared_ptr<Window> pWindow)
{
    std::shared_ptr<Renderer> pResult;
    switch (rt)
    {
    case RendererType::Software:
        pResult = std::static_pointer_cast<Renderer>(SwRenderer::Create(pWindow));
        break;
    case RendererType::DirextX11:
#ifdef _DX11
        pResult = std::static_pointer_cast<Renderer>(Dx11Renderer::Create(pWindow));
#else
        throw not_supported();
#endif
        break;
    case RendererType::DirectX12:
#ifdef _DX12
        pResult = std::static_pointer_cast<Renderer>(Dx12Renderer::Create(pWindow));
#else
        throw not_supported();
#endif
        break;
    case RendererType::OpenGL:
#ifdef _GL
        pResult = std::static_pointer_cast<Renderer>(GlRenderer::Create(pWindow));
#else
        throw not_supported();
#endif
        break;
    }
    return pResult;
}
