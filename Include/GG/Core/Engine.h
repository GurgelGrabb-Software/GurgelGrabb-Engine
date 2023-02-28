#pragma once

#include "GG/Core/EntitySystem/SystemContainer.h"
#include "GG/Core/Service/ServiceProviderInterface.h"

namespace gg
{
	class CEngine
	{
	public:
		CEngine();
		~CEngine();
		void Run();

		IServiceProvider& GetServiceProvider();

	private:
		IServiceProvider* _serviceProvider;
		CSystemContainer _systemContainer;

		// Service refs
		class CThreadPool& _threadPool;
		class CMessageQueue& _msgQueue;
	};
} // namespace gg