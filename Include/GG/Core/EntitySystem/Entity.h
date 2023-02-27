#pragma once
#include "GG/Core/EntitySystem/Component.h"
#include "GG/Core/Objects/Transform.h"

#include <cassert>
#include <map>
#include <typeinfo>
#include <utility>

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

			_componentsMap[cid] = CComponent::Instantiate< TComponent, TArgs... >( *this, args... );
			return *static_cast< TComponent* >( _componentsMap[cid] );
		}

		template < typename TComponent >
		TComponent& GetComponent()
		{
			const auto cid = GetCompID< TComponent >();
			assert( _componentsMap.contains( cid ) );
			return *static_cast< TComponent* >( _componentsMap[cid] );
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

		CTransform& GetTransform();
		const CTransform& GetTransform() const;
	private:
		CEntity();

	private:
		using CompTypeID = size_t;

		template < typename TComponent >
		constexpr static size_t GetCompID()
		{
			return typeid( TComponent ).hash_code();
		}

		CTransform _transform;
		std::map< CompTypeID, CComponent* > _componentsMap;
	};
} // namespace gg