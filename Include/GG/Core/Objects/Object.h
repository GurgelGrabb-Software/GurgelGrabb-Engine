#pragma once
#include <string>
#include <vector>

namespace gg
{
    class CComponent;

    class CObject
    {
    public:
        static CObject* Create(const char* name, CObject* parent = nullptr);
        static void Destroy( CObject* object );

    public:
        bool HasParent() const;
        CObject* GetParent();
        CObject* GetTopParent();

        void AddComponent( CComponent& component );
    private:
        using ObjectID = unsigned;

        CObject( const char* name, CObject* parent, ObjectID id );

        std::vector<CComponent*> _components;
        std::string _name;
        CObject* _parent;
        ObjectID _id;
    };
}