#pragma once

#include "RenderTypes.h"

namespace gg
{
    class CShader
    {
        public:
            CShader(const char* shader, EShaderType type);
            ~CShader();
            
            unsigned GetHandle() const { return _handle; };

            void Bind();

        private:

        EShaderType _type;

        unsigned _handle;
    };
}