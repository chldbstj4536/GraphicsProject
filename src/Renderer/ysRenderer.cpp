#include "ysRenderer.hpp"
#include "../ysWindow.hpp"
#include "../ysTexture2D.hpp"
#include <functional>

using namespace YS::Graphics;

Renderer::Renderer(std::shared_ptr<Window> pWindow)
    : m_pWindow{pWindow}
{}

std::shared_ptr<Renderer> Renderer::Create(RendererType rt, std::shared_ptr<Window> pWindow, Viewport const &vp)
{
    std::shared_ptr<Renderer> pResult;
    switch (rt)
    {
    case RendererType::Software:
        pResult = std::static_pointer_cast<Renderer>(SwRenderer::Create(pWindow, vp));
        break;
    case RendererType::DirextX11:
#ifdef _DX11
        pResult = std::static_pointer_cast<Renderer>(Dx11Renderer::Create(pWindow, vp));
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
