#include "ServiceProvider.h"

gg::CServiceProvider::CServiceProvider()
	: _serviceMap()
{
}

gg::CServiceProvider::~CServiceProvider()
{
	while ( !_serviceMap.empty() )
	{
        auto it = _serviceMap.end();
        it--;
		Unregister( it->first );
	}
}

void gg::CServiceProvider::Register( IService& service, ServiceTypeID serviceType )
{
	if ( HasService( serviceType ) )
	{
		// TODO: Log error here
		return;
	}

	_serviceMap[serviceType] = &service;
}

void gg::CServiceProvider::Unregister( ServiceTypeID serviceType, bool release )
{
	if ( release )
	{
		IService* unregService = Get( serviceType );
		delete unregService;
	}

	_serviceMap.erase( serviceType );
}

gg::IService* gg::CServiceProvider::Get( ServiceTypeID serviceType )
{
	auto found = _serviceMap.find( serviceType );
	if ( found == _serviceMap.end() )
	{
		return nullptr;
	}

	return found->second;
}

const gg::IService* gg::CServiceProvider::Get( ServiceTypeID serviceType ) const
{
	auto found = _serviceMap.find( serviceType );
	if ( found == _serviceMap.end() )
	{
		return nullptr;
	}

	return found->second;
}

bool gg::CServiceProvider::HasService( ServiceTypeID serviceType ) const
{
	return _serviceMap.contains( serviceType );
}