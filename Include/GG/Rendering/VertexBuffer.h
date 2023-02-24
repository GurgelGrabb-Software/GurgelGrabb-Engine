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
        size_t GetVertexCount() const { return _vertexCount; };
        EVertexAccessMode GetAccessMode() const { return _accessMode; };
        EPrimitiveType GetPrimitiveType() const { return _primitiveType; };

        void Bind() const;

        const std::vector<float>& GetAttributeData(EAttributeType type) const;
        void SetAttributeData(EAttributeType type, const std::vector<float>& data);
        bool ValidateAttributes() const;

        void SetPrimitiveType(EPrimitiveType primitiveType);

    private:

        bool hasAttribute(EAttributeType type);
        void addAttribute(EAttributeType type, const std::vector<float>& data);

        unsigned _handle;
        size_t _vertexCount;
        EVertexFormat _format;
        EVertexAccessMode _accessMode;
        EPrimitiveType _primitiveType;

        struct SAttributeHandle {
            unsigned handle;
            unsigned index;
            std::vector<float> data;
        };
        std::unordered_map<EAttributeType, SAttributeHandle> _attributeHandles;
    };
}