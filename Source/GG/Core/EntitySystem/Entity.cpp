#include "GG/Core/EntitySystem/Entity.h"

gg::CEntity::CEntity()
	: _transform()
	, _componentsMap()
{
}

gg::CEntity* gg::CEntity::Instantiate()
{
	return new CEntity();
}

gg::CTransform& gg::CEntity::GetTransform()
{
	return _transform;
}

const gg::CTransform& gg::CEntity::GetTransform() const 
{
	return _transform;
}