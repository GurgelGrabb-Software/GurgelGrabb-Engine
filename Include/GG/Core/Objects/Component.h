#pragma once

namespace gg
{
    class CObject;

    class CComponent
    {
        friend CObject;

    public:
        using ComponentID = unsigned;

        CObject& GetOwner() { return *_owner; }
        const CObject& GetOwner() const { return *_owner; }

    private:
        CObject* _owner;
    };
}