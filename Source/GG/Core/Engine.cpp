#include "GG/Core/Engine.h"

#include "Service/ServiceProvider.h"

#include <GG/Core/EntitySystem/Entity.h>
#include <GG/Core/Graphics/RenderManager.h>
#include <GG/Core/Messaging/MessageQueue.h>
#include <GG/Core/Playground.h>
#include <GG/Core/Threading/ThreadPool.h>
#include <GG/Core/Utility/Timer.h>

gg::CEngine::CEngine()
	: _serviceProvider( new CServiceProvider() )
	, _threadPool( _serviceProvider->EmplaceRegister< CThreadPool >( 4 ) )
	, _msgQueue( _serviceProvider->EmplaceRegister< CMessageQueue >() )
	, _window( 800u, 800u, "Hello :D" )
	, _renderManager( _window, _threadPool )
{
	_window.AddListener( this );
}

gg::CEngine::~CEngine()
{
	delete _serviceProvider;
}

void gg::CEngine::Run()
{
	CTimer timer;

	for ( int i = 0; i < 3; ++i )
	{
		auto& entity = AddEntity();
		entity.EmplaceComponent< CDrawableComponent >();
	}

	while ( _window.IsOpen() )
	{
		_threadPool.CallOnCompletes( 100 );
		_msgQueue.SendAllEvents();

		_window.PollEvents();

		_systemContainer.Tick( ESystemTickGroup::PreRender, *_serviceProvider );

		for ( int i = 0; i < _entities.Size(); ++i )
		{
			auto& entity = _entities[i];
			auto offset = i * 6.28f / _entities.Size();
			entity->GetTransform().SetPosition( { 0.5f * sinf( timer.GetTotalTime() + offset ), 0.5f * cosf( timer.GetTotalTime() + offset ), 0.f } );
		}

		_window.Clear();

		_renderManager.Draw();

		_window.Present();

		_systemContainer.Tick( ESystemTickGroup::PostRender, *_serviceProvider );
	}
}

gg::IServiceProvider& gg::CEngine::GetServiceProvider()
{
	return *( _serviceProvider );
}

CEntity& gg::CEngine::AddEntity()
{
	auto entity = _entities.Add( CEntity::Instantiate() );
	entity->AddListener( &_renderManager );
	return *entity;
}

#include <iostream>
void gg::CEngine::OnKeyEvent( EInputCode key, bool pressed )
{
	std::cout << ToString( (EInputCode)key ) << std::endl;
	if ( key == EInputCode::KEY_D ) _window.RemoveListener( this );
}