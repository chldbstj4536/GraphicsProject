#include "ysRenderer.h"
#include "ysWindow.h"
#include "ysTexture2D.h"
#include <functional>

using namespace YS::Graphics;

Renderer::Renderer(std::shared_ptr<Window> window)
    : m_pWindow(window)
    , m_vp{ window->GetPosX(), window->GetPosY(), window->GetWidth(), window->GetHeight() }
{}
SwRenderer::SwRenderer(std::shared_ptr<Window> window) : Renderer(window)
{
    m_pRT[0] = std::make_shared<SwTexture2D>(window->GetWidth(), window->GetHeight());
    m_pRT[1] = std::make_shared<SwTexture2D>(window->GetWidth(), window->GetHeight());
}

std::shared_ptr<SwRenderer> SwRenderer::Create(std::shared_ptr<Window> window)
{
    std::shared_ptr<SwRenderer> pSwRenderer = std::make_shared<enable_make_shared>(window);

    window->OnDraw.AddListener(pSwRenderer, &SwRenderer::Draw);

    return pSwRenderer;
}

void SwRenderer::Clear()
{
#ifdef _WIN32
    for (UInt i = 0; i < GetViewport().width; ++i)
        for (UInt j = 0; j < GetViewport().height; ++j)
            m_pRT[0]->SetPixel(i, j, GetClearColor().ConvertToARGB());
#endif
}
void SwRenderer::Swap()
{
    std::swap(m_pRT[0], m_pRT[1]);
    GetWindow().lock()->Swap();
}

#ifdef _WIN32
void SwRenderer::Draw(HDC hdc)
{
    BitBlt(hdc, 0, 0, GetViewport().width, GetViewport().height, m_pRT[1]->GetHDC(), 0, 0, SRCCOPY);
}
#endif