#pragma once
#include <cassert>
#include <map>
#include <typeinfo>
#include <utility>
#include "GG/EntitySystem/Base/Component.h"


namespace gg
{
	class CComponent;

	class CEntity
	{
	public:
		static CEntity* Instantiate();

		template < typename TComponent >
		TComponent& AddComponent( TComponent& c )
		{
			const auto cid = GetCompID< TComponent >();
			assert( !_componentsMap.contains( cid ) );
			_componentsMap[cid] = &c;
			return *_componentsMap[cid];
		}

		template < typename TComponent, typename... TArgs >
		TComponent& EmplaceComponent( TArgs&&... args )
		{
			const auto cid = GetCompID< TComponent >();
			assert( !_componentsMap.contains( cid ) );

			_componentsMap[cid] = CComponent::Instantiate<TComponent, TArgs...>( *this, args... );
			return *static_cast<TComponent*>(_componentsMap[cid]);
		}

		template < typename TComponent >
		TComponent& GetComponent()
		{
			const auto cid = GetCompID< TComponent >();
			assert( _componentsMap.contains( cid ) );
			return *static_cast<TComponent*>(_componentsMap[cid]);
		}

		template < typename TComponent >
		const TComponent& GetComponent() const
		{
			const auto cid = GetCompID< TComponent >();
			assert( _componentsMap.contains( cid ) );
			return *_componentsMap[cid];
		}

		template < typename TComponent >
		bool HasComponent() const
		{
			const auto cid = GetCompID< TComponent >();
			assert( _componentsMap.contains( cid ) );
			return _componentsMap[cid];
		}

	private:
		CEntity();

	private:
		using CompTypeID = size_t;

		template < typename TComponent >
		constexpr static size_t GetCompID()
		{
			return typeid( TComponent ).hash_code();
		}

		std::map< CompTypeID, CComponent* > _componentsMap;
	};
} // namespace gg