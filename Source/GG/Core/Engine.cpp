#include "GG/Core/Engine.h"

#include "Service/ServiceProvider.h"

#include <GG/Core/Messaging/MessageQueue.h>
#include <GG/Core/Playground.h>
#include <GG/Core/Threading/ThreadPool.h>
#include <GG/Rendering/RenderManager.h>
#include <GG/Rendering/Window.h>

gg::CEngine::CEngine()
	: _serviceProvider( new CServiceProvider() )
	, _threadPool( _serviceProvider->EmplaceRegister< CThreadPool >( 4 ) )
	, _msgQueue( _serviceProvider->EmplaceRegister< CMessageQueue >() )
{
}

gg::CEngine::~CEngine()
{
	delete _serviceProvider;
}

void gg::CEngine::Run()
{
	CWindow window( 800u, 800u, "Hello :D" );

	CRenderManager rm( window, _threadPool );

	while ( window.IsOpen() )
	{
		_threadPool.CallOnCompletes( 100 );
		_msgQueue.SendAllEvents();

		window.PollEvents();

		_systemContainer.Tick( ESystemTickGroup::PreRender, *_serviceProvider );

		window.Clear();

		rm.Draw();

		window.Present();

		_systemContainer.Tick( ESystemTickGroup::PostRender, *_serviceProvider );
	}
}

gg::IServiceProvider& gg::CEngine::GetServiceProvider()
{
	return *( _serviceProvider );
}