#pragma once

#include "GG/Core/Service/ServiceProviderInterface.h"

#include <map>

namespace gg
{
	class CServiceProvider : public IServiceProvider
	{
	public:
		CServiceProvider();
		~CServiceProvider();

		void Register( IService& service, ServiceTypeID serviceType ) override;
		void Unregister( ServiceTypeID serviceType, bool release = true ) override;

		IService* Get( ServiceTypeID serviceType ) override;
		const IService* Get( ServiceTypeID serviceType ) const override;

		bool HasService( ServiceTypeID serviceType ) const override;

	private:
		std::map< ServiceTypeID, IService* > _serviceMap;
	};
} // namespace gg
