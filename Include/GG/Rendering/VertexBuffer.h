#pragma once

namespace gg
{
    class CVertexBuffer
    {
        public:
            CVertexBuffer();
            ~CVertexBuffer();

            unsigned GetHandle() const { return _vao; };

            void Bind() const;
        private:

        unsigned _vao;
        unsigned _vbo;
    };
}