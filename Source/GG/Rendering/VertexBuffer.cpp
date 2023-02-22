#include "GG/Rendering/VertexBuffer.h"

#include "GG/Rendering/RenderTypes.h"

#include "GG/Rendering/GLInclude.h"

using namespace gg;

CVertexBuffer::CVertexBuffer()
{
    glGenBuffers(1, &_handle);

    SVertex v[3] = {
        {.position={.x=0.0f, .y=0.0f}},
        {.position={.x=0.5f, .y=1.0f}},
        {.position={.x=1.0f, .y=0.0f}},
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