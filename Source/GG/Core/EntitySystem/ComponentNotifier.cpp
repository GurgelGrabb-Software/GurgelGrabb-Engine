#include "GG/Core/EntitySystem/ComponentNotifier.h"

using namespace gg;

CComponentNotifier::~CComponentNotifier()
{
	for ( const auto& [id, list] : _listeners )
	{
		for ( auto& listener : list )
		{
			listener->RemoveNotifier( this );
		}
	}
}

void CComponentNotifier::AddListener( IComponentListener* listener )
{
	_listeners[listener->GetTypeID()].Add( listener );
	listener->AddNotifier( this );
}

void CComponentNotifier::RemoveListener( IComponentListener* listener )
{
	auto& list = _listeners[listener->GetTypeID()];
	for ( int i = 0; i < list.Size(); ++i )
	{
		if ( list[i] == listener )
		{
			list.Remove( i );
			break;
		}
	}
}