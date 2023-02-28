#include "GG/Core/EntitySystem/SystemContainer.h"

void gg::CSystemContainer::AddSystem( CSystem& addSystem )
{
	_addedSystems.Add( &addSystem );
	_systemsMap[addSystem.GetTickGroup()].Add( &addSystem );
}

void gg::CSystemContainer::Tick( ESystemTickGroup group, IServiceProvider& provider )
{
	for ( CSystem* sysPtr : _addedSystems )
	{
		sysPtr->Start( provider );
	}
	_addedSystems.Clear();

	for ( auto& systemInGroup : _systemsMap[group] )
	{
		systemInGroup->Tick( provider );
	}
}