#include "GG/Core/Objects/Object.h"
#include "GG/Core/Objects/Component.h"

gg::CObject* gg::CObject::Create( const char* name, CObject* parent )
{
    // TODO: Custom alloc?
    static unsigned nextID = 0;
    return new CObject( name, parent, nextID++ );
}

void gg::CObject::Destroy(CObject* object)
{
    delete object;
}

gg::CObject::CObject(const char* name, CObject* parent, ObjectID id)
    : _name(name)
    , _parent(parent)
    , _id(id)
{
}

bool gg::CObject::HasParent() const
{
    return _parent != nullptr;
}

gg::CObject* gg::CObject::GetParent()
{
    return _parent;
}

gg::CObject* gg::CObject::GetTopParent()
{
    if(_parent == nullptr)
    {
        return this;
    }

    return _parent->GetTopParent();
}

void gg::CObject::AddComponent(CComponent& component)
{
    component._owner = this;
    _components.push_back(&component);
}