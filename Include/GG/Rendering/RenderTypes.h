#pragma once

namespace gg
{
    struct SFloat2
    {
        float x, y;
    };

    struct SFloat3
    {
        float x, y, z;
    };

    struct SFloat4
    {
        float x, y, z, w;
    };

    struct SVertex
    {
        SFloat3 position;
        //SFloat4 color;
        //SFloat2 uv;
    };

    enum class EShaderType
    {
        Vertex,
        Pixel,
        Count,
    };
}