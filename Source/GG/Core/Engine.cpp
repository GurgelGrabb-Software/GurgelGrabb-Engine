#include "GG/Core/Engine.h"
#include <GG/Rendering/Window.h>
#include <iostream>

gg::CEngine::CEngine()
{
}

void gg::CEngine::Run()
{
    CWindow window;
    window.Create(800u, 800u, "Hello :D");
    while(window.IsOpen())
    {
        window.Clear();
        window.PollEvents();
        window.Present();
    }
}