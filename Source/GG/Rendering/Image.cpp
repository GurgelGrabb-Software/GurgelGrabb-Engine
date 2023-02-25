#include "GG/Rendering/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace gg;

std::shared_ptr<CImage> CImage::LoadFromFile(const std::filesystem::path& filepath)
{
    int w, h, ch;
    
    const PixelData data = (PixelData)stbi_load(filepath.string().c_str(), &w, &h, &ch, 0);

    auto image = std::make_shared<CImage>(w, h, static_cast<ETextureFormat>(ch-1), data);

    return image;
}

void CImage::SaveToFile(CImage& image, const std::filesystem::path& filepath)
{
    int channels = static_cast<int>(image._format) + 1;
    stbi_write_png(filepath.string().c_str(), image._width, image._height, channels, image._pixels, image._width * channels);
}

CImage::CImage(unsigned width, unsigned height, ETextureFormat format, const PixelData data) : 
_width(width),
_height(height),
_format(format)
{
    int channels = static_cast<int>(_format) + 1;
    _pixels = new unsigned char[width * height * channels];
    memcpy(_pixels, data, width * height * channels);
}