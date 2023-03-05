#pragma once

#include "GG/Core/EntitySystem/Component.h"
#include "GG/Core/EntitySystem/ComponentListener.h"

namespace gg
{

	class TestComponent : public CComponent
	{
	public:
		TestComponent( class CEntity& owner );
	};

	class CPlayground : public TComponentListener< TestComponent >
	{
	public:
		CPlayground();
		void Update();
		void Draw( class IRenderTarget& target );

		virtual void OnComponentAdded( TestComponent& comp ) override;
		virtual void OnComponentRemoved( TestComponent& comp ) override;
	};
} // namespace gg