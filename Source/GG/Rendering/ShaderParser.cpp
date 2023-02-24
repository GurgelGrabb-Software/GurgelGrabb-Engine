#include "GG/Rendering/ShaderParser.h"

#include <fstream>
#include <iostream>

using namespace gg;

CShaderParser::CShaderParser()
{

}

CShaderParser::~CShaderParser()
{

}

void CShaderParser::ParseFromFile(const std::filesystem::path& filepath)
{
    std::ifstream f(filepath);
    std::stringstream ss;
    ss << f.rdbuf();
    ParseFromStream(ss);
}

void CShaderParser::ParseFromString(const std::string& source)
{
    std::stringstream ss;
    ss.str(source);
    ParseFromStream(ss);
}

void CShaderParser::ParseFromStream(std::stringstream& source)
{
    EShaderType currentType = EShaderType::None;
    std::string currentShader;
    std::string currentName;

    std::string line;
    while (std::getline(source, line))
    {
        if (line.empty())
            continue;
        
        if (line.front() == '#')
        {
            if (line.find("#BEGIN") != std::string::npos)
            {
                assert(currentType == EShaderType::None);

                auto namePos = line.find("SHADER ");
                currentName = line.substr(namePos + 7);

                if (line.find("VERTEX") != std::string::npos)
                {
                    currentType = EShaderType::Vertex;
                }
                else if (line.find("PIXEL") != std::string::npos)
                {
                    currentType = EShaderType::Pixel;
                }
                continue;
            }
            else if (line.find("#END") != std::string::npos)
            {
                assert(currentType != EShaderType::None);

                shaders[currentName] = currentShader;

                auto type = currentType == EShaderType::Vertex ? "Vertex" : "Pixel";
                std::cout << "ShaderParser: Found " << type << "Shader with name: " << currentName << std::endl;

                currentType = EShaderType::None;
                currentName.clear();
                currentShader.clear();
                continue;
            }
        }

        currentShader.append(line);
        currentShader.push_back('\n');
    }
}

const std::string& CShaderParser::GetShaderSource(const std::string& name) const
{
    auto shaderIt = shaders.find(name);
    if (shaderIt != shaders.end())
    {
        return shaderIt->second;
    }
    else
    {
        assert(false);
        return std::string();
    }
}
