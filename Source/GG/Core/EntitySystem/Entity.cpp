#include "GG/Core/EntitySystem/Entity.h"

gg::CEntity::CEntity()
	: _componentsMap()
{
}

gg::CEntity* gg::CEntity::Instantiate()
{
	return new CEntity();
}
