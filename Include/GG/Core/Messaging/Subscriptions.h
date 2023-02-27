#pragma once

#include "GG/Core/Messaging/SubscriptionHandle.h"

#include <vector>

namespace gg
{
	class CSubscriptions
	{
	public:
		CSubscriptions();
		~CSubscriptions();
		void AddSubscription( const SSubscriptionHandle& InHandle );

	private:
		std::vector< SSubscriptionHandle > Handles;
	};
} // namespace gg
