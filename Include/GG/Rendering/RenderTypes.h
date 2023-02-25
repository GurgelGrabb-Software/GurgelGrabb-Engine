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
        None,
    };

    enum class EPrimitiveType
    {
        Triangles,
        TriangleFan,
        TriangleStrip,

        Lines,
        LineStrip,
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

    enum class ETextureFormat
    {
        R,
        RG,
        RGB,
        RGBA
    };

    inline constexpr unsigned GetNumOfElements(EAttributeType type) 
    {
        switch (type)
        {
            case EAttributeType::Position: return sizeof(SFloat3) / sizeof(float); break;
            case EAttributeType::Color: return sizeof(SFloat4) / sizeof(float); break;
            default: return 0; break;
        }
    }

    inline constexpr unsigned GetByteSize(EAttributeType type)
    {
        return GetNumOfElements(type) * sizeof(float);
    }

    inline constexpr bool HasFlag(int flags, int flag)
    {
        return (flags & flag) != 0;
    }

    unsigned ConvertToGLType(EVertexAccessMode mode);
    unsigned ConvertToGLType(EPrimitiveType type);
    unsigned ConvertToGLType(EShaderType type);
}