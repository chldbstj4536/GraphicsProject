#pragma once

#include <iostream>
#include <random>
#include "ysRenderer.h"
#include "ysWindow.h"

using namespace YS::Graphics;

int main()
{
    HWND hWndConsole = GetConsoleWindow();

    std::shared_ptr<Window> pWin = Window::Create(Rect{ 100, 100, 800, 600 }, TEXT("Learn to Program Windows"), Window::WindowStyle::Full_Borderless);
    std::shared_ptr<SwRenderer> pSwRenderer = SwRenderer::Create(pWin);

    while (!pWin->IsClosed())
    {
        pSwRenderer->SetClearColor(Color(1.0f, 1.0f, 0.0f, 1.0f));
        pSwRenderer->Clear();
        pSwRenderer->Swap();
    }

    pSwRenderer.reset();
    pWin.reset();

    return 0;
}