#include "ysTexture2D.h"

using namespace YS::Graphics;

SwTexture2D::SwTexture2D(SwTexture2D const &o) : SwTexture2D(o.GetWidth(), o.GetHeight()) { }
SwTexture2D::~SwTexture2D()
{
    DeleteDC(m_hDC);
    DeleteObject(m_hBmp);
}
SwTexture2D& SwTexture2D::operator=(SwTexture2D const& o)
{
    return *this = SwTexture2D(o);
}
SwTexture2D::SwTexture2D(UInt width, UInt height) : Texture2D(width, height)
{
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = GetWidth();
    bi.bmiHeader.biHeight = GetHeight();
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    // DC에 연결되지 않은 비트맵을 생성
    m_hBmp = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, (void **)&m_pTex, NULL, 0);
    // 출력 장치와는 연결되지 않은 DC를 생성
    m_hDC = CreateCompatibleDC(nullptr);
    // CreateDIBSection()에서 만든 비트맵과 출력 장치와 연결되지 않은 DC를 연결
    SelectObject(m_hDC, m_hBmp);
}