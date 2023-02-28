#pragma once
#include "GG/Core/EntitySystem/System.h"

#include <map>
#include <vector>

namespace gg
{
	class CSystemContainer
	{
	public:
		template < typename TSystem, typename... TArgs >
		void EmplaceSystem( TArgs&&... args )
		{
			CSystem* sysPtr = new TSystem( args... );
			AddSystem( *sysPtr );
		}

		void AddSystem( CSystem& addSystem );

		void Tick( ESystemTickGroup group, IServiceProvider& provider );

	private:
		std::vector< CSystem* > _addedSystems;
		std::map< ESystemTickGroup, std::vector< CSystem* > > _systemsMap;
	};
} // namespace gg