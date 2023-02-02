#pragma once

#include <memory>
#include <ysUtility.h>
#include "ysGraphicsDefine.h"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace YS::Graphics
{
    class Window;
    class Renderer : public enable_shared_from_base<Renderer>
    {
    public:
        Renderer() = delete;
        Renderer(Renderer const&) = delete;
        Renderer(Renderer&&) = default;
        virtual ~Renderer() = default;
        Renderer& operator=(Renderer const&) = delete;
        Renderer& operator=(Renderer&&) = default;
    protected:
        Renderer(std::shared_ptr<Window> window);

    public:
        virtual void Clear() = 0;
        virtual void Swap() = 0;

        void SetViewport(Viewport const &r) { m_vp = r; }
        Viewport GetViewport() const { return m_vp; }

        std::weak_ptr<Window> GetWindow() { return m_pWindow; }
        std::weak_ptr<const Window> GetWindow() const { return m_pWindow; }
        void SetClearColor(Color const &clearColor) { m_clearColor = clearColor; }
        Color GetClearColor() const { return m_clearColor; }

    private:
        std::shared_ptr<Window> m_pWindow;
        Viewport m_vp;
        Color m_clearColor = 0xffffffff;
    };

    class SwTexture2D;
    class SwRenderer : public Renderer
    {
    public:
        SwRenderer() = delete;
        SwRenderer(SwRenderer const&) = delete;
        SwRenderer(SwRenderer&&) = default;
        virtual ~SwRenderer() = default;
        SwRenderer& operator=(SwRenderer const&) = delete;
        SwRenderer& operator=(SwRenderer&&) = default;
    private:
        SwRenderer(std::shared_ptr<Window> window);

    public:
        static std::shared_ptr<SwRenderer> Create(std::shared_ptr<Window> window);

        virtual void Clear() override;
        virtual void Swap() override;

    private:
#ifdef _WIN32
        void Draw(HDC hdc);
#endif
        std::shared_ptr<SwTexture2D> m_pRT[2];

        ENABLE_MAKE_SHARED_DECL
    };
    ENABLE_MAKE_SHARED(SwRenderer)
}