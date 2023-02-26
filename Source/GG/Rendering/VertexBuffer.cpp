#include "GG/Rendering/VertexBuffer.h"

#include "GG/Rendering/RenderTypes.h"

#include "GG/Rendering/GLInclude.h"

#include <cmath>
#include <cassert>

using namespace gg;

CVertexBuffer::CVertexBuffer(EVertexFormat format, EVertexAccessMode accessMode) : 
_format(format),
_accessMode(accessMode)
{
    glGenVertexArrays(1, &_handle);
    glBindVertexArray(_handle);

    if (HasFlag(format, EVertexAttributeType::Position))
    {
        addAttribute(EVertexAttributeType::Position, {});
    }

    if (HasFlag(format, EVertexAttributeType::Color))
    {
        addAttribute(EVertexAttributeType::Color, {});
    }

    if (HasFlag(format, EVertexAttributeType::UV))
    {
        addAttribute(EVertexAttributeType::UV, {});
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

const std::vector<float>& CVertexBuffer::GetAttributeData(EVertexAttributeType type) const
{
    auto it = _attributeHandles.find(type);
    assert(it != _attributeHandles.end());

    return it->second.data;
}

void CVertexBuffer::SetAttributeData(EVertexAttributeType type, const std::vector<float>& data)
{
    auto it = _attributeHandles.find(type);
    if (it == _attributeHandles.end())
    {
        assert(false && "Attribute does not exist.");
        return;
    }

    it->second.data = data;

    _vertexCount = data.size() / GetNumOfElements(type);

    Bind();

    glBindBuffer(GL_ARRAY_BUFFER, it->second.handle);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), ConvertToGLType(_accessMode));

    glEnableVertexAttribArray(it->second.index);
    glVertexAttribPointer(it->second.index, GetNumOfElements(type), GL_FLOAT, false, GetByteSize(type), (void*)0);
}

void CVertexBuffer::addAttribute(EVertexAttributeType type, const std::vector<float>& data)
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

bool CVertexBuffer::hasAttribute(EVertexAttributeType type)
{
    return _attributeHandles.find(type) != _attributeHandles.end();
}

bool CVertexBuffer::ValidateAttributes() const
{
    for (auto& attrHandle : _attributeHandles)
    {
        if (attrHandle.second.data.size() / GetNumOfElements(attrHandle.first) == _vertexCount)
        {
            assert(false && "Attributes are not synced!");
            return false;
        }
    }
    return true;
}

void CVertexBuffer::SetPrimitiveType(EPrimitiveType primitiveType)
{
    _primitiveType = primitiveType;
}