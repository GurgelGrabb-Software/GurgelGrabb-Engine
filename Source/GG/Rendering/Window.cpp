#include "GG/Rendering/Window.h"

#include "GG/Rendering/GLInclude.h"

#define WIN_PTR (GLFWwindow*)_backendWinPtr

bool gg::CWindow::IsOpen() const
{
    return not glfwWindowShouldClose(WIN_PTR);
}

void gg::CWindow::Create(unsigned w, unsigned h, const char* t)
{
    glfwInit();
    _backendWinPtr = glfwCreateWindow( w, h, t, NULL, NULL );
    glfwMakeContextCurrent(WIN_PTR);

    gladLoadGL( glfwGetProcAddress );
}

void gg::CWindow::Destroy()
{
    glfwDestroyWindow(WIN_PTR);
}

void gg::CWindow::Clear()
{
    
}

void gg::CWindow::PollEvents()
{
    glfwPollEvents();
}

void gg::CWindow::Present()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int w, h;
    glfwGetFramebufferSize( WIN_PTR, &w, &h );

    glViewport(0, 0, w, h);

    glfwSwapBuffers(WIN_PTR);
}