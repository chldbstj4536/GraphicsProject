#pragma once

#include <memory>
#include <thread>
#include <ysEvent.h>
#include <ysUtility.h>
#include "ysGraphicsDefine.h"

#ifdef _WIN32
#include <Windows.h>
#endif

namespace YS::Graphics
{
    class Window
    {
        enum class State { InInit, Success, Fail };
    public:
        enum class WindowStyle { Fullscreen, Full_Borderless, Borderless, Normal};
/// @cond
        Window() = delete;
        Window(Window const&) = delete;
        Window(Window &&) = default;
        ~Window();
        Window& operator=(Window const&) = delete;
        Window& operator=(Window &&) = default;
/// @endcond
    private:
        Window(Rect rect, StringView name);

    public:
        /**
         * @brief 윈도우의 위치와 크기, 이름을 입력받고 이를 기반으로 윈도우를 생성하는 함수
         * 
         * @param rect 생성할 윈도우의 위치와 크기
         * @param name 생성할 윈도우의 이름
         * @return 생성된 윈도우
         * @throw YS::create_failed 윈도우 생성 실패시 예외 발생
         */
        static std::shared_ptr<Window> Create(Rect rect, StringView name, WindowStyle ws);
        void Resize(UInt width, UInt height);
        void Move(Int x, Int y);
        void Swap();

        String GetName() const { return m_name; }
        void SetName(StringView name);
        UInt GetWidth() const { return m_rect.width; }
        UInt GetHeight() const { return m_rect.height; }
        Int GetPosX() const { return m_rect.x; }
        Int GetPosY() const { return m_rect.y; }
        bool IsClosed() const { return m_hWnd == nullptr; }

#ifdef _WIN32
        HWND GetHWnd() const { return m_hWnd; }
#endif

    private:
#ifdef _WIN32
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, UInt windowCnt);

        // 윈도우 메시지 처리를 위한 전역 멤버 함수
        static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#endif

        String m_name;
        Rect m_rect;
        State m_state = State::InInit;
        bool m_isSwap = false;
        std::thread m_msgThread;

#ifdef _WIN32
        HWND m_hWnd = nullptr;
#endif

    public:
        Event<void(UInt, UInt)> OnResize;
        Event<void(Int, Int)> OnMove;
#ifdef _WIN32
        Event<void(HDC)> OnDraw;
#endif
        ENABLE_MAKE_SHARED_DECL
    };
    ENABLE_MAKE_SHARED(Window)
}
