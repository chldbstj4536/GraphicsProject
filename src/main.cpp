#pragma once

#include <iostream>
#include <random>
#include "ysWindow.hpp"
#include "Renderer/ysRenderer.hpp"
#include "ysBuffer.hpp"

using namespace YS::Graphics;

struct Vertex { float v[3]; };

int main()
{
    HWND hWndConsole = GetConsoleWindow();

    std::shared_ptr<Window> pWin = Window::Create(Rect{ 100, 100, 800, 600 }, TEXT("Learn to Program Windows"), Window::WindowMode::Full_Borderless);
    std::shared_ptr<Renderer> pSwRenderer = Renderer::Create(RendererType::Software, pWin, {0, 0, 400, 300, 1.0f, 1.0f});

    pSwRenderer->SetClearColor(Color(1.0f, 1.0f, 0.0f, 1.0f));
    while (!pWin->IsClosed())
    {
        pSwRenderer->Clear();

        pSwRenderer->Swap();
    }

    pSwRenderer.reset();
    pWin.reset();

    return 0;
}