#pragma once

#include "GG/Core/EntitySystem/System.h"

namespace gg
{
	class CGameSystem : public CSystem
	{
	public:
		virtual ESystemTickGroup GetTickGroup() const override
		{
			return ESystemTickGroup::PreRender;
		}

		virtual void Start( IServiceProvider& serviceProvider ) override;

		virtual void Tick( IServiceProvider& serviceProvider ) override;

	private:
	};
} // namespace gg