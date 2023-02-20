#include "GG/Core/Engine.h"

#include "Service/ServiceProvider.h"

#include <GG/Rendering/Window.h>
#include <iostream>

gg::CEngine::CEngine()
	: _serviceProvider( new CServiceProvider() )
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
	while ( window.IsOpen() )
	{
		window.Clear();
		window.PollEvents();
		window.Present();
	}
}

gg::IServiceProvider& gg::CEngine::GetServiceProvider()
{
	return *(_serviceProvider);
}