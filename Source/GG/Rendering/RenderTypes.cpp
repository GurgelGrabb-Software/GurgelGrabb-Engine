#include "GG/Rendering/RenderTypes.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace gg;

unsigned gg::ConvertToGLType(EVertexAccessMode mode)
{
    switch (mode)
    {
    case EVertexAccessMode::Static:
        return GL_STATIC_DRAW;
        break;
    case EVertexAccessMode::Dynamic:
        return GL_DYNAMIC_DRAW;
    default:
        return GL_STATIC_DRAW;
        break;
    }
}

unsigned gg::ConvertToGLType(EPrimitiveType type)
{
    switch (type)
    {
    case EPrimitiveType::Triangles:
        return GL_TRIANGLES;
        break;
    case EPrimitiveType::TriangleFan:
        return GL_TRIANGLE_FAN;
        break;
    case EPrimitiveType::TriangleStrip:
        return GL_TRIANGLE_STRIP;
        break;
    case EPrimitiveType::Lines:
        return GL_LINES;
        break;
    case EPrimitiveType::LineStrip:
        return GL_LINE_STRIP;
        break;
    default:
        return GL_TRIANGLES;
        break;
    }
}

unsigned gg::ConvertToGLType(EShaderType type)
{
    switch (type)
    {
    case EShaderType::Vertex:
        return GL_VERTEX_SHADER;
        break;
    case EShaderType::Pixel:
        return GL_FRAGMENT_SHADER;
    default:
        return 0;
        break;
    }
}

unsigned gg::ConvertToGLType(ETextureFormat format)
{
    switch (format)
    {
    case ETextureFormat::R:
        return GL_R32I;
        break;
    case ETextureFormat::RG:
        return GL_RG;
        break;
    case ETextureFormat::RGB:
        return GL_RGB;
        break;
    case ETextureFormat::RGBA:
        return GL_RGBA;
        break;
    default:
        return GL_RGBA;
        break;
    }
}

unsigned gg::ConvertToGLType(ESamplerMode mode)
{
    switch (mode)
    {
    case ESamplerMode::Linear:
        return GL_LINEAR;
        break;
    case ESamplerMode::Nearest:
        return GL_NEAREST;
        break;
    default:
        return GL_LINEAR;
        break;
    }
}