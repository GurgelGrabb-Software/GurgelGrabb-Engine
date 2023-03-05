#include "GG/Core/Graphics/DrawableComponent.h"

#include "GG/Core/EntitySystem/Entity.h"

using namespace gg;

DEFINE_COMPONENT( CDrawableComponent );

CDrawableComponent::CDrawableComponent( CEntity& owner )
	: CComponent( owner )
{
}
