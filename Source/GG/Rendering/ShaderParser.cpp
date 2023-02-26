#include "GG/Rendering/ShaderParser.h"

#include <fstream>
#include <iostream>
#include <cassert>

using namespace gg;

EVertexFormat parseFormat(const std::string& name)
{
    int format = 0;
    auto pos = name.find("P3");
    if (pos != std::string::npos)
    {
        format |= EVertexFormat::P3;
    }
    pos = name.find("C4");
    if (pos != std::string::npos)
    {
        format |= EVertexAttributeType::Color;
    }
    pos = name.find("UV2");
    if (pos != std::string::npos)
    {
        format |= EVertexAttributeType::UV;
    }
    return static_cast<EVertexFormat>(format);
}

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

                auto format = parseFormat(currentName);

                shaders[currentName] = std::make_pair(currentShader, format);

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
        return shaderIt->second.first;
    }
    else
    {
        assert(false);
        return std::string();
    }
}
