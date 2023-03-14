#pragma once

#include "GG/Core/Service/ServiceInterface.h"

#include <typeinfo>

namespace gg
{
	using ServiceTypeID = size_t;

	class IServiceProvider
	{
	public:
		template < typename TService >
		TService* Get()
		{
			return static_cast< TService* >( Get( typeid( TService ).hash_code() ) );
		}

		template < typename TService >
		const TService* Get() const
		{
			return static_cast< const TService* >( Get( typeid( TService ).hash_code() ) );
		}

		template < typename TService >
		bool HasService() const
		{
			return HasService( typeid( TService ).hash_code() );
		}

		template < typename TService, typename... TArgs >
		TService& EmplaceRegister( TArgs&&... args )
		{
			TService* made = new TService( args... );
			Register( *made, typeid( TService ).hash_code(), true );
			return *made;
		}

		template < typename TService >
		void Register( TService& service )
		{
			Register( service, typeid( TService ).hash_code(), false );
		}

	public:
		virtual ~IServiceProvider() { }
		virtual void Register( IService& service, ServiceTypeID serviceType, bool autoRelease ) = 0;
		virtual void Unregister( ServiceTypeID serviceType, bool release = true ) = 0;

		virtual IService* Get( ServiceTypeID serviceType ) = 0;
		virtual const IService* Get( ServiceTypeID serviceType ) const = 0;

		virtual bool HasService( ServiceTypeID serviceType ) const = 0;
	};
} // namespace gg