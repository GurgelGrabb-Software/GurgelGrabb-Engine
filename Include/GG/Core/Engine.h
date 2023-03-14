#pragma once

#include "GG/Common/Container/SparseList.h"
#include "GG/Common/Helpers/Notifier.h"
#include "GG/Core/EntitySystem/SystemContainer.h"
#include "GG/Core/Graphics/RenderManager.h"
#include "GG/Core/Service/ServiceProviderInterface.h"
#include "GG/Rendering/Window.h"

namespace gg
{
	class CEntity;
	class CSystem;

	class CEngine
		: CInputListener
		, public IService
	{
	public:
		CEngine();
		~CEngine();
		void Run( CSystem* const game );

		IServiceProvider& GetServiceProvider();

		CEntity& AddEntity();

		virtual void OnKeyEvent( EInputCode key, bool pressed ) override;

	private:
		CWindow _window;

		IServiceProvider* _serviceProvider;

		CSystemContainer _systemContainer;
		CRenderManager _renderManager;
		TList< CEntity* > _entities;

		// Service refs
		class CThreadPool& _threadPool;
		class CMessageQueue& _msgQueue;
		class CTimeManager& _timeManager;
	};
} // namespace gg