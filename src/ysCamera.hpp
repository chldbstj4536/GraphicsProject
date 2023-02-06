#pragma once

#include <ysVector.hpp>

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

        Camera(Math::Vector3 pos);

    private:
        Math::Vector3 pos;
        //Math::Vector4 rot;
    };
}