#pragma once

#include "GG/Core/Math/Mat4x4.h"

namespace gg
{
    class CShader;

    class CShaderProgram
    {
        public:
        CShaderProgram(const CShader& vertexShader, const CShader& pixelShader);
        ~CShaderProgram();

        unsigned GetHandle() const { return _handle; };

        void Bind() const;

        void SetUniform(const char* uniform, const gg::CMat4x4& matrix);

        private:

        unsigned _handle;
    };
}