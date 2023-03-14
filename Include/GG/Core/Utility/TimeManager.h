#pragma once

#include "GG/Core/EntitySystem/System.h"
#include "GG/Core/Service/ServiceInterface.h"
#include "GG/Core/Utility/Timer.h"

namespace gg
{
	class CTimeManager
		: public CSystem
		, public IService
	{
	public:
		float GetTotalTime() const
		{
			return _timer.GetTotalTime();
		}

		float GetDeltaTime() const
		{
			return _dt;
		}

		virtual ESystemTickGroup GetTickGroup() const
		{
			return ESystemTickGroup::PreRender;
		};

		virtual void Start( IServiceProvider& serviceProvider ) override;
		virtual void Tick( IServiceProvider& serviceProvider ) override;

	private:
		CTimer _timer;
		float _dt;
	};
} // namespace gg