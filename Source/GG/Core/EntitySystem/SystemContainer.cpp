#include "GG/Core/EntitySystem/SystemContainer.h"

void gg::CSystemContainer::AddSystem( CSystem& addSystem )
{
	_addedSystems.push_back( &addSystem );
	_systemsMap[addSystem.GetTickGroup()].push_back( &addSystem );
}

void gg::CSystemContainer::Tick( ESystemTickGroup group, IServiceProvider& provider )
{
	for ( CSystem* sysPtr : _addedSystems )
	{
		sysPtr->Start( provider );
	}
	_addedSystems.clear();

	for ( auto& systemInGroup : _systemsMap[group] )
	{
		systemInGroup->Tick( provider );
	}
}