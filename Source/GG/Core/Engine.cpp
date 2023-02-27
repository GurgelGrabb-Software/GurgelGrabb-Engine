#include "GG/Core/Engine.h"

#include "Service/ServiceProvider.h"

#include <GG/Rendering/Window.h>
#include <GG/Core/Threading/ThreadPool.h>
#include <GG/Core/Messaging/MessageQueue.h>
#include <iostream>

#include <GG/Core/Playground.h>

gg::CEngine::CEngine()
	: _serviceProvider( new CServiceProvider() ),
	_threadPool(_serviceProvider->EmplaceRegister<CThreadPool>(4)),
	_msgQueue(_serviceProvider->EmplaceRegister<CMessageQueue>())
{
}

gg::CEngine::~CEngine()
{
	delete _serviceProvider;
}

void gg::CEngine::Run()
{
	CWindow window;
	window.Create( 800u, 800u, "Hello :D" );

	CPlayground pg;
	
	while ( window.IsOpen() )
	{
		_threadPool.CallOnCompletes(100);
		_msgQueue.SendAllEvents();

		window.PollEvents();
		pg.Update();

		window.Clear();

		pg.Draw(window);

		window.Present();
	}
}

gg::IServiceProvider& gg::CEngine::GetServiceProvider()
{
	return *(_serviceProvider);
}