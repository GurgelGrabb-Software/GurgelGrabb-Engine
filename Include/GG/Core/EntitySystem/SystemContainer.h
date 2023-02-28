#pragma once
#include "GG/Core/EntitySystem/System.h"

#include <GG/Common/Container/List.h>
#include <map>

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
		TList< CSystem* > _addedSystems;
		std::map< ESystemTickGroup, TList< CSystem* > > _systemsMap;
	};
} // namespace gg