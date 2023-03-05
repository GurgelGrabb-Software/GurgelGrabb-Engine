#pragma once

#include "GG/Common/Container/List.h"
#include "GG/Core/EntitySystem/ComponentListener.h"

#include <unordered_map>

namespace gg
{
	class CComponentNotifier
	{
	public:
		~CComponentNotifier();

		void AddListener( IComponentListener* listener );
		void RemoveListener( IComponentListener* listener );

		template < typename T >
		void NotifyAdded( T& component )
		{
			for ( auto listener : GetListenerList< T >() )
			{
				static_cast< TComponentListener< T >* >( listener )->OnComponentAdded( component );
			}
		}

		template < typename T >
		void NotifyChanged( T& component )
		{
			for ( auto listener : GetListenerList< T >() )
			{
				static_cast< TComponentListener< T >* >( listener )->OnComponentChanged( component );
			}
		}

		template < typename T >
		void NotifyRemoved( T& component )
		{
			for ( auto listener : GetListenerList< T >() )
			{
				static_cast< TComponentListener< T >* >( listener )->OnComponentRemoved( component );
			}
		}

	private:
		template < typename T >
		TList< IComponentListener* >& GetListenerList()
		{
			return _listeners[typeid( T ).hash_code()];
		}

		std::unordered_map< size_t, TList< IComponentListener* > > _listeners;
	};
} // namespace gg