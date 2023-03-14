#include "GG/Game/GameSystem.h"

#include "GG/Core/Engine.h"
#include "GG/Core/EntitySystem/Entity.h"
#include "GG/Core/Graphics/DrawableComponent.h"
#include "GG/Core/Service/ServiceProviderInterface.h"
#include "GG/Core/Utility/TimeManager.h"

#include <vector>

using namespace gg;

std::vector< CEntity* > entities;

void CGameSystem::Start( IServiceProvider& serviceProvider )
{
	if ( auto engine = serviceProvider.Get< CEngine >() )
	{
		for ( int i = 0; i < 3; ++i )
		{
			auto& entity = engine->AddEntity();
			entity.EmplaceComponent< CDrawableComponent >();
			entities.push_back( &entity );
		}
	}
}

void CGameSystem::Tick( IServiceProvider& serviceProvider )
{
	auto timer = serviceProvider.Get< CTimeManager >();

	for ( int i = 0; i < entities.size(); ++i )
	{
		auto& entity = *entities[i];
		auto offset = i * 6.28f / entities.size();
		entity.GetTransform().SetPosition( { 0.5f * sinf( timer->GetTotalTime() + offset ), 0.5f * cosf( timer->GetTotalTime() + offset ), 0.f } );
	}
}