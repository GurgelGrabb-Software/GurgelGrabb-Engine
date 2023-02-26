#include "GG/Rendering/Texture.h"

#include "GG/Rendering/Image.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

using namespace gg;

CTexture::CTexture(CImage& image)
{
    glGenTextures(1, &_handle);
    glBindTexture(GL_TEXTURE_2D, _handle);

    glTexImage2D(GL_TEXTURE_2D, 0, ConvertToGLType(image.GetFormat()), image.GetWidth(), image.GetHeight(), 0, ConvertToGLType(image.GetFormat()), GL_UNSIGNED_BYTE, image.GetData());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    SetSamplerModeMin(ESamplerMode::Nearest);
    SetSamplerModeMag(ESamplerMode::Linear);
}

void CTexture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, _handle);
}

void CTexture::GenerateMipmap()
{
    Bind();
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

void CTexture::SetSamplerModeMin(ESamplerMode mode)
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, ConvertToGLType(mode));
}

void CTexture::SetSamplerModeMag(ESamplerMode mode)
{
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, ConvertToGLType(mode));
}