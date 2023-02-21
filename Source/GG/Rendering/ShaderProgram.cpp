#include "GG/Rendering/ShaderProgram.h"

#include "GG/Rendering/Shader.h"

#include "GG/Rendering/GLInclude.h"

using namespace gg;

CShaderProgram::CShaderProgram(const CShader& vertexShader, const CShader& pixelShader)
{
    _handle = glCreateProgram();
    glAttachShader(_handle, vertexShader.GetHandle());
    glAttachShader(_handle, pixelShader.GetHandle());
    glLinkProgram(_handle);
}

CShaderProgram::~CShaderProgram()
{
    glDeleteProgram(_handle);
}

void CShaderProgram::Bind()
{
    glUseProgram(_handle);
}