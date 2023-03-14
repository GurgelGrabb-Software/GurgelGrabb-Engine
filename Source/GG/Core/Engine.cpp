#include "GG/Core/Engine.h"

#include "Service/ServiceProvider.h"

#include <GG/Core/EntitySystem/Entity.h>
#include <GG/Core/Graphics/RenderManager.h>
#include <GG/Core/Messaging/MessageQueue.h>
#include <GG/Core/Playground.h>
#include <GG/Core/Threading/ThreadPool.h>
#include <GG/Core/Utility/TimeManager.h>
#include <GG/Core/Utility/Timer.h>

gg::CEngine::CEngine()
	: _serviceProvider( new CServiceProvider() )
	, _threadPool( _serviceProvider->EmplaceRegister< CThreadPool >( 8 ) )
	, _msgQueue( _serviceProvider->EmplaceRegister< CMessageQueue >() )
	, _timeManager( _serviceProvider->EmplaceRegister< CTimeManager >() )
	, _window( 800u, 800u, "Hello :D" )
	, _renderManager( _window, _threadPool )
{
	_window.AddListener( this );
	_systemContainer.AddSystem( _timeManager );
	_serviceProvider->Register( *this );
}

gg::CEngine::~CEngine()
{
	delete _serviceProvider;
}

void gg::CEngine::Run( CSystem* const game )
{
	if ( game )
	{
		_systemContainer.AddSystem( *game );
	}

	while ( _window.IsOpen() )
	{
		_threadPool.CallOnCompletes( 100 );
		_msgQueue.SendAllEvents();

		_window.PollEvents();

		_systemContainer.Tick( ESystemTickGroup::PreRender, *_serviceProvider );

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

void gg::CEngine::OnKeyEvent( EInputCode key, bool pressed ) { }