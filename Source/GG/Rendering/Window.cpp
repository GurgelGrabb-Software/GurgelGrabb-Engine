#include "GG/Rendering/Window.h"

#include "GG/Rendering/GLInclude.h"

#define WIN_PTR (GLFWwindow*)_backendWinPtr

#include "GG/Rendering/VertexBuffer.h"
#include "GG/Rendering/ShaderProgram.h"
#include "GG/Rendering/Shader.h"
#include "GG/Rendering/RenderTypes.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

bool gg::CWindow::IsOpen() const
{
    return not glfwWindowShouldClose(WIN_PTR);
}

void gg::CWindow::Create(unsigned w, unsigned h, const char* t)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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
    glClear(GL_COLOR_BUFFER_BIT);
}

void gg::CWindow::PollEvents()
{
    glfwPollEvents();
}

void gg::CWindow::Present()
{
    glfwSwapBuffers(WIN_PTR);

#ifdef APPLE // Hack for MacOS: nothing gets drawn until window has been altered once.
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;
        int x, y;
        glfwGetWindowPos(WIN_PTR, &x, &y);
        //glfwSetWindowPos(WIN_PTR, x+1, y+1);
    }
#endif
}

glm::i32vec2 gg::CWindow::GetSize() const
{
    glm::i32vec2 size;
    glfwGetWindowSize( WIN_PTR, &size.x, &size.y );
    return size;
}

void gg::CWindow::SetViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

void gg::CWindow::Draw(const gg::CVertexBuffer& vertexBuffer, const CShaderProgram& program)
{
    program.Bind();
    vertexBuffer.Bind();
    glDrawArrays(ConvertToGLType(vertexBuffer.GetPrimitiveType()), 0, vertexBuffer.GetVertexCount());
}