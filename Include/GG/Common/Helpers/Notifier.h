#pragma once

#include <cassert>
#include <functional>
#include <type_traits>
#include <vector>

namespace gg
{
	class CListener;

	class INotifier
	{
	public:
		virtual void RemoveListener( CListener* ) = 0;
	};

	class CListener
	{
	protected:
		CListener() {};

	public:
		virtual ~CListener()
		{
			if ( _notifier )
			{
				_notifier->RemoveListener( this );
			}
		};

		void SetNotifier( INotifier* notifier )
		{
			assert( ( notifier == nullptr ) || ( _notifier == nullptr ) );
			_notifier = notifier;
		}

	private:
		INotifier* _notifier = nullptr;
	};

	template < typename ListenerType >
	class TNotifier : INotifier
	{

	public:
		~TNotifier()
		{
			for ( auto& listener : _listeners )
			{
				listener->SetNotifier( nullptr );
			}
		}

		void NotifyListeners( const std::function< void( ListenerType& ) >& func )
		{
			for ( auto& listener : _listeners )
			{
				func( *listener );
			}
		}

		void AddListener( ListenerType* listener )
		{
			_listeners.push_back( listener );
			listener->SetNotifier( this );
		}

		virtual void RemoveListener( CListener* listener ) override
		{
			std::erase_if( _listeners,
						   [listener]( ListenerType* l )
						   {
							   if ( l == listener )
							   {
								   l->SetNotifier( nullptr );
								   return true;
							   }
							   return false;
						   } );
		}

	private:
		std::vector< ListenerType* > _listeners;
	};
} // namespace gg