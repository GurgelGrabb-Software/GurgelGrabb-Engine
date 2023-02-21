#pragma once

namespace gg
{
    class CVertexBuffer
    {
        public:
            CVertexBuffer();
            ~CVertexBuffer();

            unsigned GetHandle() const { return _handle; };

            void Bind();
        private:

        unsigned _handle;
    };
}