#pragma once

namespace gg
{
    class CShader;

    class CShaderProgram
    {
        public:
        CShaderProgram(const CShader& vertexShader, const CShader& pixelShader);
        ~CShaderProgram();

        unsigned GetHandle() const { return _handle; };

        void Bind();

        private:

        unsigned _handle;
    };
}