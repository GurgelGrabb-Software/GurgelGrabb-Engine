#pragma once

#include "GG/Rendering/RenderTypes.h"
#include "GG/Rendering/VertexBuffer.h"

#include <memory>

namespace gg
{
    class CVertexBuffer;

    namespace GraphicsUtilities
    {
        std::shared_ptr<CVertexBuffer> CreateTriangle(float size = 1.f, EVertexFormat format = EVertexFormat::P3C4);
        std::shared_ptr<CVertexBuffer> CreateTriangle(float size, const SFloat4& color);
        
        std::shared_ptr<CVertexBuffer> CreateRectangle(float width = 1.f, float height = 1.f, EVertexFormat format = EVertexFormat::P3C4);
        std::shared_ptr<CVertexBuffer> CreateRectangleColor(float width, float height, const SFloat4& color);
        std::shared_ptr<CVertexBuffer> CreateRectangleUV(float width, float height);
        std::shared_ptr<CVertexBuffer> CreateRectangleColorUV(float width, float height, const SFloat4& color);
        
        std::shared_ptr<CVertexBuffer> CreateCircle(float diameter = 1.f, int resolution = 32, EVertexFormat format = EVertexFormat::P3C4);
        std::shared_ptr<CVertexBuffer> CreateCircle(float diameter, const SFloat4& color, int resolution = 32);

        template< typename T >
        void SetVertexAttributes(CVertexBuffer& buffer, EVertexAttributeType type, const T& data)
        {
            std::vector<float> attr(buffer.GetVertexCount() * 4);
            for (int i = 0; i < buffer.GetVertexCount(); ++i)
            {
                T& c = *(T*)(&attr[i*4]);
                c = data;
            }
            buffer.SetAttributeData(type, attr);
        }
    }
}