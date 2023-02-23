#include "GG/Rendering/VertexBuffer.h"

#include "GG/Rendering/RenderTypes.h"

#include "GG/Rendering/GLInclude.h"

#include <cmath>
#include <cassert>

using namespace gg;

unsigned convertToGLType(EVertexAccessMode mode)
{
    switch (mode)
    {
    case EVertexAccessMode::Static:
        return GL_STATIC_DRAW;
        break;
    case EVertexAccessMode::Dynamic:
        return GL_DYNAMIC_DRAW;
    default:
        return GL_STATIC_DRAW;
        break;
    }
}

CVertexBuffer::CVertexBuffer(EVertexFormat format, EVertexAccessMode accessMode) : 
_format(format),
_accessMode(accessMode)
{
    glGenVertexArrays(1, &_handle);
    glBindVertexArray(_handle);

    if (HasFlag(format, EAttributeType::Position))
    {
        addAttribute(EAttributeType::Position, {});
    }

    if (HasFlag(format, EAttributeType::Color))
    {
        addAttribute(EAttributeType::Color, {});
    }

    if (HasFlag(format, EAttributeType::UV))
    {
        addAttribute(EAttributeType::UV, {});
    }
}

CVertexBuffer::~CVertexBuffer()
{
    glDeleteBuffers(1, &_handle);
}

void CVertexBuffer::Bind() const
{
    glBindVertexArray(_handle);
}

const std::vector<float>& CVertexBuffer::GetAttributeData(EAttributeType type) const
{
    auto it = _attributeHandles.find(type);
    assert(it != _attributeHandles.end());

    return it->second.data;
}

void CVertexBuffer::SetAttributeData(EAttributeType type, const std::vector<float>& data)
{
    auto it = _attributeHandles.find(type);
    assert(it != _attributeHandles.end());

    it->second.data = data;

    Bind();

    glBindBuffer(GL_ARRAY_BUFFER, it->second.handle);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), convertToGLType(_accessMode));

    glEnableVertexAttribArray(it->second.index);
    glVertexAttribPointer(it->second.index, (sizeof(float) * data.size()) / GetSize(type), GL_FLOAT, false, GetSize(type), (void*)0);
}

void CVertexBuffer::addAttribute(EAttributeType type, const std::vector<float>& data)
{
    auto index = _attributeHandles.size();

    auto& attrHandle = _attributeHandles[type];
    attrHandle.index = index;
    glGenBuffers(1, &attrHandle.handle);

    if (!data.empty())
    {
        SetAttributeData(type, data);
    }
}

bool CVertexBuffer::hasAttribute(EAttributeType type)
{
    return _attributeHandles.find(type) != _attributeHandles.end();
}