#pragma once

#include "GG/Core/EntitySystem/ComponentListener.h"
#include "GG/Core/Graphics/DrawableComponent.h"
#include "GG/Core/Math/Mat4x4.h"

#include <memory>

namespace gg
{
	class CVertexBuffer;
	class CShaderProgram;
	class CTexture;
	class CEntity;

	class CRenderManager : public TComponentListener< CDrawableComponent >
	{
	public:
		CRenderManager( class IRenderTarget& target, class CThreadPool& threadPool );

		void Draw();

		virtual void OnComponentAdded( CDrawableComponent& component ) override;
		virtual void OnComponentChanged( CDrawableComponent& component ) override;
		virtual void OnComponentRemoved( CDrawableComponent& component ) override;

	private:
		IRenderTarget& _target;
		CThreadPool& _threadPool;

		struct SDefaults
		{
			std::shared_ptr< CVertexBuffer > texturedSquare;
			std::shared_ptr< CShaderProgram > program;
			std::shared_ptr< CTexture > texture;
		} _defaults;

		struct SDrawable
		{
			CEntity* entity = nullptr;
			CMat4x4 world;
		};

		TList< SDrawable > _drawables;
	};
} // namespace gg