#pragma once

namespace gg
{
    struct SVertex
    {
        float x, y, z;
    };

    struct SColor
    {
        float r, g, b, a;
    };

    enum class EShaderType
    {
        Vertex,
        Pixel,
        Count,
    };
}