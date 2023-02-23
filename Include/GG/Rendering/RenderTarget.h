#pragma once

namespace gg
{
    class IRenderTarget
    {
    public:
        virtual void Draw(const class CVertexBuffer&, const class CShaderProgram&) = 0;
    };
}