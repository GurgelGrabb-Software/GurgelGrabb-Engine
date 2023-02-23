#include "GG/Rendering/Shader.h"

#include "GG/Rendering/GLInclude.h"
#include "GG/Core/Utility/Logging.h"
#include <iostream>

using namespace gg;

unsigned convertToGLType(EShaderType type)
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

CShader::CShader(const char* shader, EShaderType type) : 
_type(type)
{
    _handle = glCreateShader(convertToGLType(type));
    glShaderSource(_handle, 1, &shader, NULL);
    glCompileShader(_handle);

    int result;
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &result);
    if(!result) {
        char log[512];
        glGetShaderInfoLog(_handle, 512, NULL, log);
        std::cout << "Shader: " << log << std::endl;
    }
}

CShader::~CShader()
{
    glDeleteShader(_handle);
}

void CShader::Bind()
{

}