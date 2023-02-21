#include "GG/Rendering/VertexBuffer.h"

#include "GG/Rendering/RenderTypes.h"

#include <GLFW/glfw3.h>

using namespace gg;

CVertexBuffer::CVertexBuffer()
{
    glGenBuffers(1, &_handle);

    SVertex v[3] = {
        {.x=0.0f, .y=0.0f},
        {.x=0.5f, .y=1.0f},
        {.x=1.0f, .y=0.0f},
    };

    Bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * 3, v, GL_STATIC_DRAW);
}

CVertexBuffer::~CVertexBuffer()
{
    glDeleteBuffers(1, &_handle);
}

void CVertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _handle);
}