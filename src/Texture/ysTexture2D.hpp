#pragma once

#include "../ysGraphicsDefine.hpp"
#include "../ysFormat.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace YS::Graphics
{
    class Texture2D
    {
    public:
        enum class Usage { Default, Immutable, Dynamic, Staging };

        Texture2D() = delete;
        Texture2D(Texture2D const &) = delete;
        Texture2D(Texture2D &&) = delete;
        virtual ~Texture2D() = default;
        Texture2D &operator=(Texture2D const &) = delete;
        Texture2D &operator=(Texture2D &&) = delete;

        Texture2D(UInt width, UInt height, UInt MipLv, UInt ArrSize, TextureFormat format, TextureAccess access, ) : m_width(width), m_height(height) {}

        virtual void SetPixel(UInt x, UInt y, UInt32 c) = 0;
        virtual UInt32 GetPixel(UInt x, UInt y) const = 0;
        UInt GetWidth() const { return m_width; }
        UInt GetHeight() const { return m_height; }

    private:
        UInt m_width = 0, m_height = 0;
    };

    class SwTexture2D : public Texture2D
    {
    public:
        SwTexture2D() = default;
        SwTexture2D(SwTexture2D const &);
        SwTexture2D(SwTexture2D &&) = default;
        virtual ~SwTexture2D();
        SwTexture2D &operator=(SwTexture2D const &);
        SwTexture2D &operator=(SwTexture2D &&) = default;

        SwTexture2D(UInt width, UInt height);

        virtual void SetPixel(UInt x, UInt y, UInt32 c) { 
            m_pTex[(y * GetWidth()) + x] = c; }
        //virtual void SetPixel(UInt x, UInt y, UInt32 c) { m_pTex[0] = c; }
        virtual UInt32 GetPixel(UInt x, UInt y) const override { return m_pTex[(y * GetWidth()) + x]; }
        HDC GetHDC() { return m_hDC; }

    private:
        LPDWORD m_pTex = nullptr;
        HBITMAP m_hBmp = nullptr;
        HDC m_hDC = nullptr;
    };
}