#include "GG/Rendering/Window.h"
#include <SDL.h>

void gg::CWindow::Create(unsigned w, unsigned h, const char* t)
{
    SDL_Window* windowPtr = SDL_CreateWindow( t, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN );
    SDL_Renderer* rendererPtr = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED);

    _backendWinPtr = windowPtr;
    _backendRendererPtr = rendererPtr;
}

void gg::CWindow::Clear()
{
    SDL_RenderClear((SDL_Renderer*)_backendRendererPtr);
}

void gg::CWindow::Present()
{
    SDL_RenderPresent((SDL_Renderer*)_backendRendererPtr);
}