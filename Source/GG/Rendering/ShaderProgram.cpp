#include "GG/Rendering/ShaderProgram.h"

#include "GG/Rendering/Shader.h"
#include "GG/Rendering/Texture.h"

#include "GG/Rendering/GLInclude.h"

#include <iostream>

using namespace gg;

CShaderProgram::CShaderProgram(const CShader& vertexShader, const CShader& pixelShader)
{
    _handle = glCreateProgram();
    glAttachShader(_handle, vertexShader.GetHandle());
    glAttachShader(_handle, pixelShader.GetHandle());
    glLinkProgram(_handle);

    int result;
    glGetProgramiv(_handle, GL_LINK_STATUS, &result);
    if(!result) {
        char log[512];
        glGetProgramInfoLog(_handle, 512, NULL, log);
        std::cout << "ShaderProgram: " << log << std::endl;
    }
}

CShaderProgram::~CShaderProgram()
{
    glDeleteProgram(_handle);
}

void CShaderProgram::Bind() const
{
    glUseProgram(_handle);
}

void CShaderProgram::SetUniform(const char* uniform, const CTexture& v, unsigned unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    v.Bind();

    int location = glGetUniformLocation(_handle, uniform);
    glUniform1i(location, unit);
}

void CShaderProgram::SetUniform(const char* uniform, const gg::CMat4x4& v)
{
    int location = glGetUniformLocation(_handle, uniform);
    glUniformMatrix4fv(location, 1, false, v.GetData());
}

void CShaderProgram::SetUniform(const char* uniform, const gg::SFloat4& v)
{
    int location = glGetUniformLocation(_handle, uniform);
    glUniform4fv(location, 1, &v.x);
}

void CShaderProgram::SetUniform(const char* uniform, const gg::SFloat3& v)
{
    int location = glGetUniformLocation(_handle, uniform);
    glUniform3fv(location, 1, &v.x);
}

void CShaderProgram::SetUniform(const char* uniform, const gg::SFloat2& v)
{
    int location = glGetUniformLocation(_handle, uniform);
    glUniform2fv(location, 1, &v.x);
}

void CShaderProgram::SetUniform(const char* uniform, float v)
{
    int location = glGetUniformLocation(_handle, uniform);
    glUniform1fv(location, 1, &v);
}