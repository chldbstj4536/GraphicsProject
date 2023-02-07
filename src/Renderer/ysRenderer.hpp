#pragma once

#include <memory>
#include <ysUtility.hpp>
#include "../ysGraphicsDefine.hpp"

#ifdef _WIN32
    #include <Windows.h>
#define _DX11
    #include <wrl.h>
    class ID3D11Device;
    class ID3D11DeviceContext;
    class IDXGISwapChain1;
#endif

namespace YS::Graphics
{
    enum class RendererType { Software, DirextX11, DirectX12, OpenGL };
    class Window;
    class Camera;
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
        Renderer(std::shared_ptr<Window> pWindow);

    public:
        static std::shared_ptr<Renderer> Create(RendererType rt, std::shared_ptr<Window> pWindow, Viewport const &vp) throw(not_supported);

        virtual void Clear() = 0;
        virtual void Swap() = 0;
        virtual void Draw() = 0;

        virtual void SetViewport(Viewport const &vp) { m_vp = vp; }
        Viewport GetViewport() { return m_vp; }
        virtual void SetCamera(Camera const &r) = 0;

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

        SwRenderer(std::shared_ptr<Window> pWindow);

        static std::shared_ptr<SwRenderer> Create(std::shared_ptr<Window> pWindow, Viewport const &vp);

        virtual void Clear() override;
        virtual void Draw() override;
        virtual void Swap() override;

        virtual void SetViewport(Viewport const& vp);
        virtual void SetCamera(Camera const &r) override;
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

        Dx11Renderer(std::shared_ptr<Window> pWindow);

        static std::shared_ptr<Dx11Renderer> Create(std::shared_ptr<Window> pWindow, Viewport const &vp);

        virtual void Clear() override;
        virtual void Swap() override;
        virtual void Draw() override;

        virtual void SetViewport(Viewport const &vp) override;
        virtual void SetCamera(Camera const &r) override;
        virtual void SetClearColor(Color const &clearColor) override;

    private:
        Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDC;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> m_pSwapChain;
    };

    //class Renderer::Dx12Renderer : public Renderer
    //{
    //public:
    //    Dx12Renderer() = delete;
    //    Dx12Renderer(Dx12Renderer const&) = delete;
    //    Dx12Renderer(Dx12Renderer&&) = delete;
    //    virtual ~Dx12Renderer() = default;
    //    Dx12Renderer& operator=(Dx12Renderer const&) = delete;
    //    Dx12Renderer& operator=(Dx12Renderer&&) = delete;
    //    
    //    Dx12Renderer(std::shared_ptr<Window> window);

    //    static std::shared_ptr<Dx12Renderer> Create(std::shared_ptr<Window> window);

    //    virtual void Clear() override;
    //    virtual void Swap() override;
    //    virtual void Draw() override;

    //    virtual void SetCamera(Camera const &r) override;
    //    virtual void SetClearColor(Color const &clearColor) override;

    //};
    //class Renderer::GlRenderer : public Renderer
    //{
    //public:
    //    GlRenderer() = delete;
    //    GlRenderer(GlRenderer const&) = delete;
    //    GlRenderer(GlRenderer&&) = delete;
    //    virtual ~GlRenderer() = default;
    //    GlRenderer& operator=(GlRenderer const&) = delete;
    //    GlRenderer& operator=(GlRenderer&&) = delete;

    //    GlRenderer(std::shared_ptr<Window> window);

    //    static std::shared_ptr<GlRenderer> Create(std::shared_ptr<Window> window);

    //    virtual void Clear() override;
    //    virtual void Swap() override;
    //    virtual void Draw() override;

    //    virtual void SetCamera(Camera const& r) override;
    //    virtual void SetClearColor(Color const& clearColor) override;
    //};
}