#pragma once

#include "GG/Rendering/RenderTypes.h"

#include <filesystem>
#include <string>
#include <unordered_map>
#include <list>
#include <sstream>

namespace gg
{
    class CShaderParser
    {
    public:

        using ShaderID = std::string;

        CShaderParser();
        ~CShaderParser();

        void ParseFromFile(const std::filesystem::path& filepath);
        void ParseFromString(const std::string& source);
        void ParseFromStream(std::stringstream& source);

        const std::string& GetShaderSource(const std::string& name) const;

    private:
        std::unordered_map<ShaderID, std::pair<std::string, EVertexFormat>> shaders;
    };
}