#pragma once

#include "GG/Core/Math/Mat4x4.h"

#include "GG/Rendering/RenderTypes.h"

namespace gg
{
    class CShader;
    class CTexture;

    class CShaderProgram
    {
        public:
        CShaderProgram(const CShader& vertexShader, const CShader& pixelShader);
        ~CShaderProgram();

        unsigned GetHandle() const { return _handle; };

        void Bind() const;

        void SetUniform(const char* uniform, const CTexture& v, unsigned unit = 0);
        void SetUniform(const char* uniform, const gg::CMat4x4& v);
        void SetUniform(const char* uniform, const SFloat4& v);
        void SetUniform(const char* uniform, const SFloat3& v);
        void SetUniform(const char* uniform, const SFloat2& v);
        void SetUniform(const char* uniform, float v);

        private:

        unsigned _handle;
    };
}