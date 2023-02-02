#pragma once

#include <iostream>
#include <random>
#include "ysRenderer.h"
#include "ysWindow.h"

int main()
{
    std::shared_ptr<YS::Graphics::Window> pWin = YS::Graphics::Window::Create(YS::Graphics::Rect{ 100, 100, 800, 600 }, TEXT("Learn to Program Windows"));
    std::shared_ptr<YS::Graphics::SwRenderer> pSwRenderer = YS::Graphics::SwRenderer::Create(pWin);

    HWND hWndConsole = GetConsoleWindow();

    pWin->SetName(TEXT("Change window name"));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<YS::UInt> dis(0, 0xffffffff);

    while (!pWin->IsClosed())
    {
        YS::Graphics::Color color(dis(gen));
        pSwRenderer->SetClearColor(color);
        pSwRenderer->Clear();
        pSwRenderer->Swap();
    }

    pSwRenderer.reset();
    pWin.reset();

    return 0;
}