#pragma once
#include "GG/Core/EntitySystem/System.h"

#include <GG/Common/Container/List.h>
#include <map>

namespace gg
{
	class CSystemContainer
	{
	public:

		~CSystemContainer();

		template < typename TSystem, typename... TArgs >
		void EmplaceSystem( TArgs&&... args )
		{
			CSystem* sysPtr = new TSystem( args... );
			_ownedSystems.Add(sysPtr);
			AddSystem( *sysPtr );
		}

		void AddSystem( CSystem& addSystem );

		void Tick( ESystemTickGroup group, IServiceProvider& provider );

	private:
		TList< CSystem* > _ownedSystems;
		TList< CSystem* > _addedSystems;
		std::map< ESystemTickGroup, TList< CSystem* > > _systemsMap;
	};
} // namespace gg