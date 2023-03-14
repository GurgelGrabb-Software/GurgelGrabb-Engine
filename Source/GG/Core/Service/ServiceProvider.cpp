#include "ServiceProvider.h"

gg::CServiceProvider::CServiceProvider()
	: _serviceMap()
{
}

gg::CServiceProvider::~CServiceProvider()
{
	while ( !_deletionStack.empty() )
	{
		auto type = _deletionStack.top();
		auto it = _serviceMap.find( type );
		if ( it != _serviceMap.end() )
		{
			auto owned = _owned.find( it->second );
			bool release = false;
			if ( owned != _owned.end() )
			{
				release = true;
				_owned.erase( owned );
			}
			Unregister( it->first, release );
		}
		_deletionStack.pop();
	}
}

void gg::CServiceProvider::Register( IService& service, ServiceTypeID serviceType, bool autoRelease )
{
	if ( HasService( serviceType ) )
	{
		// TODO: Log error here
		return;
	}

	_serviceMap[serviceType] = &service;
	_deletionStack.push( serviceType );
	if ( autoRelease )
	{
		_owned.insert( &service );
	}
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