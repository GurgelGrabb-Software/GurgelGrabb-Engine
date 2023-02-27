#pragma once

#include <filesystem>
#include <memory>

#include "GG/Rendering/RenderTypes.h"

namespace gg
{
    class CImage
    {
    public:

        using PixelData = unsigned char*;

        static std::shared_ptr<CImage> LoadFromFile(const std::filesystem::path& filepath);
        static void SaveToFile(CImage& image, const std::filesystem::path& filepath);

        CImage(unsigned width, unsigned height, ETextureFormat format, PixelData data = nullptr);
        ~CImage();

        unsigned GetWidth() const { return _width; };
        unsigned GetHeight() const { return _height; };
        ETextureFormat GetFormat() const { return _format; };
        const PixelData GetData() const { return _pixels; };

    private:

        unsigned _width, _height;
        PixelData _pixels = nullptr;
        ETextureFormat _format;
    
    };
}