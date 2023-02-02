#pragma once

#include "ysTexture2D.h"
#include <memory>

namespace YS::Graphics
{
    class Viewport
    {
    public:
        Viewport() = default;
        Viewport(Viewport const &) = default;
        Viewport(Viewport &&) = default;
        ~Viewport() = default;
        Viewport& operator=(Viewport const &) = default;
        Viewport& operator=(Viewport &&) = default;

        Viewport(Rect r);

        void SetRect(Rect r)
        {
            if (m_rect.width != r.width || m_rect.height != r.height)
            {
                // m_tex.swap(std::make_unique<SwTexture2D>(r.width, r.height));
            }

            m_rect = r;
        }

        Rect GetRect() const { return m_rect; }
        UInt GetWidth() { return m_rect.width; }
        UInt GetHeight() { return m_rect.height; }
        Texture2D* GetTexture() { return m_tex.get(); }

    private:
        Rect m_rect;
        std::unique_ptr<Texture2D> m_tex;
    };
}