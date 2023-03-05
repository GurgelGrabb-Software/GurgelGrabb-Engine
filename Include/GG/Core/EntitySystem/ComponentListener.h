#pragma once

#include "GG/Common/Container/List.h"

namespace gg
{
	class CComponentNotifier;

	struct SNotifierList
	{
		~SNotifierList();

		TList< CComponentNotifier* > list;
		class IComponentListener* owner;
	};

	class IComponentListener
	{
	public:
		virtual ~IComponentListener() = default;
		constexpr virtual size_t GetTypeID() const = 0;
		virtual void AddNotifier( CComponentNotifier* ) = 0;
		virtual void RemoveNotifier( CComponentNotifier* ) = 0;
	};

	template < typename T >
	class TComponentListener : public IComponentListener
	{
	public:
		TComponentListener()
		{
			_notifiers.owner = this;
		}

		constexpr virtual size_t GetTypeID() const override
		{
			return typeid( T ).hash_code();
		}

		virtual void AddNotifier( CComponentNotifier* notifier ) override
		{
			_notifiers.list.Add( notifier );
		}

		virtual void RemoveNotifier( CComponentNotifier* notifier ) override
		{
			auto& list = _notifiers.list;
			for ( int i = 0; i < list.Size(); ++i )
			{
				if ( list[i] == notifier )
				{
					list.Remove( i );
					break;
				}
			}
		}

		virtual void OnComponentAdded( T& component ) = 0;
		virtual void OnComponentChanged( T& component ) {};
		virtual void OnComponentRemoved( T& component ) = 0;

	private:
		SNotifierList _notifiers;
	};
} // namespace gg