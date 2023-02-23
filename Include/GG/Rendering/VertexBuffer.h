#pragma once

#include "GG/Rendering/RenderTypes.h"

#include <unordered_map>
#include <vector>

namespace gg
{
    class CVertexBuffer
    {
    public:
        explicit CVertexBuffer(EVertexFormat format, EVertexAccessMode accessMode = EVertexAccessMode::Static);
        ~CVertexBuffer();

        unsigned GetHandle() const { return _handle; };
        EVertexFormat GetFormat() const { return _format; };
        EVertexAccessMode GetAccessMode() const { return _accessMode; };

        void Bind() const;

        const std::vector<float>& GetAttributeData(EAttributeType type) const;
        void SetAttributeData(EAttributeType type, const std::vector<float>& data);

    private:

        bool hasAttribute(EAttributeType type);
        void addAttribute(EAttributeType type, const std::vector<float>& data);

        unsigned _handle;
        EVertexFormat _format;
        EVertexAccessMode _accessMode;

        struct SAttributeHandle {
            unsigned handle;
            unsigned index;
            std::vector<float> data;
        };
        std::unordered_map<EAttributeType, SAttributeHandle> _attributeHandles;
    };
}