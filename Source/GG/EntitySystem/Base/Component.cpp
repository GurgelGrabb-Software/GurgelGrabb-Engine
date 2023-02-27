#include "GG/EntitySystem/Base/Component.h"

#include "GG/EntitySystem/Base/Entity.h"

using namespace gg;

CComponent::CComponent( CEntity& owner )
	: _ownerPtr( &owner )
{
}

CComponent::~CComponent() { }

const std::string gg::CComponent::GetName() const
{
	return "BaseComponent";
}

CEntity& CComponent::GetOwner()
{
	return *_ownerPtr;
}

const CEntity& CComponent::GetOwner() const
{
	return *_ownerPtr;
}