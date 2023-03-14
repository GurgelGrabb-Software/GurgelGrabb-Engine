#pragma once

#include "GG/Core/Service/ServiceProviderInterface.h"

#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace gg
{
	class CServiceProvider : public IServiceProvider
	{
	public:
		CServiceProvider();
		~CServiceProvider();

		void Register( IService& service, ServiceTypeID serviceType, bool autoRelease ) override;
		void Unregister( ServiceTypeID serviceType, bool release = true ) override;

		IService* Get( ServiceTypeID serviceType ) override;
		const IService* Get( ServiceTypeID serviceType ) const override;

		bool HasService( ServiceTypeID serviceType ) const override;

	private:
		std::unordered_map< ServiceTypeID, IService* > _serviceMap;
		std::stack< ServiceTypeID > _deletionStack;
		std::unordered_set< IService* > _owned;
	};
} // namespace gg
