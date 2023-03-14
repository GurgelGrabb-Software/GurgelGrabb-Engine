#include "GG/Core/Utility/TimeManager.h"

#include "GG/Core/Service/ServiceProviderInterface.h"

#include <iostream>
#include <string>

using namespace gg;

void CTimeManager::Start( IServiceProvider& serviceProvider ) { }

void CTimeManager::Tick( IServiceProvider& serviceProvider )
{
	_dt = _timer.Restart();
}