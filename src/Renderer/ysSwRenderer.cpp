#include "ysRenderer.hpp"
#include "../ysWindow.hpp"
#include "../ysTexture2D.hpp"
#include <functional>

using namespace YS::Graphics;

Renderer::SwRenderer::SwRenderer(std::shared_ptr<Window> pWindow) : Renderer(pWindow)
{
    m_pRT[0] = std::make_shared<SwTexture2D>(pWindow->GetWidth(), pWindow->GetHeight());
    m_pRT[1] = std::make_shared<SwTexture2D>(pWindow->GetWidth(), pWindow->GetHeight());
}

std::shared_ptr<Renderer::SwRenderer> Renderer::SwRenderer::Create(std::shared_ptr<Window> pWindow, Viewport const &vp)
{
    auto pSwRenderer = std::make_shared<Renderer::SwRenderer>(pWindow);

    pWindow->OnDraw.AddListener(pSwRenderer, &SwRenderer::Draw);

    return pSwRenderer;
}

void Renderer::SwRenderer::Clear()
{
#ifdef _WIN32
    for (UInt i = 0; i < GetViewport().width; ++i)
        for (UInt j = 0; j < GetViewport().height; ++j)
            m_pRT[0]->SetPixel(i, j, GetClearColor().ConvertToARGB());
#endif
}
void Renderer::SwRenderer::Draw()
{

}
void Renderer::SwRenderer::Swap()
{
    std::swap(m_pRT[0], m_pRT[1]);
    GetWindow().lock()->Swap();
}
void Renderer::SwRenderer::SetViewport(Viewport const& r)
{
    Renderer::SetViewport(r);

}
void Renderer::SwRenderer::SetClearColor(Color const& clearColor)
{
    Renderer::SetClearColor(clearColor);

}

#ifdef _WIN32
void Renderer::SwRenderer::Draw(HDC hdc)
{
    BitBlt(hdc, 0, 0, GetViewport().width, GetViewport().height, m_pRT[1]->GetHDC(), 0, 0, SRCCOPY);
}
#endif