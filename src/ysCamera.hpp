#pragma once

#include "ysGraphicsDefine.hpp"

namespace YS::Graphics
{
    class Camera
    {
    public:
        Camera() = delete;
        Camera(Camera const &) = delete;
        Camera(Camera &&) = delete;
        ~Camera() = delete;
        Camera& operator=(Camera const &) = delete;
        Camera& operator=(Camera &&) = delete;

        Camera(Rect vp, Float near, Float far);

    private:
        Rect m_vp;
        Float m_near, m_far;
    };
}