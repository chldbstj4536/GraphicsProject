// Todo #1: 윈도우 모드 변경 추가 line:114

#include "ysWindow.hpp"
#include "Renderer/ysRenderer.hpp"
#include "ysBuffer.hpp"

using namespace YS::Graphics;

Window::Window(Rect r, StringView name, WindowMode winMode) : m_rect(r), m_name(name), m_winMode(winMode) { }
Window::~Window() { SendMessage(m_hWnd, WM_DESTROY, 0, 0); m_msgThread.join(); }
    
std::shared_ptr<Window> Window::Create(Rect r, StringView name, WindowMode winMode)
{
    std::shared_ptr<Window> pWin = std::make_shared<enable_make_shared>(r, name, winMode);
    pWin->m_msgThread = std::thread(
        [pWin]()
        {
            WNDCLASS wc = { 0 };

        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpszClassName = pWin->m_name.c_str();

        RegisterClass(&wc);

        int winMode = 0;
        int showStyle = SW_SHOWNORMAL;
        switch (pWin->GetWindowMode())
        {
        case WindowMode::Fullscreen:
            winMode |= WS_MAXIMIZE;
            break;
        case WindowMode::Full_Borderless:
            pWin->m_rect.x = pWin->m_rect.y = 0;
            winMode = WS_POPUP;
            showStyle = SW_MAXIMIZE;
            break;
        case WindowMode::Borderless:
            winMode = WS_POPUP;
            break;
        case WindowMode::Normal:
            winMode = WS_OVERLAPPED;
            break;
        }

        pWin->m_hWnd = CreateWindowEx(
            WS_EX_APPWINDOW, pWin->m_name.c_str(), pWin->m_name.c_str(), winMode, pWin->m_rect.x, pWin->m_rect.y,
            pWin->m_rect.width, pWin->m_rect.height, nullptr, nullptr, GetModuleHandle(nullptr), pWin.get()
        );

        if (pWin->m_hWnd == nullptr)
        {
            pWin->m_state = State::Fail;
            return;
        }

        ShowWindow(pWin->m_hWnd, showStyle);
        pWin->m_state = State::Success;

        // Run the message loop.
        MSG msg = {};
        while (!pWin->IsClosed())
        {
            if (PeekMessage(&msg, pWin->m_hWnd, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
                std::this_thread::yield();
        }
    });
    {
        using namespace std;
        while (pWin->m_state == State::InInit) std::this_thread::sleep_for(1ms);
    }
    if (pWin->m_state == State::Fail)
        throw create_failed();

    return pWin;
}

void Window::Resize(UInt width, UInt height)
{
    m_rect.width = width;
    m_rect.height = height;
    ::MoveWindow(m_hWnd, m_rect.x, m_rect.y, m_rect.width, m_rect.height, true);
}
void Window::Move(Int x, Int y)
{
    m_rect.x = x;
    m_rect.y = y;
    ::MoveWindow(m_hWnd, m_rect.x, m_rect.y, m_rect.width, m_rect.height, true);
}
void Window::Swap()
{
    m_isSwap = true;
#ifdef _WIN32
    ::InvalidateRect(m_hWnd, nullptr, true);
    ::UpdateWindow(m_hWnd);
#endif
}

void Window::SetName(StringView name)
{
    m_name = name;
#ifdef _WIN32
    SetWindowText(m_hWnd, m_name.c_str());
#endif
}
void Window::SetWindowMode(WindowMode winMode)
{
    m_winMode = winMode;
    // ToDo #1: 윈도우 모드 변경 해야함
    OnChangedWinMode(winMode);
}


LRESULT Window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, UInt windowCnt)
{
    switch (uMsg)
    {
    // 윈도우가 종료되었는가?
    case WM_DESTROY:
    {
        m_hWnd = nullptr;
        if (windowCnt == 0)
            PostQuitMessage(0);
        return 0;
    }
    // 윈도우 크기가 변경 되었는가?
    case WM_SIZE:
    {
        if (m_rect.width != static_cast<UInt>(LOWORD(lParam)) || m_rect.height != static_cast<UInt>(HIWORD(lParam)))
        {
            m_rect.width = static_cast<UInt>(LOWORD(lParam));
            m_rect.height = static_cast<UInt>(HIWORD(lParam));
            OnResize(m_rect.width, m_rect.height);
        }
        break;
    }
    // 윈도우 위치가 변경 되었는가?
    case WM_MOVE:
    {
        if (m_rect.x != static_cast<Int>(LOWORD(lParam)) || m_rect.y != static_cast<Int>(HIWORD(lParam)))
        {
            m_rect.x = static_cast<Int>(LOWORD(lParam));
            m_rect.y = static_cast<Int>(HIWORD(lParam));
            OnMove(m_rect.x, m_rect.y);
        }
        break;
    }
    case WM_PAINT:
    {
        if (!m_isSwap) return 0;

        m_isSwap = false;
        PAINTSTRUCT ps{};
        HDC hdc = BeginPaint(m_hWnd, &ps);
        OnDraw(hdc);
        EndPaint(m_hWnd, &ps);
        return 0;
    }
    default:
        return DefWindowProc(m_hWnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

/// @brief 전역 함수
LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static UInt windowCnt = 0;

    // 호출된 Window 클래스를 담기 위한 변수
    Window* pThis = nullptr;

    if (uMsg == WM_NCCREATE)
    {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hWnd = hWnd;
        ++windowCnt;
    }
    else
    {
        pThis = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (pThis)
        return pThis->HandleMessage(uMsg, wParam, lParam, windowCnt);
    else
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
}