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

    enum class EShaderType
    {
        Vertex,
        Pixel,
        Count,
    };

    enum class EVertexAccessMode
    {
        Static,
        Dynamic,
    };

    enum EAttributeType
    {
        Position    = 0x100000,
        Color       = 0x010000,
        UV          = 0x001000,
    };

    enum EVertexFormat
    {
        P3      = Position,
        P3C4    = Position | Color,
        P3C4UV2 = Position | Color | UV,
        P3UV2   = Position | UV,
    };

    inline constexpr unsigned GetSize(EAttributeType type) 
    {
        switch (type)
        {
            case EAttributeType::Position: return sizeof(SFloat3); break;
            case EAttributeType::Color: return sizeof(SFloat4); break;
            default: return 0; break;
        }
    }

    inline constexpr bool HasFlag(int flags, int flag)
    {
        return (flags & flag) != 0;
    }
}