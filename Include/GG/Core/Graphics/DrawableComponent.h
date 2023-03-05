#pragma once

#include "GG/Core/EntitySystem/Component.h"

namespace gg
{
	class CDrawableComponent : public CComponent
	{
	public:
		DECLARE_COMPONENT( CDrawableComponent );

		CDrawableComponent( CEntity& owner );
		virtual ~CDrawableComponent() = default;
	};
} // namespace gg