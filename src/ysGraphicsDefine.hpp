#pragma once

#include <cmath>
#include <ysDefine.hpp>
#include <algorithm>

namespace YS::Graphics
{
    struct Rect { Int x, y; UInt width, height; };
    struct Viewport
    {
        UInt GetAbsoluteX() { if (-1.0f <= x && x <= 1.0f) return x * width; return static_cast<Int>(x); }
        UInt GetAbsoluteY() { if (-1.0f <= y && y <= 1.0f) return y * height; return static_cast<Int>(y); }

        Float x, y;
        UInt width, height;
        Float near, far;
    };
    struct Color
    {
        Color() = default;
        Color(Color const&) = default;
        Color(Color &&) = default;
        ~Color() = default;
        Color& operator=(Color const&) = default;
        Color& operator=(Color &&) = default;

        Color(float r, float g, float b, float a) : r{ r }, g{ g }, b{ b }, a{ a } {}
        Color(UInt hex)
            : r{ static_cast<float>((0xff & (hex >> 24)) / 255.0f) }
            , g{ static_cast<float>((0xff & (hex >> 16)) / 255.0f) }
            , b{ static_cast<float>((0xff & (hex >> 8)) / 255.0f) }
            , a{ static_cast<float>((0xff & hex) / 255.0f) } {}

        UInt ConvertToRGBA() { return static_cast<UInt>(*this); }
        UInt ConvertToARGB()
        {
            UInt result = 0;
            result = static_cast<UInt>(0xff * std::clamp(a, 0.0f, 1.0f));
            result <<= 8;
            result |= static_cast<UInt>(0xff * std::clamp(r, 0.0f, 1.0f));
            result <<= 8;
            result |= static_cast<UInt>(0xff * std::clamp(g, 0.0f, 1.0f));
            result <<= 8;
            result |= static_cast<UInt>(0xff * std::clamp(b, 0.0f, 1.0f));
            return result;
        }
        operator UInt()
        {
            UInt result = 0;
            result = static_cast<UInt>(0xff * std::clamp(r, 0.0f, 1.0f));
            result <<= 8;
            result |= static_cast<UInt>(0xff * std::clamp(g, 0.0f, 1.0f));
            result <<= 8;
            result |= static_cast<UInt>(0xff * std::clamp(b, 0.0f, 1.0f));
            result <<= 8;
            result |= static_cast<UInt>(0xff * std::clamp(a, 0.0f, 1.0f));
            return result;
        }

        UInt GetHex() { return static_cast<UInt>(*this); }

        Float r, g, b, a;
    };
}