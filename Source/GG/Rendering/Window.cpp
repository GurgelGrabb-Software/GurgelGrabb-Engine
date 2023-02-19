#include "GG/Rendering/Window.h"
#include <SDL.h>

void gg::CWindow::Create(unsigned w, unsigned h, const char* t)
{
    SDL_Window* windowPtr = SDL_CreateWindow( t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0 );
    SDL_Renderer* rendererPtr = SDL_CreateRenderer(windowPtr, "MainRenderer", SDL_RENDERER_ACCELERATED);

    _backendWinPtr = windowPtr;
    _backendRendererPtr = rendererPtr;
}

void gg::CWindow::Clear()
{
    SDL_RenderClear((SDL_Renderer*)_backendRendererPtr);
}

void gg::CWindow::PollEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) 
    {
        if(e.type == SDL_EVENT_QUIT)
            _open = false;
        {
            break;
        }
    }
}

void gg::CWindow::Present()
{
    SDL_RenderPresent((SDL_Renderer*)_backendRendererPtr);
}