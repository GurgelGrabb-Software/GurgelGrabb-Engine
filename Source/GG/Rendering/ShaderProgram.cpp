#include "GG/Rendering/ShaderProgram.h"

#include "GG/Rendering/Shader.h"

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

void CShaderProgram::SetUniform(const char* uniform, const gg::CMat4x4& matrix)
{
    int location = glGetUniformLocation(_handle, uniform);
    glUniformMatrix4fv(location, 1, false, matrix.GetData());
}