#include "GG/Rendering/VertexBuffer.h"

#include "GG/Rendering/RenderTypes.h"

#include "GG/Rendering/GLInclude.h"

#include <cmath>

using namespace gg;

CVertexBuffer::CVertexBuffer()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    const float PI2 = 3.14159f * 2.f;
    const float s = 0.5f;
    SVertex v[3] = {
        {.position={.x = s*std::cosf(PI2 * 2.f/3.f), .y=s*std::sinf(PI2 * 2.f/3.f)}},
        {.position={.x = s*std::cosf(0.f),           .y=s*std::sinf(0.f)}},
        {.position={.x = s*std::cosf(PI2 * 1.f/3.f), .y=s*std::sinf(PI2 * 1.f/3.f)}},
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(SVertex) * 3, v, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(SVertex), (void*)0);
}

CVertexBuffer::~CVertexBuffer()
{
    glDeleteBuffers(1, &_vao);
}

void CVertexBuffer::Bind() const
{
    glBindVertexArray(_vao);
}