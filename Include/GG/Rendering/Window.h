#pragma once

#include "GG/Common/Helpers/Notifier.h"
#include "GG/Rendering/InputTypes.h"
#include "GG/Rendering/RenderTarget.h"

#include <glm/vec2.hpp>

namespace gg
{
	class CInputListener : public CListener
	{
	public:
		virtual void OnKeyEvent( EInputCode key, bool pressed ) {};
	};

	class CWindow
		: public IRenderTarget
		, public TNotifier< CInputListener >
	{
	public:
		CWindow( unsigned w, unsigned h, const char* t );

		bool IsOpen() const;

		void Destroy();
		void Clear();
		void PollEvents();
		void Present();
		glm::i32vec2 GetSize() const;

		void SetViewport( int x, int y, int w, int h );

		virtual void Draw( const CVertexBuffer& vertexBuffer ) override;

	private:
		void Create( unsigned w, unsigned h, const char* t );
		void SetupInputCallbacks();

		void* _backendWinPtr;
	};
} // namespace gg