#pragma once

#include "GG/Rendering/RenderTypes.h"

namespace gg
{
    class CTexture
    {
    public:

        CTexture(class CImage& image);

        unsigned GetHandle() const { return _handle; };
        void Bind() const;

        void GenerateMipmap();
        void SetSamplerModeMin(ESamplerMode mode);
        void SetSamplerModeMag(ESamplerMode mode);

    private:
        unsigned _handle;
    };
}