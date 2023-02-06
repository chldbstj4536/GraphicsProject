#pragma once

#include <memory>
#include <vector>
#include "ysGraphicsDefine.hpp"

namespace YS::Graphics
{
    class Buffer
    {
    public:
        Buffer() = default;
        Buffer(Buffer const &) = delete;
        Buffer(Buffer &&) = default;
        virtual ~Buffer() = default;
        Buffer &operator=(Buffer const &) = delete;
        Buffer &operator=(Buffer &&) = default;

    private:
        void* pData;
    };
}