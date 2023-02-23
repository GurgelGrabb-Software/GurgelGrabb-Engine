#pragma once

#include "GG/Rendering/RenderTarget.h"

#include <glm/vec2.hpp>

namespace gg
{
    class CWindow : public IRenderTarget
    {
    public:
        bool IsOpen() const;

        void Create( unsigned w, unsigned h, const char* t );
        void Destroy();
        void Clear();
        void PollEvents();
        void Present();
        glm::i32vec2 GetSize() const;

        void SetViewport(int x, int y, int w, int h);

        virtual void Draw(const CVertexBuffer& vertexBuffer, const CShaderProgram& shaderProgram) override;

    private:
        void* _backendWinPtr;
        void* _backendRendererPtr;
        bool  _open = true;
    };
}