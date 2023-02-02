#pragma once

#include <memory>
#include "ysGraphicsDefine.h"

#ifdef _WIN32
#include <Windows.h>
#endif


namespace YS::Graphics
{
    template <typename _DataType>
    class Buffer
    {
    public:
        Buffer() = default;
        Buffer(Buffer const &) = default;
        Buffer(Buffer &&) = default;
        virtual ~Buffer() = default;
        Buffer &operator=(Buffer const &) = default;
        Buffer &operator=(Buffer &&) = default;

        virtual bool CreateBuffer(UInt size) { m_pData = std::make_unique<_DataType[]>(size); }
        void SetBufferData(UInt index, _DataType data) { m_pData[index] = data; }
        _DataType &GetBufferData(UInt index) { return m_pData[index]; }

    private:
        UInt m_size;
        std::unique_ptr<_DataType[]> m_pData;
    };
}