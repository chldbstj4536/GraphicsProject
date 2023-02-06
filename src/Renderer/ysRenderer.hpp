#pragma once

#include <memory>
#include <ysUtility.hpp>
#include "ysGraphicsDefine.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace YS::Graphics
{
    enum class RendererType { Software, DirextX11, DirectX12, OpenGL };
    class Window;
    class Renderer
    {
    public:
        Renderer() = delete;
        Renderer(Renderer const&) = delete;
        Renderer(Renderer&&) = delete;
        virtual ~Renderer() = default;
        Renderer& operator=(Renderer const&) = delete;
        Renderer& operator=(Renderer&&) = delete;
    protected:
        Renderer::Renderer(std::shared_ptr<Window> pWindow)
            : m_pWindow(pWindow)
            , m_vp{ pWindow->GetPosX(), pWindow->GetPosY(), pWindow->GetWidth(), pWindow->GetHeight() }
        {}

    public:
        static std::shared_ptr<Renderer> Create(RendererType rt, std::shared_ptr<Window> pWindow)
        {
            std::shared_ptr<Renderer> pResult;
            switch (rt)
            {
            case RendererType::Software:    pResult = SwRenderer::Create(pWindow); break;
            case RendererType::DirextX11:   pResult = Dx11Renderer::Create(pWindow); break;
            case RendererType::DirectX12:   pResult = Dx12Renderer::Create(pWindow); break;
            case RendererType::OpenGL:      pResult = GlRenderer::Create(pWindow); break;
            }
            return pResult;
        }

        virtual void Clear() = 0;
        virtual void Swap() = 0;
        virtual void Draw() = 0;

        virtual void SetViewport(Viewport const &r) { m_vp = r; }
        Viewport GetViewport() const { return m_vp; }

        std::weak_ptr<Window> GetWindow() { return m_pWindow; }
        std::weak_ptr<const Window> GetWindow() const { return m_pWindow; }
        virtual void SetClearColor(Color const &clearColor) { m_clearColor = clearColor; }
        Color GetClearColor() const { return m_clearColor; }

    private:
        std::shared_ptr<Window> m_pWindow;
        Viewport m_vp;
        Color m_clearColor = 0xffffffff;

        class SwRenderer;
        class Dx11Renderer;
        class Dx12Renderer;
        class GlRenderer;
    };

    class SwTexture2D;
    class Renderer::SwRenderer : public Renderer
    {
    public:
        SwRenderer() = delete;
        SwRenderer(SwRenderer const&) = delete;
        SwRenderer(SwRenderer&&) = delete;
        virtual ~SwRenderer() = default;
        SwRenderer& operator=(SwRenderer const&) = delete;
        SwRenderer& operator=(SwRenderer&&) = delete;

        SwRenderer(std::shared_ptr<Window> window);

        static std::shared_ptr<Renderer> Create(std::shared_ptr<Window> window);

        virtual void Clear() override;
        virtual void Draw() override;
        virtual void Swap() override;

        virtual void SetViewport(Viewport const &r) override;
        virtual void SetClearColor(Color const &clearColor) override;

    private:
#ifdef _WIN32
        void Draw(HDC hdc);
#endif
        std::shared_ptr<SwTexture2D> m_pRT[2];

        ENABLE_MAKE_SHARED_DECL;
    };
    ENABLE_MAKE_SHARED(Renderer::SwRenderer);

    class DxTexture2D;
    class Renderer::Dx11Renderer : public Renderer
    {
    public:
        Dx11Renderer() = delete;
        Dx11Renderer(Dx11Renderer const&) = delete;
        Dx11Renderer(Dx11Renderer&&) = delete;
        virtual ~Dx11Renderer() = default;
        Dx11Renderer& operator=(Dx11Renderer const&) = delete;
        Dx11Renderer& operator=(Dx11Renderer&&) = delete;

        Dx11Renderer(std::shared_ptr<Window> window);

        static std::shared_ptr<Renderer> Create(std::shared_ptr<Window> window);

        virtual void Clear() override;
        virtual void Swap() override;
        virtual void Draw() override;

        virtual void SetViewport(Viewport const &r) override;
        virtual void SetClearColor(Color const &clearColor) override;
    };

    class Renderer::Dx12Renderer : public Renderer
    {
    public:
        Dx12Renderer() = delete;
        Dx12Renderer(Dx12Renderer const&) = delete;
        Dx12Renderer(Dx12Renderer&&) = delete;
        virtual ~Dx12Renderer() = default;
        Dx12Renderer& operator=(Dx12Renderer const&) = delete;
        Dx12Renderer& operator=(Dx12Renderer&&) = delete;
        
        Dx12Renderer(std::shared_ptr<Window> window);

        static std::shared_ptr<Renderer> Create(std::shared_ptr<Window> window);

        virtual void Clear() override;
        virtual void Swap() override;
        virtual void Draw() override;

        virtual void SetViewport(Viewport const &r) override;
        virtual void SetClearColor(Color const &clearColor) override;

    };
    class Renderer::GlRenderer : public Renderer
    {
    public:
        GlRenderer() = delete;
        GlRenderer(GlRenderer const&) = delete;
        GlRenderer(GlRenderer&&) = delete;
        virtual ~GlRenderer() = default;
        GlRenderer& operator=(GlRenderer const&) = delete;
        GlRenderer& operator=(GlRenderer&&) = delete;

        GlRenderer(std::shared_ptr<Window> window);

        static std::shared_ptr<Renderer> Create(std::shared_ptr<Window> window);

        virtual void Clear() override;
        virtual void Swap() override;
        virtual void Draw() override;

        virtual void SetViewport(Viewport const& r) override;
        virtual void SetClearColor(Color const& clearColor) override;
    };
}