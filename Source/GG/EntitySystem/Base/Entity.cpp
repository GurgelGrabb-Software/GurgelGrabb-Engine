#include "GG/EntitySystem/Base/Entity.h"

gg::CEntity::CEntity()
	: _componentsMap()
{
}

gg::CEntity* gg::CEntity::Instantiate()
{
	return new CEntity();
}
